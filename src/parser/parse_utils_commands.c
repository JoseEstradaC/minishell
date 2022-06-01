/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/01 16:23:23 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			token_is_divider(char *token, int all_dividers);
char		*parse_quotes(char **str);

void	join_to_command_array(t_command_table *table, t_command *command_new)
{
	t_command	**temp;
	int			index;

	temp = (t_command **)ft_calloc(sizeof(t_command *),
			table->number_of_commands + 1);
	index = 0;
	while (table->number_of_commands != index)
	{
		temp[index] = table->commands[index];
		index++;
	}
	temp[index] = command_new;
	free(table->commands);
	table->commands = temp;
	table->number_of_commands++;
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
		if (ft_strchr(args[index], '\"') != NULL || ft_strchr(args[index],
				'\'') != NULL)
		{
			if (!parse_quotes(&args[index]))
				return (NULL);
		}
		index++;
	}
	command->args = args;
	command->number_of_arguments = number;
	return (command);
}

t_command	*fill_table_with_commands(t_command_table **table, char ***lexer)
{
	char		**start;
	int			args_count;
	t_command	*command;

	while (**lexer && !token_is_divider(**lexer, 0))
	{
		start = *lexer;
		args_count = 1;
		(*lexer)++;
		while (**lexer && !token_is_divider(**lexer, 1))
		{
			args_count++;
			(*lexer)++;
		}
		command = create_command(start, args_count);
		if (!command)
			return (NULL);
		join_to_command_array(*table, command);
		if (!(**lexer))
			break ;
		(*lexer)++;
	}
	(*lexer)--;
	return (command);
}
