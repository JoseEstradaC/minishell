/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:27:22 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/28 18:30:26 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_split_count(char **split)
{
	int	size;

	size = 0;
	while (*split)
	{
		size++;
		split++;
	}
	return (size);
}
