/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:53:19 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/08 19:46:40 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *str, ...)
{
	va_list	argptr;
	int		total_print;

	va_start(argptr, str);
	total_print = ft_printf_print(&str, &argptr);
	va_end(argptr);
	return (total_print);
}

int	ft_printf_print(char const **str, va_list *argptr)
{
	int	total_print;
	int	temp;

	total_print = 0;
	while (**str)
	{
		if (**str == '%')
		{
			temp = ft_printf_found_placeholder(str, argptr);
			if (temp == -1)
				return (-1);
			total_print += temp;
			continue ;
		}
		ft_putchar_fd(**str, 1);
		total_print++;
		(*str)++;
	}
	return (total_print);
}

int	ft_printf_found_placeholder(char const **str, va_list *argptr)
{
	int	total_print;
	int	temp;

	total_print = 0;
	if (*((*str) + 1) == '%')
	{
		ft_putchar_fd('%', 1);
		total_print++;
		*str += 2;
		return (total_print);
	}
	(*str)++;
	temp = ft_printf_print_placeholder(str, argptr);
	(*str)++;
	if (temp == -1)
		return (-1);
	total_print += temp;
	return (total_print);
}
