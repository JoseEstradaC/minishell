/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:08:51 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/20 13:08:58 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		str_length;
	char	*str_copy;
	char	*ret;

	str_length = ft_strlen(s);
	str_copy = (char *)malloc(sizeof(char) * (str_length + 1));
	if (!str_copy)
		return (NULL);
	ret = str_copy;
	while (*s != '\0')
	{
		*str_copy = *s;
		s++;
		str_copy++;
	}
	*str_copy = '\0';
	return (ret);
}
