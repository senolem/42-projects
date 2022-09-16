/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:24:58 by albaur            #+#    #+#             */
/*   Updated: 2022/09/16 15:50:35 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialize.hpp"

int	main(void)
{
	Data	*test = new Data;
	uintptr_t	testptr = 0;
	Data		*testdata = NULL;

	test->str = "coucou les ptits zamis kwa";
	testptr = serialize(test);
	testdata = deserialize(testptr);
	std::cout << "Initial data : " << test->str << std::endl;
	std::cout << "Serialized data : " << testptr << std::endl;
	std::cout << "Deserialized data : " << testdata->str << std::endl;
}