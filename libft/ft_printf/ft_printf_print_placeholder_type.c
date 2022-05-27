/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_placeholder_type.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:10:18 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/09 19:29:07 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_print_plus_space(t_placeholder *analized_placeholder)
{
	char	*temp;

	if (analized_placeholder->type == 's')
		return (0);
	if ((analized_placeholder->space || analized_placeholder->plus)
		&& analized_placeholder->data[0] != '-')
	{
		if (analized_placeholder->space)
			temp = ft_strjoin(" ", analized_placeholder->data);
		if (analized_placeholder->plus)
			temp = ft_strjoin("+", analized_placeholder->data);
		free(analized_placeholder->data);
		if (!temp)
			return (1);
		analized_placeholder->data = temp;
	}
	return (0);
}

int	ft_printf_print_precision(t_placeholder *analized_placeholder)
{
	char	*temp;

	if (analized_placeholder->type != 's')
		return (0);
	if (analized_placeholder->precision >= 1)
	{
		temp = ft_substr(analized_placeholder->data, 0,
				analized_placeholder->precision - 1);
		free(analized_placeholder->data);
		if (!temp)
			return (1);
		analized_placeholder->data = temp;
	}
	return (0);
}

/*
**
**	Print left or right alingment with 0 or space padding
**
*/

int	ft_prinft_print_width(t_placeholder *analized_placeholder)
{
	char	c;
	char	*padding;
	size_t	len;

	c = ' ';
	if (analized_placeholder->zeropadding == 1)
		c = '0';
	len = ft_printf_print_width_get(analized_placeholder);
	padding = (char *)ft_calloc(sizeof(char), len + 1);
	if (!padding)
		return (1);
	ft_memset(padding, c, len);
	return (ft_printf_placeholder_width_write(analized_placeholder, padding));
}

size_t	ft_printf_print_width_get(t_placeholder *analized_placeholder)
{
	size_t	len;
	char	*str;

	str = analized_placeholder->data;
	len = ft_strlen(str);
	if (analized_placeholder->type == 'c')
	{
		if (str[0] == 'N' && str[1] == 'U' && str[2] == 'L')
			len -= 2;
	}
	if (analized_placeholder->width >= len)
		len = analized_placeholder->width - len;
	else
		len = 0;
	return (len);
}
