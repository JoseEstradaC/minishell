/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:12:20 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/11 18:43:46 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	index;

	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		index = 0;
		while (index != n)
		{
			((char *)dst)[index] = ((char *)src)[index];
			index++;
		}
	}
	else
	{
		index = n;
		while (index != 0)
		{
			index--;
			((char *)dst)[index] = ((char *)src)[index];
		}
	}
	return (dst);
}
