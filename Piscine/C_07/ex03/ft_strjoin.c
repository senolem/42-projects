/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:46:55 by albaur            #+#    #+#             */
/*   Updated: 2021/11/24 19:24:54 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(int size, char **strs, char *sep);

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*str;
	int		count;
	int		a;
	int		z;
	int		l;

	a = 0;
	z = 0;
	l = 0;
	count = 1;
	while (a < size)
		count += ft_strlen(strs[a++]) + ft_strlen(sep);
	str = malloc(count * sizeof(char *));
	a = -1;
	while (++a < size)
	{
		while (strs[a][z] != '\0')
			str[l++] = strs[a][z++];
		z = 0;
		while (sep[z] && a < size - 1)
			str[l++] = sep[z++];
		z = 0;
	}
	str[l] = '\0';
	return (str);
}
