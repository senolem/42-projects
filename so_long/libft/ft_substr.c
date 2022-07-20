/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:20:15 by albaur            #+#    #+#             */
/*   Updated: 2022/03/04 10:24:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!str || !s)
		return (0);
	while (j < len && i < ft_strlen(s))
	{
		str[j++] = s[i++];
	}
	str[j] = 0;
	return (str);
}
