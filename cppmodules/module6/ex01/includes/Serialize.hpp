/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialize.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:27:08 by albaur            #+#    #+#             */
/*   Updated: 2022/09/16 15:30:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZE_HPP
# define SERIALIZE_HPP

# include <iostream>
# include <string>

typedef struct s_Data
{
	std::string	str;
}		Data;

uintptr_t	serialize(Data *ptr);
Data*		deserialize(uintptr_t raw);

#endif