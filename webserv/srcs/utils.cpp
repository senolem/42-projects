/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:29:38 by melones           #+#    #+#             */
/*   Updated: 2023/03/31 03:33:51 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string	concatStringVector(const std::vector<std::string> &vct, const std::string c)
{
	std::vector<std::string>::const_iterator	iter = vct.begin();
	std::vector<std::string>::const_iterator	iter2 = vct.end();
	std::string									str;

	while (iter != iter2)
	{
		str = str + *iter;
		if (iter + 1 != iter2)
			str = str + c;
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
		std::cout << "	- " << iter->first << " : " << iter->second << "\n";
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
	str += "] ";
	str += "HEAD [";
	if (methods.head)
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
		std::cout << "	- [" << iter->second.filetype << "] path : " << iter->second.path << "\n";
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

std::string trim(const std::string& str, const std::string& totrim)
{
	std::string	result = str;
	size_t		pos;

	pos = result.find_first_not_of(totrim);
	if (pos != std::string::npos)
		result.erase(0, pos);
	pos = result.find_last_not_of(totrim);
	if (pos != std::string::npos)
		result.erase(pos + 1);
	while ((pos = result.find_first_of(totrim)) != std::string::npos)
		result.erase(pos, 1);
	return (result);
}

char	**map_split(std::map<std::string, std::string> string_map)
{
	size_t											i = 0;
	char											**tmp;
	std::map<std::string, std::string>::iterator	iter = string_map.begin();
	std::map<std::string, std::string>::iterator	iter2 = string_map.end();

	tmp = new char*[string_map.size() + 1];
	if (!tmp)
		return (NULL);
	while (iter != iter2)
	{
		std::string	tmp2(iter->first + "=" + iter->second);
		tmp[i] = new char[tmp2.size() + 1];
		if (!tmp[i])
			return (NULL);
		std::strcpy(tmp[i], tmp2.c_str());
		++i;
		++iter;
	}
	tmp[i] = NULL;
	return (tmp);
}

int	get_path_type(const std::string &path)
{
	struct stat	st;
	int			res;
	std::string	tmp(path);

	res = stat(tmp.c_str(), &st);
	if (res == 0)
	{
		if (st.st_mode & S_IFREG)
			return (0);
		else if (st.st_mode & S_IFDIR)
			return (1);
		else
			return (-1);
	}
	else if (res == -1 && (errno == ENOENT || errno == ENOTDIR))
		return (-2);
	return (-1);
}

bool	is_consecutive_slash(char lhs, char rhs)
{
	return (lhs == '/' && rhs == '/');
}

std::string	remove_consecutive_slashes(const std::string &str)
{
	std::string	tmp(str);

	std::string::iterator	iter = std::unique(tmp.begin(), tmp.end(), is_consecutive_slash);
	tmp.erase(iter, tmp.end());
	return (tmp);
}

std::string	itostr(int i)
{
	std::stringstream	stream;

	stream << i;
	return (stream.str());
}

std::string	get_date(void)
{
	time_t		now = time(NULL);
	std::string	date;
	char		buffer[256];
	struct tm	*date_tm;

	#if defined(__APPLE__)
		date_tm = std::localtime(&now);
	#else
		date_tm = std::localtime(&now);
	#endif
	std::strftime(buffer, sizeof(buffer), "on %d-%m-%Y at %H:%M:%S", date_tm);
	date = buffer;
	return (date);
}

char	to_lower(char c)
{
	if (std::isupper(c))
		return (std::tolower(c));
	else
		return (c);
}

bool	toLowerStringCompare(std::string s1, std::string s2)
{
	std::string::iterator	iter;
	std::string				lower_s1(s1.size(), ' ');
	std::string				lower_s2(s2.size(), ' ');

	if (s1.empty() || s2.empty())
		return (false);
	std::transform(s1.begin(), s1.end(), lower_s1.begin(), to_lower);
	std::transform(s2.begin(), s2.end(), lower_s2.begin(), to_lower);
	return (lower_s1 == lower_s2);
}

std::string	strToLower(const std::string &str)
{
	std::string	tmp(str);

	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	return (tmp);
}

size_t	findCaseInsensitive(std::string str, std::string to_search, size_t pos)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::transform(to_search.begin(), to_search.end(), to_search.begin(), ::tolower);
	return (str.find(to_search, pos));
}

bool	stringIsNumeric(const std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}
