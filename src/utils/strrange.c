/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrange.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:21:19 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/05 17:29:12 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strrange(char *str, int start, int end)
{
	char	*ret;

	ret = (char *)ft_calloc(sizeof(char), (end - start) + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str + start + 1, end - start);
	return (ret);
}
