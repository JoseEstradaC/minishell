/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:03:19 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/04 19:45:11 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_divider(char *token)
{
	if (!token || !*token)
		return (1);
	if (token_is_pipe(token) || token_is_input(token)
		|| token_is_input_append(token) || token_is_output(token)
		|| token_is_output_append(token))
		return (1);
	return (0);
}

int	token_is_redirrect(char *token)
{
	if (token_is_input(token) || token_is_input_append(token)
		|| token_is_output(token) || token_is_output_append(token))
		return (1);
	return (0);
}

void	free_table(t_command_table *table)
{
	int	index;

	index = table->number_of_commands;
	while (index > 0)
	{
		index--;
		ft_split_free(table->commands[index]->args);
		free(table->commands[index]);
	}
	free(table->commands);
	free(table);
}
