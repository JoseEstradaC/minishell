/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:12:20 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/24 19:39:36 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if ((size >= __SIZE_MAX__ && num > 1) || (num >= __SIZE_MAX__ && size > 1))
		return (NULL);
	ptr = malloc(num * size);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, num * size);
	return (ptr);
}
