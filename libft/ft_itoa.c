/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 05:18:39 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/02 19:52:46 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	isnegative_check(int *isnegative, long *number)
{
	*isnegative = 0;
	if (*number < 0)
	{
		*isnegative = 1;
		*number = *number * -1;
	}
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*str;
	int		isnegative;
	long	number;

	number = n;
	isnegative_check(&isnegative, &number);
	size = ft_intlen(n) + isnegative + 1;
	str = (char *)malloc(sizeof(char) * size);
	size--;
	if (!str)
		return (NULL);
	if (isnegative == 1)
		*str = '-';
	str[size] = '\0';
	size--;
	while (number > 9)
	{
		str[size] = (number % 10) + '0';
		number = number / 10;
		size--;
	}
	str[size] = number + '0';
	return (str);
}
