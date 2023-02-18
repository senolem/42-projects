/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:21:31 by albaur            #+#    #+#             */
/*   Updated: 2023/02/18 02:12:54 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include <iostream>
# include <string>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <string.h>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <map>
# include "Structures.hpp"

// utils
std::string	concatStringVector(const std::vector<std::string> &vct);
void		printIntStringMap(const std::map<int, std::string> map);
std::string	concatMethods(const ft::t_methods methods);
void		printCgiMap(const std::map<std::string, ft::t_cgi> map);

#endif