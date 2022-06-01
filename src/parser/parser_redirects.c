/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:28:13 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/01 19:14:32 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		token_is_divider(char *token, int all_dividers);
char	*parse_quotes(char **str);

char	*fill_redirects(t_command_table *table, char ***lexer)
{
	char	*file;

	file = **lexer;
	if (**(*lexer - 1) == '>')
	{
		table->out_file = file;
		table->out_type = *(*lexer - 1);
	}
	else
	{
		table->input_file = file;
		table->input_type = *(*lexer - 1);
	}
	if (ft_strchr(file, '\"') != NULL || ft_strchr(file, '\'') != NULL)
	{
		if (!parse_quotes(&file))
			return (NULL);
	}
	return (file);
}

char	*fill_table_with_redirects(t_command_table *table, char ***lexer)
{
	while (**lexer && token_is_divider(**lexer, 0))
	{
		(*lexer)++;
		if (!(**lexer))
		{
			ft_putstr_fd("Redirrect not defined\n", 2);
			return (NULL);
		}
		if (!fill_redirects(table, lexer))
			return (NULL);
		(*lexer)++;
	}
	return (*(*lexer - 1));
}
