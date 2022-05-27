/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_placeholder_utils.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:59:09 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/06 02:54:03 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_check_fixminus(t_placeholder *analized_placeholder)
{
	if (analized_placeholder->type == 'i' || analized_placeholder->type == 'd')
	{
		if (analized_placeholder->data[0] == '-')
			return (1);
	}
	return (0);
}

int	ft_printf_placeholder_width_write(t_placeholder *placeholder,
										char *padding)
{
	int		fix_minus;
	char	*temp;
	char	*temp1;

	fix_minus = ft_printf_check_fixminus(placeholder);
	if (placeholder->aling == 0)
		temp = ft_strjoin(padding, placeholder->data + fix_minus);
	else
		temp = ft_strjoin(placeholder->data + fix_minus, padding);
	free(padding);
	if (!temp)
		return (1);
	free(placeholder->data);
	if (fix_minus)
	{
		temp1 = ft_strjoin("-", temp);
		free(temp);
		if (!temp1)
			return (1);
		temp = temp1;
	}
	placeholder->data = temp;
	return (0);
}
