/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 04:28:46 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/23 20:56:46 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	size_t	index;
	int		isnegative;
	int		ret;

	index = 0;
	ret = 0;
	isnegative = 1;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			isnegative = -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		ret = ret * 10 + (str[index] - '0');
		index++;
	}
	return (ret * isnegative);
}
