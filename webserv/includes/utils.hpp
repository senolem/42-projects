/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:08:51 by melones           #+#    #+#             */
/*   Updated: 2023/04/05 22:47:29 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include "webserv.hpp"

std::string					concatStringVector(const std::vector<std::string> &vct, const std::string c);
void						printIntStringMap(const std::map<int, std::string> map);
std::string					concatMethods(const t_methods methods);
void						printCgiMap(const std::map<std::string, t_cgi> map);
std::vector<std::string>	split_string(const std::string &str, const std::string &c);
std::string					trim(const std::string& str, const std::string &totrim);
char						**map_split(std::map<std::string, std::string> string_map);
int							get_path_type(const std::string &path);
bool						is_consecutive_slash(char lhs, char rhs);
std::string					remove_consecutive_slashes(const std::string &str);
std::string					itostr(int i);
std::string					get_date(void);
bool						toLowerCharCompare(char c1, char c2);
bool						toLowerStringCompare(const std::string &s1, const std::string &s2);
std::string					strToLower(const std::string &str);
size_t						findCaseInsensitive(std::string str, std::string to_search, size_t pos = 0);
bool						stringIsNumeric(const std::string& str);

#endif