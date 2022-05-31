/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:03:19 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/31 18:01:38 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_divider(char *token, int all_dividers)
{
	int	length;

	length = ft_strlen(token);
	if (all_dividers)
	{
		if (length == 1 && (token[0] == '|' || token[0] == '>'
				|| token[0] == '<'))
			return (1);
		else if (length == 2 && (ft_strncmp(token, ">>", 2) || ft_strncmp(token,
						"<<", 2)))
			return (1);
	}
	else
	{
		if (length == 1 && (token[0] == '>' || token[0] == '<'))
			return (1);
		else if (length == 2 && (ft_strncmp(token, ">>", 2) == 1
					|| ft_strncmp(token, "<<", 2) == 1))
			return (1);
	}
	return (0);
}

int	remove_quotes(char **str, char *start, char *end)
{
	char	*new_string;
	char	*copy_str;
	char	*copy;

	new_string = (char *)ft_calloc(ft_strlen(*str) - 1, sizeof(char));
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
	return (-2);
}

void	reset_vars(int *end, int *start, char *type)
{
	*end = -1;
	*start = -1;
	*type = '\0';
}

void	parse_quotes(char **str)
{
	int		start;
	int		end;
	int		index;
	char	type;

	index = 0;
	if (ft_strchr(*str, '\"') == NULL && ft_strchr(*str, '\'') == NULL)
		return ;
	reset_vars(&end, &start, &type);
	while ((*str)[index])
	{
		if (type && type == (*str)[index])
			end = index;
		if (((*str)[index] == '\'' || (*str)[index] == '\"') && type == '\0')
		{
			type = (*str)[index];
			start = index;
		}
		if (end != -1 && start != -1)
		{
			index += remove_quotes(str, *str + start, *str + end);
			reset_vars(&end, &start, &type);
		}
		index++;
	}
}

t_command	*create_command(char **start, int number)
{
	char		**args;
	int			index;
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	args = (char **)ft_calloc(number + 1, sizeof(char *));
	index = 0;
	while (index != number)
	{
		args[index] = ft_strdup(start[index]);
		parse_quotes(&args[index]);
		index++;
	}
	command->args = args;
	command->number_of_arguments = number;
	return (command);
}
