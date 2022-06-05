/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:30 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/05 16:42:01 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*parse_quotes(char **str, char **env);

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

t_command	*create_command(char **start, int number, char **env)
{
	char		**args;
	int			index;
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	args = (char **)ft_calloc(number + 1, sizeof(char *));
	if (!args)
		return (NULL);
	index = 0;
	while (index != number)
	{
		args[index] = ft_strdup(start[index]);
		if (!parse_quotes(&args[index], env))
			return (NULL);
		index++;
	}
	command->args = args;
	command->number_of_arguments = number;
	return (command);
}

t_command	*get_command(t_command_table **table, char ***lexer)
{
	char		**start;
	int			args_count;
	t_command	*command;

	if (token_is_pipe(**lexer))
		(*lexer)++;
	start = *lexer;
	args_count = 1;
	(*lexer)++;
	while (**lexer && !token_is_divider(**lexer))
	{
		args_count++;
		(*lexer)++;
	}
	command = create_command(start, args_count, *(*table)->env);
	if (!command)
		return (NULL);
	join_to_command_array(*table, command);
	return (command);
}
