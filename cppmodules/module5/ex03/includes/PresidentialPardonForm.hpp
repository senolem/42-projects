/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:35:24 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 18:40:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include <iostream>
# include <string>
# include "Form.hpp"
# include "Bureaucrat.hpp"
# include "Exception.hpp"

class PresidentialPardonForm : public Form
{
	private:
	std::string	target;

	public:
	PresidentialPardonForm(void);
	PresidentialPardonForm(PresidentialPardonForm const &src);
	~PresidentialPardonForm(void);
	PresidentialPardonForm &operator=(PresidentialPardonForm const &src);
	PresidentialPardonForm(std::string const target);

	std::string	getTarget(void) const;
	virtual bool	execute(Bureaucrat const &executor) const;
	void	pardon(void) const;
};

std::ostream	&operator<<(std::ostream &stream, const PresidentialPardonForm &form);

#endif