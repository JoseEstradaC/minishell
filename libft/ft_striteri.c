/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:54:51 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/23 20:39:25 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	ssize_t	index;

	if (!s || !f)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		f(index, s + index);
		index++;
	}
}
