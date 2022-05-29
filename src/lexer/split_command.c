/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:07:00 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/29 17:23:30 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_word(const char *s, int *first, int *last, char c)
{
	char	type;

	*first = *last;
	type = '\0';
	while (s[*first] == c && type == '\0')
	{
		if (ft_isset(s[*first], "\"\'"))
			type = s[*first];
		*first = *first + 1;
	}
	*last = *first;
	while ((s[*last] != c || type != '\0') && s[*last] != '\0')
	{
		if (type == s[*last])
			type = '\0';
		else if (ft_isset(s[*last], "\"\'") && type == '\0')
			type = s[*last];
		if (type == '\0' && s[*last] == c)
			break ;
		*last = *last + 1;
	}
}

static int	count_words(const char *s, char c)
{
	int		first;
	int		last;
	size_t	index;

	index = 0;
	first = 0;
	last = 0;
	while (s[last] != '\0')
	{
		next_word(s, &first, &last, c);
		if (first == last)
			break ;
		else
			index++;
	}
	return (index);
}

static void	*free_split(char **ret, size_t total)
{
	if (total == 0)
	{
		free(ret);
		return (NULL);
	}
	while (total != 0)
	{
		free(ret[total]);
		total--;
	}
	free(ret[total]);
	free(ret);
	return (NULL);
}

char	**split_command(char const *s, char c)
{
	int		first;
	int		last;
	char	**ret;
	size_t	index;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!ret)
		return (NULL);
	index = 0;
	first = 0;
	last = 0;
	while (s[last] != '\0')
	{
		next_word(s, &first, &last, c);
		if (first == last)
			break ;
		ret[index] = ft_substr(s, first, last - first);
		if (!ret[index])
			return (free_split(ret, index));
		index++;
	}
	ret[index] = NULL;
	return (ret);
}
