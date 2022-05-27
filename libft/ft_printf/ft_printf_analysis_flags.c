/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_analysis_flags.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:05:43 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/05 20:41:07 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prinft_analysis_flag_aling(const char **str)
{
	size_t	index;

	index = 0;
	while (ft_isset(*(*str + index), "-+ 0#"))
	{
		if (**str == '-')
			return (1);
		index++;
	}
	return (0);
}

int	ft_prinft_analysis_flag_zeropadding(const char **str)
{
	size_t	index;

	index = 0;
	while (ft_isset(*(*str + index), "-+ 0#"))
	{
		if (**str == '0')
			return (1);
		index++;
	}
	return (0);
}

int	ft_prinft_analysis_flag_space(const char **str)
{
	size_t	index;

	index = 0;
	while (ft_isset(*(*str + index), "-+ 0#"))
	{
		if (**str == ' ')
			return (1);
		index++;
	}
	return (0);
}

int	ft_prinft_analysis_flag_plus(const char **str)
{
	size_t	index;

	index = 0;
	while (ft_isset(*(*str + index), "-+ 0#"))
	{
		if (**str == '+')
			return (1);
		index++;
	}
	return (0);
}

int	ft_prinft_analysis_flag_hashtag(const char **str)
{
	size_t	index;

	index = 0;
	while (ft_isset(*(*str + index), "-+ 0#"))
	{
		if (**str == '#')
			return (1);
		index++;
	}
	return (0);
}
