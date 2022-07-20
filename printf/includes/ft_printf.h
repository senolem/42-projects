/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:46:59 by albaur            #+#    #+#             */
/*   Updated: 2022/03/24 15:55:20 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int			ft_printf(const char *str, ...);
int			ft_putstr(char *str);
int			ft_putptr(unsigned long long ptr);
int			ft_putnbr(int nb);
int			ft_putchar(int c);
int			ft_itohex(unsigned int num, const char format);
int			ft_putint_unsigned(unsigned int n);
void		ft_putchar_fd(char c, int fd);
char		*ft_itoa(int n);

#endif