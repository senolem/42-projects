/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:36:05 by albaur            #+#    #+#             */
/*   Updated: 2022/09/14 17:55:03 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) : Form("ShrubberyCreationForm", 145, 137), target("DefaultTarget")
{

}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src) : Form(src.getName(), src.getRequiredSignGrade(), src.getRequiredExecGrade()), target(src.getTarget())
{
	if (src.getIsSigned())
		this->setSignedTrue();
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{

}

std::ostream	&operator<<(std::ostream &stream, const ShrubberyCreationForm &form)
{
	return (stream << "ShrubberyCreationForm [" << form.getName() << "] : isSigned : " << form.getIsSigned() << " | requiredSignGrade : " << form.getRequiredSignGrade() << " | requiredExecGrade : " << form.getRequiredExecGrade());
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form("DefaultShrubberyCreationForm", 145, 137), target(target)
{

}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (this->checkPrerequisites(executor, "ShrubberyCreationForm"))
		this->plantTree();
}

std::string	ShrubberyCreationForm::getTarget(void) const
{
	return (this->target);
}

void	ShrubberyCreationForm::plantTree(void) const
{
	std::string		path(this->target + "_shrubbery");
	std::ofstream	outFile(path);
	std::string		buffer;

	if (!outFile)
	{
		std::cerr << "Error: cannot create file." << std::endl;
		return ;
	}
	outFile << std::endl;
	outFile << "		                                   .;" << std::endl;
	outFile << "      .              .              ;%     ;;" << std::endl;
	outFile << "        ,           ,                :;%  %;" << std::endl;
	outFile << "         :         ;                   :;%;'     .," << std::endl;
	outFile << ",.        %;     %;            ;        %;'    ,;" << std::endl;
	outFile << "  ;       ;%;  %%;        ,     %;    ;%;    ,%'" << std::endl;
	outFile << "   %;       %;%;      ,  ;       %;  ;%;   ,%;'" << std::endl;
	outFile << "    ;%;      %;        ;%;        % ;%;  ,%;'" << std::endl;
	outFile << "     `%;.     ;%;     %;'         `;%%;.%;'" << std::endl;
	outFile << "      `:;%.    ;%%. %@;        %; ;@%;%'" << std::endl;
	outFile << "         `:%;.  :;bd%;          %;@%;'" << std::endl;
	outFile << "           `@%:.  :;%.         ;@@%;'" << std::endl;
	outFile << "             `@%.  `;@%.      ;@@%;" << std::endl;
	outFile << "               `@%%. `@%%    ;@@%;" << std::endl;
	outFile << "                 ;@%. :@%%  %@@%;" << std::endl;
	outFile << "                   %@bd%%%bd%%:;" << std::endl;
	outFile << "                     #@%%%%%:;;" << std::endl;
	outFile << "                     %@@%%%::;" << std::endl;
	outFile << "                     %@@@%(o);  . '" << std::endl;
	outFile << "                     %@@@o%;:(.,'" << std::endl;
	outFile << "                 `.. %@@@o%::;" << std::endl;
	outFile << "                    `)@@@o%::;" << std::endl;
	outFile << "                     %@@(o)::;" << std::endl;
	outFile << "                    .%@@@@%::;" << std::endl;
	outFile << "                    ;%@@@@%::;." << std::endl;
	outFile << "                   ;%@@@@%%:;;;." << std::endl;
	outFile << "               ...;%@@@@@%%:;;;;,.." << std::endl;
	outFile << std::endl;
	outFile << std::endl;
	outFile << "		                                   .;" << std::endl;
	outFile << "      .              .              ;%     ;;" << std::endl;
	outFile << "        ,           ,                :;%  %;" << std::endl;
	outFile << "         :         ;                   :;%;'     .," << std::endl;
	outFile << ",.        %;     %;            ;        %;'    ,;" << std::endl;
	outFile << "  ;       ;%;  %%;        ,     %;    ;%;    ,%'" << std::endl;
	outFile << "   %;       %;%;      ,  ;       %;  ;%;   ,%;'" << std::endl;
	outFile << "    ;%;      %;        ;%;        % ;%;  ,%;'" << std::endl;
	outFile << "     `%;.     ;%;     %;'         `;%%;.%;'" << std::endl;
	outFile << "      `:;%.    ;%%. %@;        %; ;@%;%'" << std::endl;
	outFile << "         `:%;.  :;bd%;          %;@%;'" << std::endl;
	outFile << "           `@%:.  :;%.         ;@@%;'" << std::endl;
	outFile << "             `@%.  `;@%.      ;@@%;" << std::endl;
	outFile << "               `@%%. `@%%    ;@@%;" << std::endl;
	outFile << "                 ;@%. :@%%  %@@%;" << std::endl;
	outFile << "                   %@bd%%%bd%%:;" << std::endl;
	outFile << "                     #@%%%%%:;;" << std::endl;
	outFile << "                     %@@%%%::;" << std::endl;
	outFile << "                     %@@@%(o);  . '" << std::endl;
	outFile << "                     %@@@o%;:(.,'" << std::endl;
	outFile << "                 `.. %@@@o%::;" << std::endl;
	outFile << "                    `)@@@o%::;" << std::endl;
	outFile << "                     %@@(o)::;" << std::endl;
	outFile << "                    .%@@@@%::;" << std::endl;
	outFile << "                    ;%@@@@%::;." << std::endl;
	outFile << "                   ;%@@@@%%:;;;." << std::endl;
	outFile << "               ...;%@@@@@%%:;;;;,.." << std::endl;
	outFile << std::endl;
}