/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_placeholder.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:28:56 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/09 19:27:48 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_print_placeholder_free(t_placeholder *analized_placeholder,
										int all)
{
	if (all)
		free(analized_placeholder->data);
	free(analized_placeholder);
	return (-1);
}

int	ft_printf_print_placeholder(char const **str, va_list *argptr)
{
	t_placeholder	*analized_placeholder;
	size_t			len;

	analized_placeholder = ft_printf_analysis(str, argptr);
	if (!analized_placeholder)
		return (-1);
	if (ft_printf_print_plus_space(analized_placeholder))
		return (ft_printf_print_placeholder_free(analized_placeholder, 0));
	if (ft_printf_print_precision(analized_placeholder))
		return (ft_printf_print_placeholder_free(analized_placeholder, 0));
	if (analized_placeholder->width >= 1)
	{
		if (ft_prinft_print_width(analized_placeholder))
			return (ft_printf_print_placeholder_free(analized_placeholder, 1));
	}
	len = ft_strlen(analized_placeholder->data);
	if (analized_placeholder->type == 'c')
		len = ft_printf_print_placeholder_type_c(analized_placeholder);
	else
		ft_putstr_fd(analized_placeholder->data, 1);
	ft_printf_print_placeholder_free(analized_placeholder, 1);
	return (len);
}

int	ft_printf_print_placeholder_type_c(t_placeholder *placeholder)
{
	char	*str;
	size_t	index;
	int		ret;

	index = 0;
	ret = 0;
	str = placeholder->data;
	while (str[index])
	{
		if (str[index] == 'N' && str[index + 1] == 'U' && str[index + 2] == 'L')
		{
			write(1, "\0", 1);
			index += 3;
		}
		else
		{
			write(1, &str[index], 1);
			index++;
		}
		ret++;
	}
	return (ret);
}
