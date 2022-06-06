/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:52:47 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/06 13:32:48 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char **str, char *start, char *end, int *index)
{
	char	*new_string;
	char	*copy_str;
	char	*copy;

	new_string = (char *)ft_calloc(ft_strlen(*str) - 1, sizeof(char));
	if (!new_string)
		return (NULL);
	copy_str = *str;
	copy = new_string;
	while (**str)
	{
		if (!(*str == start || *str == end))
		{
			*new_string = **str;
			new_string++;
		}
		(*str)++;
	}
	free(copy_str);
	*str = copy;
	(*index) += -2;
	return (copy_str);
}

void	reset_vars(int *end, int *start, char *type)
{
	*end = -1;
	*start = -1;
	*type = '\0';
}

void	parse_qoutes_start(char **str, int *index, char *type, int *start)
{
	if (((*str)[*index] == '\'' || (*str)[*index] == '\"') && *type == '\0')
	{
		*type = (*str)[*index];
		*start = *index;
	}
}

char	*expand_var(char **s, int *index, char **env)
{
	int		start;
	int		end;
	char	*v;
	char	*ret;
	char	*e;

	start = *index;
	end = start + 1;
	while ((*s)[end] && (ft_isalnum((*s)[end]) || ft_isset((*s)[end], "_?")))
		end++;
	v = strrange(*s, start, end);
	if (!v)
		return (NULL);
	e = get_env_value(v, env);
	ret = (char *)ft_calloc(1, ft_strlen(*s) - ft_strlen(v) + ft_strlen(e) + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, *s, start + 1);
	ft_strlcpy(ret + start, e, ft_strlen(e) + 1);
	ft_strlcpy(ret + start + ft_strlen(e), *s + end, end - ft_strlen(*s));
	free(v);
	free(*s);
	*index = *index + ft_strlen(e) - 1;
	*s = ret;
	return (ret);
}

char	*parse_quotes(char **str, char **env)
{
	int		start;
	int		end;
	int		index;
	char	type;

	index = 0;
	reset_vars(&end, &start, &type);
	while ((*str)[index])
	{
		if ((type == '\0' || type == '\"') && (*str)[index] == '$')
			if (!expand_var(str, &index, env))
				return (NULL);
		if (type && type == (*str)[index])
			end = index;
		parse_qoutes_start(str, &index, &type, &start);
		if (end != -1 && start != -1)
		{
			if (!remove_quotes(str, *str + start, *str + end, &index))
				return (NULL);
			reset_vars(&end, &start, &type);
		}
		index++;
	}
	return (*str);
}
