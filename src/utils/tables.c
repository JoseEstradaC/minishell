/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:34 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/01 14:31:56 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	len_table(char **table)
{
	int	len;

	len = 0;
	while (table[len])
		len++;
	return (len);
}

// Join a + b (pointers to a null-terminated array of strings)
char	**join_tables(char **a, char **b)
{
	int		size;
	char	**ret;
	int		i;
	int		j;

	size = len_table(a) + len_table(b) + 1;
	ret = (char **)malloc(size * sizeof(char *));
	i = -1;
	while (a[++i])
		ret[i] = a[i];
	j = 0;
	while (b[j])
		ret[i++] = b[j++];
	ret[i] = NULL;
	return (ret);
}
