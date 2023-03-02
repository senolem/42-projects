/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:08:51 by melones           #+#    #+#             */
/*   Updated: 2023/03/02 15:01:49 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include "webserv.hpp"

std::string					concatStringVector(const std::vector<std::string> &vct);
void						printIntStringMap(const std::map<int, std::string> map);
std::string					concatMethods(const t_methods methods);
void						printCgiMap(const std::map<std::string, t_cgi> map);
std::vector<std::string>	ft_split_string(const std::string &str, const std::string &c);
std::string					getHeader(std::vector<std::string> header, std::string field);

#endif