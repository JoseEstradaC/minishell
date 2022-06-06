/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:40:10 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 22:29:54 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_free(char **split)
{
	char	**temp;

	if (!split)
		return ;
	temp = split;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(*split);
	free(temp);
}
