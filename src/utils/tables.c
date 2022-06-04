/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:34 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/04 20:32:26 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_table(char **table)
{
	int	len;

	len = 0;
	while (table && table[len])
		len++;
	return (len);
}

// Join a + b (pointers to a null-terminated array of strings)
char	**join_split(char **a, char **b)
{
	int		size;
	char	**ret;
	int		i;
	int		j;

	size = len_table(a) + len_table(b) + 1;
	ret = (char **)malloc(size * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (a && a[++i])
		ret[i] = ft_strdup(a[i]);
	j = 0;
	while (b && b[j])
		ret[i++] = ft_strdup(b[j++]);
	ret[i] = NULL;
	return (ret);
}

static int	get_new_size(char *str, char ***table)
{
	int		count;
	char	**ptr;
	int		size;

	count = 0;
	ptr = *table;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, str, ft_strlen(str))
			&& (*ptr)[ft_strlen(str)] == '=')
			count++;
		ptr++;
	}
	size = len_table(*table) - count;
	if (size <= 0)
	{
		free(*table);
		*table = NULL;
		return (0);
	}
	return (size);
}

int	del_str_split(char *str, char ***table)
{
	int		size;
	char	**ptr;
	char	**new_tab;
	int		i;

	size = get_new_size(str, table);
	if (!size)
		return (0);
	new_tab = (char **)malloc(sizeof(char *) * (size + 1));
	ptr = *table;
	i = 0;
	while (*ptr)
	{
		if (!(!ft_strncmp(*ptr, str, ft_strlen(str))
				&& (*ptr)[ft_strlen(str)] == '='))
			new_tab[i++] = ft_strdup(*ptr);
		ptr++;
	}
	new_tab[i] = NULL;
	ft_split_free(*table);
	*table = new_tab;
	return (0);
}
