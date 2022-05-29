/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:33 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/29 17:42:04 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(t_command_table *table)
{
	int	index;

	index = table->number_of_commands;
	while (index > 0)
	{
		index--;
		free(table->commands[index]);
	}
	free(table->commands);
	free(table);
}

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

t_command_table	*parser(char **lexer)
{
	t_command_table	*table;
	t_command		*command;

	if (ft_split_count(lexer) < 1)
		return (NULL);
	table = (t_command_table *)ft_calloc(1, sizeof(t_command_table));
	while (*lexer && !ft_isset(**lexer, "><|"))
	{
		command = (t_command *)ft_calloc(1, sizeof(t_command));
		command->args = lexer;
		command->number_of_arguments = 1;
		lexer++;
		while (*lexer && !ft_isset(**lexer, "><|"))
		{
			command->number_of_arguments++;
			lexer++;
		}
		join_to_command_array(table, command);
		if (!(*lexer))
			break ;
		lexer++;
	}
	return (table);
}
