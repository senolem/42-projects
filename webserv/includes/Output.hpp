/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:08:34 by melones           #+#    #+#             */
/*   Updated: 2023/03/28 16:00:56 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_HPP
# define OUTPUT_HPP
# include <string>

const std::string	SERV = "[Server]";
const std::string	WEBSERV = "[Webserv]";
const std::string	CONFIGPARSER = "[ConfigParser]";
const std::string	ERROR = "[ERROR]";
const std::string	INFO = "[INFO]";
const std::string	RED = "\033[31m";
const std::string	GREEN = "\033[32m";
const std::string	YELLOW = "\033[33m";
const std::string	BLUE = "\033[34m";
const std::string	MAGENTA = "\033[35m";
const std::string	CYAN = "\033[36m";
const std::string	WHITE = "\033[37m";
const std::string	NONE = "\033[0m";

#endif