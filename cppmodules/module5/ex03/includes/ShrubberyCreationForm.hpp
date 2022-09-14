/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:34:58 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 18:06:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include <iostream>
# include <string>
# include <fstream>
# include "Form.hpp"
# include "Bureaucrat.hpp"
# include "Exception.hpp"

class ShrubberyCreationForm : public Form
{
	private:
	std::string	target;

	public:
	ShrubberyCreationForm(void);
	ShrubberyCreationForm(ShrubberyCreationForm const &src);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm &operator=(ShrubberyCreationForm const &src);
	ShrubberyCreationForm(std::string const target);

	std::string	getTarget(void) const;
	virtual bool	execute(Bureaucrat const &executor) const;
	void	plantTree(void) const;
};

std::ostream	&operator<<(std::ostream &stream, const ShrubberyCreationForm &form);

#endif