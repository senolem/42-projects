/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:53:49 by albaur            #+#    #+#             */
/*   Updated: 2021/11/16 21:11:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2);

int	ft_strcmp(char *s1, char *s2)
{
	int	result;

	result = 0;
	while ((s1[result] == s2[result])
		&& (s1[result] != '\0')
		&& (s2[result] != '\0'))
		result++;
	return (s1[result] - s2[result]);
}
