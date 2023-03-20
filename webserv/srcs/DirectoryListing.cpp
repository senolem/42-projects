/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListing.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:12:42 by melones           #+#    #+#             */
/*   Updated: 2023/03/20 19:53:23 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectoryListing.hpp"

DirectoryListing::DirectoryListing(void)
{

}

DirectoryListing::DirectoryListing(const DirectoryListing &src)
{
	*this = src;
}

DirectoryListing::~DirectoryListing(void)
{

}

DirectoryListing	&DirectoryListing::operator=(const DirectoryListing &src)
{
	(void)src;
	return (*this);
}

std::string	DirectoryListing::getPage(void)
{
	std::ifstream		file("directory_listing.html");
	std::stringstream	string_stream;

	if (!file.is_open())
		return ("500");
	string_stream << file.rdbuf();
	return (string_stream.str());
}

void	DirectoryListing::generate(t_response_header &response, t_request_header &request)
{
	struct stat					st;
	std::string					page;
	std::string					tmp(request.path);
	std::string					directory;
	std::string					full_path;
	std::string					size;
	std::vector<std::string>	links;

	if (request.path.at(request.path.length() - 1) == '/' && request.path.length() > 0)
		tmp.erase(request.path.length() - 1);
	directory = tmp.substr(tmp.find_last_of('/'));
	tmp.erase(tmp.find(request.matched_subserver->second.root), request.matched_subserver->second.root.length());
	full_path = request.path;
	if (full_path.length() > 0 && full_path.at(0) == '/')
		full_path.erase(0);
	if (full_path.length() > 0 && full_path.at(full_path.length() - 1) != '/')
		full_path.append("/");
	DIR	*dir = opendir(request.path.c_str());
	if (!dir)
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to open folder " << request.path << "\n";
		request.status = 500;
		return ;
	}
	page = getPage();
	if (page == "500")
	{
		std::cout << RED << ERROR << GREEN << SERV << NONE << " Failed to open directory listing template\n";
		request.status = 500;
		return ;
	}
	for (size_t i = page.find("%DIRECTORY%"); i != std::string::npos; i = page.find("%DIRECTORY%"))
		page.replace(i, std::string("%DIRECTORY%").length(), directory);
	for (struct dirent *curr = readdir(dir); curr; curr = readdir(dir))
	{
		std::string	name = curr->d_name;
		stat((full_path + curr->d_name).c_str(), &st);
		if (name == "." || name == ".." || curr->d_type != DT_REG)
			size = "-";
		else
			size = getSize(st);
		std::string	date = getModifiedDate(st);
		links.push_back("<tr><td><a href =\"http://" + request.matched_subserver->first + ":" + request.matched_subserver->second.listen + tmp + "/" + curr->d_name + "\">" + curr->d_name + "</a></td><td>" + size + "</td><td>" + date + "</td></tr>\n");
	}
	std::sort(links.begin(), links.end());
	for (std::vector<std::string>::iterator iter = links.begin(); iter != links.end(); iter++)
		page += *iter;
	page += "</tbody>\n</body>\n</html>\n";
	closedir(dir);
	response.status_code = "200 OK";
	response.content = page;
	response.content_length = page.size();
	response.content_type = "text/html";
}

std::string	DirectoryListing::getSize(struct stat &st)
{
	std::string	size;

	const char*	units[] = {"B", "KB", "MB", "GB", "TB"};
	int			i = 0;
	double		bytes = static_cast<double>(st.st_size);
	char		buffer[128];

	while (bytes >= 1024 && i < 4)
	{
		bytes /= 1024.0;
		++i;
	}
	std::snprintf(buffer, sizeof(buffer), "%.2f %s", bytes, units[i]);
	return (buffer);
}

std::string	DirectoryListing::getModifiedDate(struct stat &st)
{
	std::string	date;
	char		buffer[256];
	struct tm	*date_tm;

	#if defined(__APPLE__)
		date_tm = std::localtime(&st.st_mtimespec.tv_sec);
	#else
		date_tm = std::localtime(&st.st_mtim.tv_sec);
	#endif
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", date_tm);
	date = buffer;
	return (date);
}
