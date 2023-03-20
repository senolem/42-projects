/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:29:38 by melones           #+#    #+#             */
/*   Updated: 2023/03/20 14:38:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string	concatStringVector(const std::vector<std::string> &vct, const char c)
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
		std::cout << "	- [" << iter->second.filetype << "] path : " << iter->second.path << std::endl;
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

int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*toreturn;
	long	nb;

	nb = n;
	i = ft_intlen(nb);
	toreturn = (char *)malloc(i * sizeof(char) + 1);
	if (!toreturn)
		return (0);
	toreturn[i--] = '\0';
	if (nb == 0)
		toreturn[0] = 48;
	if (nb < 0)
	{
		toreturn[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		toreturn[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (toreturn);
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

	res = stat(path.c_str(), &st);
	if (res == 0)
	{
		if (st.st_mode & S_IFREG)
			return (0);
		else if (st.st_mode & S_IFDIR)
			return (1);
		else
			return (-1);
	}
	else if (res == -1 && errno == ENOENT)
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