/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_occurrences.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:41:36 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/27 17:46:43 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_occurrences(char *str, char c)
{
	int	index;

	index = 0;
	while (*str)
	{
		if (*str == c)
			index++;
		str++;
	}
	return (index);
}
