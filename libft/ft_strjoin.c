/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:37:08 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/03 02:22:04 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	index;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	index = 0;
	while (*s1 != '\0')
	{
		str[index] = *s1;
		index++;
		s1++;
	}
	while (*s2 != '\0')
	{
		str[index] = *s2;
		index++;
		s2++;
	}
	str[index] = '\0';
	return (str);
}
