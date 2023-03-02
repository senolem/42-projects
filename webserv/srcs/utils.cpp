/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:29:38 by melones           #+#    #+#             */
/*   Updated: 2023/03/02 16:13:08 by albaur           ###   ########.fr       */
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

std::vector<std::string>	ft_split_string(const std::string s, const char c)
{
	size_t						i = 0;
	std::vector<std::string>	split;
	std::string					str(s);

	while (str[i])
	{
		if ((str[i] == c && i != 0) || !str[i + 1])
		{
			if (str[i + 1])
				split.push_back(str.substr(0, i));
			else
				split.push_back(str.substr(0, i + 1));
			str.erase(0, i);
			i = 0;
		}
		if (str[i] == c && i == 0)
			str.erase(0, 1);
		++i;
	}
	return (split);
}

std::vector<std::string> ft_split_string(const std::string &s, const std::string &c)
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

std::string	getHeader(std::vector<std::string> header, std::string field)
{
	size_t								i = 0;
	std::vector<std::string>::iterator	iter = header.begin();
	std::vector<std::string>::iterator	iter2 = header.end();
	std::string							ret;

	while (iter != iter2)
	{
		i = iter->find(field);
		if (i != std::string::npos)
		{
			if (i == 0)
				return (*iter);
			else
				return (ret);
		}
		++iter;
	}
	return (ret);
}
