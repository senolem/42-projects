/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:01:49 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 17:45:29 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include "Exception.hpp"

class Bureaucrat
{
	private:
	const std::string	name;
	unsigned int		grade;

	public:
	Bureaucrat(void);
	Bureaucrat(Bureaucrat const &src);
	~Bureaucrat(void);
	Bureaucrat &operator=(Bureaucrat const &src);
	Bureaucrat(std::string const name, unsigned int grade);

	std::string	getName(void) const;
	unsigned int	getGrade(void) const;
	void	incrementGrade(void);
	void	decrementGrade(void);
	void	setGrade(unsigned int grade);
};

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &slave);

#endif