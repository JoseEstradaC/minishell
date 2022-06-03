/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:03:19 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/03 12:04:31 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_pipe(char *token)
{
	int	length;

	length = ft_strlen(token);
	if (length == 1 && token[0] == '|')
		return (1);
	return (0);
}

int	token_is_input(char *token)
{
	int	length;

	length = ft_strlen(token);
	if (length == 1 && token[0] == '<')
		return (1);
	return (0);
}

int	token_is_input_append(char *token)
{
	int	length;

	length = ft_strlen(token);
	if (length == 2 && !ft_strncmp(token, "<<", 2))
		return (1);
	return (0);
}

int	token_is_output(char *token)
{
	int	length;

	length = ft_strlen(token);
	if (length == 1 && token[0] == '>')
		return (1);
	return (0);
}

int	token_is_output_append(char *token)
{
	int	length;

	length = ft_strlen(token);
	if (length == 2 && !ft_strncmp(token, ">>", 2))
		return (1);
	return (0);
}
