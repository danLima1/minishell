/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:47:29 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/23 08:27:10 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_putchar(int c);

int	ft_putstr(char *s);

int	ft_printf(const char *fmt, ...);

int	printhex(unsigned long int nbr, unsigned int base, char *xcase);

int	ft_putnbr(int n);

int	ft_u_putnbr(unsigned int n);

int	ft_putptr(unsigned long int ptr);

#endif
