/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 21:15:23 by albaur            #+#    #+#             */
/*   Updated: 2023/01/25 21:16:46 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	close_file(t_data *data)
{
	std::cout.rdbuf(data->buffer_cout);
	data->file.close();
}

s_data	*open_file(t_data *data, std::string path)
{
	data->file.open(path, std::iostream::out);
	data->buffer_cout = std::cout.rdbuf();
	data->buffer_file = data->file.rdbuf();
	std::cout.rdbuf(data->buffer_file);
	return (data);
}
