/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:52:49 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/04 02:47:04 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(const int n)
{
	size_t	size;
	long	temp;

	temp = n;
	size = 0;
	if (n < 0)
		temp *= -1;
	while (temp > 9)
	{
		temp = temp / 10;
		size++;
	}
	size++;
	return (size);
}

size_t	ft_uintlen(const unsigned int n)
{
	size_t	size;
	long	temp;

	temp = n;
	size = 0;
	while (temp > 9)
	{
		temp = temp / 10;
		size++;
	}
	size++;
	return (size);
}
