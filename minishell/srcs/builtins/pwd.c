/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:22 by albaur            #+#    #+#             */
/*   Updated: 2022/09/20 10:06:51 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **str)
{
	char	*buf;

	(void)str;
	buf = NULL;
	buf = getcwd(buf, sizeof(buf));
	if (buf)
	{
		ft_putendl(buf);
		free(buf);
		buf = NULL;
	}
	else
	{
		perror(strerror(errno));
		ft_putendl("");
	}
	return (0);
}
