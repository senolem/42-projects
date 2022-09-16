/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:41 by albaur            #+#    #+#             */
/*   Updated: 2022/09/16 15:19:18 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConversion.hpp"

ScalarConversion::ScalarConversion(void)
{
	this->type = TypeInvalid;
}

ScalarConversion::ScalarConversion(ScalarConversion const &src)
{
	*this = src;
}

ScalarConversion::~ScalarConversion(void)
{

}

ScalarConversion &ScalarConversion::operator=(ScalarConversion const &src)
{
	(void)src;
	return (*this);
}

void	ScalarConversion::analyseInput(std::string input)
{
	size_t	i = 0;
	size_t	len = input.length();
	bool	neg = false;
	long	nb = 0;
	
	this->input = input;
	if (len == 0)
	{
		this->type = TypeInvalid;
		return ;
	}
	else if (funHandler())
		return ;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '-')
		{
			if (i == 0 && (input[i + 1] >= '0' && input[i + 1] <= '9'))
			{
				neg = true;
				continue ;
			}
			i = 0;
			break ;
		}
		if (!std::isdigit(input[i]))
		{
			i = 0;
			break ;
		}
		nb *= 10;
		nb += input[i] - '0';
		if ((neg && nb - 1 > std::numeric_limits<int>::max())
			|| nb > std::numeric_limits<int>::max())
		{
			i = 0;
			break ;
		}
	}
	if (i == len)
	{
		this->type = TypeInt;
		return ;
	}
	else if (decimalHandler())
		return ;
	else if (input.length() == 1 && input.at(0) >= 32 && input.at(0) <= 126)
	{
		this->type = TypeChar;
		return ;
	}
	this->type = TypeInvalid;
}

bool	ScalarConversion::funHandler(void)
{
	if (this->input == "-inff")
		this->type = TypeFunNegativeInfFloat;
	else if (this->input == "+inff")
		this->type = TypeFunInfFloat;
	else if (this->input == "nanf")
		this->type = TypeFunNanFloat;
	else if (this->input == "-inf")
		this->type = TypeFunNegativeInf;
	else if (this->input == "+inf")
		this->type = TypeFunInf;
	else if (this->input == "nan")
		this->type = TypeFunNan;
	if (this->type >= TypeFunNegativeInfFloat && this->type <= TypeFunNan)
		return (true);
	else
		return (false);
}

bool	ScalarConversion::decimalHandler(void)
{
	size_t	i = 0;
	size_t	len = 0;
	char	*decimal;
	double	nb = std::strtod(this->input.c_str(), &decimal);

	if (this->input != decimal && nb != HUGE_VAL)
	{
		if ((this->input.at(this->input.length() - 1) == 'f' && nb <= std::numeric_limits<float>::max() && nb >= -std::numeric_limits<float>::max())
				|| (nb <= std::numeric_limits<double>::max() && nb >= -std::numeric_limits<double>::max()))
		{
			if (this->input[0] == '-' && this->input.length() >= 2)
				++i;
			if (this->input[i] == '.' && (this->input[i + 1] == 'f'
					|| this->input.at(i + 1) == '\0'))
				return (false);
			while (this->input[i] == '.' || std::isdigit(this->input[i]))
			{
				if (this->input[i] == '.')
					++len;
				if (len > 1)
					return (false);
				++i;
			}
			if (!this->input[i])
			{
				this->type = TypeDouble;
				return (true);
			}
			else if (this->input[i] == 'f' && !this->input[i + 1] && len <= 1)
			{
				this->type = TypeFloat;
				return (true);
			}
		}
	}
	return (false);
}

std::string	ScalarConversion::printDecimal(double nb) const
{
	if (nb - static_cast<int>(nb) == 0.0)
		return (".0");
	return ("");
}

void	ScalarConversion::printInput(void) const
{
	switch (this->type)
	{
		case TypeChar:
			std::cout << "Detected type: char" << std::endl;
			this->printType(this->input.at(0));
			break;
		case TypeInt:
			std::cout << "Detected type: int" << std::endl;
			this->printType(atoi(this->input.c_str()));
			break;
		case TypeFloat:
			std::cout << "Detected type: float" << std::endl;
			this->printType(std::atof(this->input.c_str()));
			break;
		case TypeDouble:
			std::cout << "Detected type: double" << std::endl;
			this->printType(std::strtod(this->input.c_str(), NULL));
			break;
		case TypeFunNegativeInfFloat:
			std::cout << "Detected type: -inff" << std::endl;
			this->printType(-(std::numeric_limits<float>::infinity()));
			break;
		case TypeFunInfFloat:
			std::cout << "Detected type: +inff" << std::endl;
			this->printType(std::numeric_limits<float>::infinity());
			break;
		case TypeFunNanFloat:
			std::cout << "Detected type: nanf" << std::endl;
			this->printType(std::numeric_limits<float>::quiet_NaN());
			break;
		case TypeFunNegativeInf:
			std::cout << "Detected type: -inf" << std::endl;
			this->printType(-(std::numeric_limits<double>::infinity()));
			break;
		case TypeFunInf:
			std::cout << "Detected type: +inf" << std::endl;
			this->printType(std::numeric_limits<double>::infinity());
			break;
		case TypeFunNan:
			std::cout << "Detected type: nan" << std::endl;
			this->printType(std::numeric_limits<double>::quiet_NaN());
			break;
		case TypeInvalid:
			std::cout << "Error : Invalid input. Only one argument is accepted." << std::endl;
			break;
		default:
			std::cout << "Error : Unknown conversion type." << std::endl;
			break;
	}
}

void	ScalarConversion::printType(char c) const
{
	std::cout << "char: " << c << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void	ScalarConversion::printType(int i) const
{
	std::cout << "char: ";
	if (i > std::numeric_limits<char>::max())
		std::cout << "Overflow" << std::endl;
	else if (i < std::numeric_limits<char>::min())
		std::cout << "Underflow" << std::endl;
	else if (i >= 32 && i <= 126)
		std::cout << static_cast<char>(i) << std::endl;
	else if ((i >= 0 && i <= 32) || i == 127)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "impossible" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

void	ScalarConversion::printType(float f) const
{
	std::cout << "char: ";
	if (f > std::numeric_limits<char>::max())
		std::cout << "Overflow" << std::endl;
	else if (f < std::numeric_limits<char>::min())
		std::cout << "Underflow" << std::endl;
	else if (f >= 32 && f <= 126)
		std::cout << static_cast<char>(f) << std::endl;
	else if ((f >= 0 && f <= 32) || f == 127)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "impossible" << std::endl;
	std::cout << "int: ";
	if (f > std::numeric_limits<int>::max())
		std::cout << "Overflow" << std::endl;
	else if (f < std::numeric_limits<int>::min())
		std::cout << "Underflow" << std::endl;
	else if (f <= std::numeric_limits<int>::max() && f >= std::numeric_limits<int>::min())
		std::cout << static_cast<int>(f);
	else
		std::cout << "impossible" << std::endl;
	std::cout << "float: " << f << printDecimal(static_cast<double>(f)) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(f) << printDecimal(static_cast<double>(f)) << std::endl;
}

void	ScalarConversion::printType(double d) const
{
	std::cout << "char: ";
	if (d > std::numeric_limits<char>::max())
		std::cout << "Overflow" << std::endl;
	else if (d < std::numeric_limits<char>::min())
		std::cout << "Underflow" << std::endl;
	else if (d >= 32 && d <= 126)
		std::cout << static_cast<char>(d) << std::endl;
	else if ((d >= 0 && d < 32) || d == 127)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "impossible" << std::endl;
	std::cout << "int: ";
	if (d > std::numeric_limits<int>::max())
		std::cout << "Overflow" << std::endl;
	else if (d < std::numeric_limits<int>::min())
		std::cout << "Underflow" << std::endl;
	else if (d <= std::numeric_limits<int>::max() && d >= std::numeric_limits<int>::min())
		std::cout << static_cast<int>(d) << std::endl;
	else
		std::cout << "impossible" << std::endl;
	std::cout << "float: ";
	if (d > std::numeric_limits<float>::max())
		std::cout << "Overflow" << std::endl;
	else if (d < -std::numeric_limits<float>::max())
		std::cout << "Underflow" << std::endl;
	else
		std::cout << static_cast<float>(d) << printDecimal(d) << "f" << std::endl;
	std::cout << "double: " << d << printDecimal(d) << std::endl;
}
