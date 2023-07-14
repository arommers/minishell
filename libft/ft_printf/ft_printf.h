/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 11:23:29 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/04/18 20:40:42 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int	char_decider(int fd, char chr, va_list ap, int i);
int	int_printer(int fd, long n, int i);
int	ft_printf(int fd, const char *s, ...);
int	int_decider(int fd, char chr, va_list ap, int i);
int	p_maker(int fd, va_list ap, int i);
int	s_printer(int fd, char *s, int i);
int	u_maker(int fd, char chr, long n, int i);
int	va_decider(int fd, char chr, va_list ap, int i);
int	x_printer(int fd, char chr, unsigned long x, int i);

#endif