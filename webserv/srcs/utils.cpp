/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:29:38 by melones           #+#    #+#             */
/*   Updated: 2023/03/03 14:05:55 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string	concatStringVector(const std::vector<std::string> &vct)
{
	std::vector<std::string>::const_iterator	iter = vct.begin();
	std::vector<std::string>::const_iterator	iter2 = vct.end();
	std::string									str;

	while (iter != iter2)
	{
		str = str + *iter;
		if (iter + 1 != iter2)
			str = str + " ";
		++iter;
	}
	return (str);
}

void	printIntStringMap(const std::map<int, std::string> map)
{
	std::map<int, std::string>::const_iterator	iter = map.begin();
	std::map<int, std::string>::const_iterator	iter2 = map.end();

	while (iter != iter2)
	{
		std::cout << "	- " << iter->first << " : " << iter->second << std::endl;
		++iter;
	}
}

std::string	concatMethods(const t_methods methods)
{
	std::string	str;

	str = "GET [";
	if (methods.get)
		str += "true";
	else
		str += "false";
	str += "] ";
	str += "POST [";
	if (methods.post)
		str += "true";
	else
		str += "false";
	str += "] ";
	str += "DELETE [";
	if (methods.del)
		str += "true";
	else
		str += "false";
	str += "]";
	return (str);
}

void	printCgiMap(const std::map<std::string, t_cgi> map)
{
	std::map<std::string, t_cgi>::const_iterator	iter = map.begin();
	std::map<std::string, t_cgi>::const_iterator	iter2 = map.end();
	
	while (iter != iter2)
	{
		std::cout << "	- [" << iter->second.filetype << "] path : " << iter->second.path << std::endl;
		std::cout << "	- [" << iter->second.filetype << "] methods_allowed : " << concatMethods(iter->second.methods_allowed) << std::endl;
		++iter;
	}
}

std::vector<std::string> split_string(const std::string &s, const std::string &c)
{
	std::string					str(s);			
    std::vector<std::string>	vect;
    size_t						pos = 0;

	if (c == str)
        return (vect);
    while ((pos = str.find(c, 0)) != std::string::npos)
	{
		if (pos == 0)
			str.erase(0, c.length());
		else
		{
        	vect.push_back(str.substr(0, pos));
			str.erase(0, c.length() + pos);
		}
    }
	if (str.length() > 0)
		vect.push_back(str);
	if (vect.empty())
		vect.push_back(str);
	return (vect);
}
