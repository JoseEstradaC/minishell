/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:17:56 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/09 19:59:41 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 
** ORDER
** 
** aling, *plus, *space, zeropadding, *hashtag, width, *precision, *type
** ------------
** 
** data  		-> data to print
** type			-> % value
** 
** '0' flag ignored with '-' flag
** '0' flag ignored with precision
** ' ' flag ignored with '+'
** 
** aling(-) -> 0 default (right-align), 1(Left-align)
** space(' ') -> 0 default, 1 (in d or i) if is posivite print ' '
** plus('+') -> 0 default, 1 (in d or i) if is posivite print '+'
** zeropadding(0) -> 0 default, 1 zero with padding
** hashtag(#) -> 0 default, 1 (in x or X) 0x or 0X suffix
** width({INT}) -> 0 default, >0 amount of space (Depend of aling)
** precision(.{INT}) -> 0 default, >({num} - 1) in s amount of s number to print
*/

t_placeholder	*ft_printf_analysis(const char **str, va_list *argptr)
{
	t_placeholder	*placeholder;

	placeholder = (t_placeholder *)malloc(sizeof(t_placeholder));
	if (!placeholder)
		return (NULL);
	placeholder->aling = ft_prinft_analysis_flag_aling(str);
	placeholder->plus = ft_prinft_analysis_flag_plus(str);
	placeholder->space = ft_prinft_analysis_flag_space(str);
	placeholder->zeropadding = ft_prinft_analysis_flag_zeropadding(str);
	placeholder->hashtag = ft_prinft_analysis_flag_hashtag(str);
	*str += placeholder->aling + placeholder->plus + placeholder->space
		+ placeholder->zeropadding + placeholder->hashtag;
	placeholder->width = ft_prinft_analysis_flag_width(str);
	placeholder->precision = ft_prinft_analysis_flag_precision(str);
	placeholder->type = **str;
	placeholder->data = ft_printf_analysis_data_type(placeholder->type, argptr,
			placeholder);
	if (!placeholder->data)
	{
		free(placeholder);
		return (NULL);
	}
	ft_prinft_analysis_precision_to_padding(placeholder);
	return (placeholder);
}

char	*ft_printf_analysis_data_type(char type, va_list *argptr,
		t_placeholder *placeholder)
{
	if (type == 'c')
		return (ft_printf_analysis_data_c(argptr));
	if (type == 's')
		return (ft_printf_analysis_data_s(argptr, placeholder->space));
	if (type == 'p')
		return (ft_printf_transform_ptr_to_hex(va_arg(*argptr, void *)));
	if (type == 'd' || type == 'i')
		return (ft_itoa(va_arg(*argptr, int)));
	if (type == 'u')
		return (ft_printf_transform_uint(va_arg(*argptr, unsigned int)));
	if (type == 'x')
		return (ft_printf_transform_uin_to_hex(va_arg(*argptr, unsigned int), 0,
				placeholder->hashtag));
	if (type == 'X')
		return (ft_printf_transform_uin_to_hex(va_arg(*argptr, unsigned int), 1,
				placeholder->hashtag));
	return (NULL);
}

char	*ft_printf_analysis_data_s(va_list *argptr, size_t space)
{
	char	*data;
	char	*ret;

	data = va_arg(*argptr, char *);
	if (!data && space == 0)
		ret = (ft_strdup("(null)"));
	else if ((!data || !(*data)) && space == 1)
		ret = ft_calloc(sizeof(char), 1);
	else
		ret = ft_strdup(data);
	return (ret);
}

char	*ft_printf_analysis_data_c(va_list *argptr)
{
	char	*ret;
	int		data;

	data = va_arg(*argptr, int);
	if (data == 0)
	{
		ret = ft_calloc(sizeof(char *), 4);
		if (!ret)
			return (NULL);
		ret[0] = 'N';
		ret[1] = 'U';
		ret[2] = 'L';
		return (ret);
	}
	else
	{
		ret = ft_calloc(sizeof(char *), 2);
		if (!ret)
			return (NULL);
		ret[0] = (char)data;
	}
	return (ret);
}
