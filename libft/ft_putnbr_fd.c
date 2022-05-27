/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 05:09:21 by jestrada          #+#    #+#             */
/*   Updated: 2022/04/21 16:43:57 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive_number(long num, int fd)
{
	if (num > 9)
		ft_recursive_number(num / 10, fd);
	write(fd, &"0123456789"[num % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	ft_recursive_number(num, fd);
}
