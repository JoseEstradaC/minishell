/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 03:40:05 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/20 20:36:26 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	unsigned char	*str;
	size_t			index;

	index = 0;
	str = (unsigned char *)ptr;
	while (index < num)
	{
		if (str[index] == (unsigned char)value)
			return (&str[index]);
		index++;
	}
	return (NULL);
}
