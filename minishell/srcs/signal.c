/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:55 by albaur            #+#    #+#             */
/*   Updated: 2022/06/19 16:14:39 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler_quit(void)
{
	char	**env;
	char	*nb;

	env = env_read(ENV_FILE);
	if (!env)
		return ;
	nb = env_get("?nb", env);
	if (!ft_strcmp(nb, "1"))
	write(1, "Quit\n", 5);
	free(nb);
	free(env);
}

void	sig_handler(int	sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
		sig_handler_quit();
}

void	sig_wait(t_data *data, int sig, void (*hdlr)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = hdlr;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, sig);
	if (sigaction(sig, &sa, NULL))
		throw_error(data, strerror(sig), 0);
}

void	sig_ignore(t_data *data, int sig)
{
	struct sigaction sa;

	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, sig);
	if (sigaction(sig, &sa, NULL))
		throw_error(data, strerror(sig), 0);
}