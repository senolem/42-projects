/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:35:01 by albaur            #+#    #+#             */
/*   Updated: 2022/09/16 14:27:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERSION_HPP
# define SCALARCONVERSION_HPP

# include <iostream>
# include <string>
# include <limits>
# include <cmath>

class ScalarConversion
{
	private:
	std::string	input;
	int			type;

	enum	inputType {
		TypeChar = 0,
		TypeInt,
		TypeFloat,
		TypeDouble,
		TypeFunNegativeInfFloat,
		TypeFunInfFloat,
		TypeFunNanFloat,
		TypeFunNegativeInf,
		TypeFunInf,
		TypeFunNan,
		TypeInvalid
	};

	public:
	ScalarConversion(void);
	ScalarConversion(ScalarConversion const &src);
	~ScalarConversion(void);
	ScalarConversion &operator=(ScalarConversion const &src);

	void		analyseInput(std::string input);
	bool		funHandler(void);
	bool		decimalHandler(void);
	std::string	printDecimal(double nb) const;
	void		printInput(void) const;
	void		printType(char c) const;
	void		printType(int i) const;
	void		printType(float f) const;
	void		printType(double d) const;
};

#endif