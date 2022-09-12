/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:01:49 by albaur            #+#    #+#             */
/*   Updated: 2022/09/12 19:16:02 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include "Exception.hpp"
# include "Form.hpp"

class Form;

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
	void	signForm(Form &boringform);
};

std::ostream	&operator<<(std::ostream &stream, const Bureaucrat &slave);

#endif