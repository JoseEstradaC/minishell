/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:28:13 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/03 13:51:24 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_quotes(char **str);

char	*fill_redirects(t_command_table *table, char ***lexer)
{
	if (ft_strchr(**lexer, '\"') != NULL || ft_strchr(**lexer, '\'') != NULL)
	{
		if (!parse_quotes(*lexer))
			return (NULL);
	}
	if (**(*lexer - 1) == '>')
	{
		table->out_file = **lexer;
		table->out_type = *(*lexer - 1);
	}
	else
	{
		table->input_file = **lexer;
		table->input_type = *(*lexer - 1);
	}
	return ("a");
}

char	*fill_table_with_redirects(t_command_table *table, char ***lexer)
{
	while (**lexer && token_is_redirrect(**lexer))
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
