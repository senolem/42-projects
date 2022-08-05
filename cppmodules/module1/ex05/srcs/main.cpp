/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:33:48 by albaur            #+#    #+#             */
/*   Updated: 2022/08/05 15:25:15 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(void)
{
	Harl	harltwopointoh;

	harltwopointoh.complain("debug");
	harltwopointoh.complain("info");
	harltwopointoh.complain("warning");
	harltwopointoh.complain("error");
}