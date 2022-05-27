/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:44:22 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/04 03:00:12 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_length;
	size_t	dst_length;

	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	while (*dst)
		dst++;
	index = 0;
	if (size <= dst_length)
		return (size + src_length);
	while (src[index] && index < size - dst_length - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (src_length + dst_length);
}
