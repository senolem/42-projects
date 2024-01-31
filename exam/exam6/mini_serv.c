#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

fd_set rfd, wfd, fds;
char rbuf[65536];
char wbuf[65536];
char *msg[65536];
int maxfd = 0;
int clients = 0;
int idx[65536];

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void display(int client, char *wbuf)
{
	for (int i = 0; i <= maxfd; i++)
	{
		if (FD_ISSET(i, &wfd) && i != client)
			send(i, wbuf, strlen(wbuf), 0);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 12);
		exit(1);
	}

	struct sockaddr_in serveraddr;
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if (socketfd < 0)
		fatal();

	FD_ZERO(&fds);
	maxfd = socketfd;
	FD_SET(maxfd, &fds);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(2130706433);
	serveraddr.sin_port = htons(atoi(argv[1]));

	if (bind(socketfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		fatal();

	if (listen(socketfd, 10) != 0)
		fatal();

	while (1)
	{
		rfd = wfd = fds;
		if (select(maxfd + 1, &rfd, &wfd, NULL, NULL) < 0)
			fatal();
		for (int i = 0; i <= maxfd; i++)
		{
			if (!FD_ISSET(i, &rfd))
				continue;
			if (i == socketfd)
			{
				socklen_t len = sizeof(serveraddr);
				int client = accept(socketfd, (struct sockaddr *)&serveraddr, &len);
				if (client >= 0)
				{
					maxfd = client > maxfd ? client : maxfd;
					idx[client] = clients++;
					msg[client] = NULL;
					FD_SET(client, &fds);
					sprintf(wbuf, "server: client %d just arrived\n", idx[client]);
					display(client, wbuf);
					break;
				}
			}
			else
			{
				int rlen = recv(i, rbuf, 6000, 0);
				if (rlen <= 0)
				{
					sprintf(wbuf, "server: client %d just left\n", idx[i]);
					display(i, wbuf);
					FD_CLR(i, &fds);
					free(msg[i]);
					msg[i] = NULL;
					close(i);
					break;
				}
				char *s;
				rbuf[rlen] = '\0';
				msg[i] = str_join(msg[i], rbuf);
				while (extract_message(&(msg[i]), &s))
				{
					sprintf(wbuf, "client %d: ", idx[i]);
					display(i, wbuf);
					display(i, s);
					free(s);
					s = NULL;
				}
			}
		}
	}
}
