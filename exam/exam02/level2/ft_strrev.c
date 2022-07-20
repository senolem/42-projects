/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 06:23:40 by albaur            #+#    #+#             */
/*   Updated: 2022/05/11 06:34:53 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[len])
		++len;
	--len;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		++i;
		--len;
	}
	return (str);
}

int	main(void)
{
	char	str[500] = "abc";
	printf("%s\n", ft_strrev(str));
}