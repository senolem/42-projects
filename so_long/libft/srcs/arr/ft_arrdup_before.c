/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:14:16 by albaur            #+#    #+#             */
/*   Updated: 2022/06/16 16:42:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup_before(char **str, char *name)
{
	int		i;
	char	**tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	if (!str)
		return (NULL);
	tmp2 = ft_strjoin(name, "=");
	while (str[i])
	{
		if (!ft_strncmp(str[i], tmp2, ft_strlen(tmp2)))
			break ;
		++i;
	}
	free(tmp2);
	if (!i)
		return (NULL);
	else
		tmp = ft_arrndup(str, i);
	if (!tmp)
		return (NULL);
	return (tmp);
}
