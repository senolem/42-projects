/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 06:16:34 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 06:22:43 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		++i;
	dup = malloc(sizeof(char) * i + 1);
	if (!dup)
		return (0);
	i = 0;
	while(src[i])
	{
		dup[i] = src[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}

int	main(void)
{
	printf("%s\n", ft_strdup("salut"));
}