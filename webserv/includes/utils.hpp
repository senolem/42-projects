/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:08:51 by melones           #+#    #+#             */
/*   Updated: 2023/03/05 23:21:03 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include "webserv.hpp"

std::string					concatStringVector(const std::vector<std::string> &vct);
void						printIntStringMap(const std::map<int, std::string> map);
std::string					concatMethods(const t_methods methods);
void						printCgiMap(const std::map<std::string, t_cgi> map);
std::vector<std::string>	split_string(const std::string &str, const std::string &c);
std::string					getHeader(std::vector<std::string> header, std::string field);
char						*ft_itoa(int n);

#endif