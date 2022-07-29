/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:03:51 by faventur          #+#    #+#             */
/*   Updated: 2022/07/06 11:40:23 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_get_env() function takes an environment variable name as a
** parameter and returns its content.
*/

#include "minishell.h"

char	*ft_getenv(char *varname)
{
	char	**arr;
	char	*str;

	arr = env_read(ENV_FILE);
	str = env_get(varname, arr);
	ft_arr_freer(arr);
	return (str);
}
