/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:29:53 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/09 18:57:09 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_transform_uint(unsigned int n)
{
	size_t			size;
	char			*str;
	unsigned int	number;

	number = n;
	size = ft_uintlen(n) + 1;
	str = (char *)ft_calloc(sizeof(char), size);
	if (!str)
		return (NULL);
	size -= 2;
	while (number > 9)
	{
		str[size] = (number % 10) + '0';
		number = number / 10;
		size--;
	}
	str[size] = number + '0';
	return (str);
}

int	ft_recursive_number_ptr(uintptr_t num, char **str)
{
	char	c[2];
	char	*temp;
	int		fail;

	fail = 0;
	if (num > 15)
		fail = ft_recursive_number_ptr(num / 16, str);
	c[0] = "0123456789abcdef"[num % 16];
	c[1] = '\0';
	if (fail == 1)
		return (fail);
	temp = ft_strjoin(*str, c);
	if (!temp)
	{
		free(*str);
		return (1);
	}
	free(*str);
	*str = temp;
	return (0);
}

char	*ft_printf_transform_ptr_to_hex(void *ptr)
{
	uintptr_t	intptr;
	char		*str;

	intptr = (uintptr_t)ptr;
	str = ft_calloc(sizeof(char), 3);
	str[0] = '0';
	str[1] = 'x';
	ft_recursive_number_ptr(intptr, &str);
	if (!str)
		return (NULL);
	return (str);
}

int	ft_recursive_number16(unsigned int num, char **str)
{
	char	c[2];
	char	*temp;
	int		fail;

	fail = 0;
	if (num > 15)
		fail = ft_recursive_number16(num / 16, str);
	c[0] = "0123456789abcdef"[num % 16];
	c[1] = '\0';
	if (fail == 1)
		return (fail);
	temp = ft_strjoin(*str, c);
	if (!temp)
	{
		free(*str);
		return (1);
	}
	free(*str);
	*str = temp;
	return (0);
}

char	*ft_printf_transform_uin_to_hex(unsigned int num, int mayus, int show0x)
{
	char	*str;
	size_t	index;

	if (show0x == 1 && num != 0)
	{
		str = ft_calloc(sizeof(char), 3);
		str[0] = '0';
		str[1] = 'x';
	}
	else
		str = ft_calloc(sizeof(char), 1);
	ft_recursive_number16(num, &str);
	if (!str)
		return (NULL);
	index = 0;
	if (mayus == 0)
		return (str);
	while (str[index])
	{
		str[index] = ft_toupper(str[index]);
		index++;
	}
	return (str);
}
