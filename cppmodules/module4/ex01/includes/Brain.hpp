/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:22:45 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 14:25:36 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

class Brain
{
	protected:
	std::string	ideas[100];

	public:
	Brain(void);
	Brain(Brain const &src);
	~Brain(void);
	Brain &operator=(Brain const &src);

	void	setIdea(std::string const &idea, int i);
	void	displayIdea(int	const i);
};

#endif