/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:40:10 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/31 14:38:14 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_free(char **split)
{
	char	**temp;

	temp = split;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(*split);
	free(temp);
}
