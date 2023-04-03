/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CloseServer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:42:17 by melones           #+#    #+#             */
/*   Updated: 2023/04/03 10:47:32 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_SERVER_HPP
# define CLOSE_SERVER_HPP
# include "webserv.hpp"

void	close_server(int sig, siginfo_t *info, void *context);

#endif