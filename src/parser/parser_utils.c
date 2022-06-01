/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:03:19 by jestrada          #+#    #+#             */
/*   Updated: 2022/06/01 16:31:41 by jestrada         ###   ########.fr       */
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
		else if (length == 2 && (!ft_strncmp(token, ">>", 2)
				|| !ft_strncmp(token, "<<", 2)))
			return (1);
	}
	else
	{
		if (length == 1 && (token[0] == '>' || token[0] == '<'))
			return (1);
		else if (length == 2 && (!ft_strncmp(token, ">>", 2)
				|| !ft_strncmp(token, "<<", 2)))
			return (1);
	}
	return (0);
}
