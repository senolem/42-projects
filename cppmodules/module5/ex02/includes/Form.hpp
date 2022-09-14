/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:51:54 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 17:50:51 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include "Bureaucrat.hpp"
# include "Exception.hpp"

class Bureaucrat;

class Form
{
	private:
	const std::string	name;
	bool	isSigned;
	const unsigned int	requiredSignGrade;
	const unsigned int	requiredExecGrade;

	public:
	Form(void);
	Form(Form const &src);
	~Form(void);
	Form &operator=(Form const &src);
	Form(std::string name, unsigned int requiredSignGrade, unsigned int requiredExecGrade);

	std::string	getName(void) const;
	bool	getIsSigned(void) const;
	unsigned int	getRequiredSignGrade(void) const;
	unsigned int	getRequiredExecGrade(void) const;
	void	beSigned(Bureaucrat const &slave);
	void	setSignedTrue(void);
	virtual void	execute(Bureaucrat const &executor) const = 0;
	bool	checkPrerequisites(Bureaucrat const &executor, std::string formType) const;
};

std::ostream	&operator<<(std::ostream &stream, const Form &form);

#endif