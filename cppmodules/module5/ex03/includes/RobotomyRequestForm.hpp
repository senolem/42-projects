/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:35:11 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 18:40:52 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include <iostream>
# include <string>
# include <time.h>
# include "Form.hpp"
# include "Bureaucrat.hpp"
# include "Exception.hpp"

class RobotomyRequestForm : public Form
{
	private:
	std::string	target;

	public:
	RobotomyRequestForm(void);
	RobotomyRequestForm(RobotomyRequestForm const &src);
	~RobotomyRequestForm(void);
	RobotomyRequestForm &operator=(RobotomyRequestForm const &src);
	RobotomyRequestForm(std::string const target);

	std::string	getTarget(void) const;
	virtual bool	execute(Bureaucrat const &executor) const;
	void	robotomize(void) const;
};

std::ostream	&operator<<(std::ostream &stream, const RobotomyRequestForm &form);

#endif