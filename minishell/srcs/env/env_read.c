/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:53:47 by albaur            #+#    #+#             */
/*   Updated: 2022/07/01 15:58:02 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_read_clean(t_read *r)
{
	if (r->fd >= 0)
		close(r->fd);
	free(r->tmp);
	if (!r->env)
		return (NULL);
	else
		return (r->env);
}

char	**env_read(char *path)
{
	t_read	r;

	if (!path)
		return (NULL);
	r.i = 1;
	r.tmp = NULL;
	r.fd = open(path, O_RDONLY, 0777);
	r.env = 0;
	if (r.fd < 0)
		return (env_read_clean(&r));
	while (r.i > 0)
	{
		r.i = read(r.fd, r.buffer, 1);
		if (r.i == -1)
			return (env_read_clean(&r));
		r.buffer[r.i] = 0;
		r.tmp = ft_concat(r.tmp, r.buffer);
		if (!r.tmp)
			return (env_read_clean(&r));
	}
	r.env = ft_split(r.tmp, '\n');
	return (env_read_clean(&r));
}
