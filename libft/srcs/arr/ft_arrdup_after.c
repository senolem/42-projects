/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:14:26 by albaur            #+#    #+#             */
/*   Updated: 2022/06/16 16:37:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup_after(char **str, char *name)
{
	int		i;
	char	**tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (!str)
		return (NULL);
	i = ft_arrlen(str);
	tmp2 = ft_strjoin(name, "=");
	while (str[--i])
	{
		if (!ft_strncmp(str[i], tmp2, ft_strlen(tmp2)))
			break ;
	}
	free(tmp2);
	if (!(ft_arrlen(str) - i - 1))
		return (NULL);
	else
		tmp = ft_arrdup(str + i + 1);
	if (!tmp)
		return (NULL);
	return (tmp);
}
