/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:50:23 by jestrada          #+#    #+#             */
/*   Updated: 2022/05/17 17:07:36 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char **buffer)
{
	char	*ret;

	ret = ft_strchr(*buffer, '\n');
	if (!ret)
		return (ft_substr(*buffer, 0, ft_strlen(*buffer)));
	return (ft_substr(*buffer, 0, ret - *buffer + 1));
}

char	*join_buffer(char **buffer, char *readed)
{
	char	*temp;

	temp = *buffer;
	*buffer = ft_strjoin(*buffer, readed);
	if (!*buffer)
		return (NULL);
	free(temp);
	return (*buffer);
}

char	*next_line(char **buffer)
{
	char	*temp;
	char	*find;

	find = ft_strchr(*buffer, '\n');
	if (!find)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	temp = ft_substr(*buffer, find - *buffer + 1, ft_strlen(find));
	free(*buffer);
	*buffer = temp;
	return (*buffer);
}

char	*read_line(char **buffer, int fd)
{
	char	readed[BUFFER_SIZE + 1];
	ssize_t	linesread;
	char	*temp;

	linesread = 1;
	while (linesread > 0)
	{
		ft_bzero(readed, BUFFER_SIZE + 1);
		linesread = read(fd, readed, BUFFER_SIZE);
		if (linesread == 0)
			break ;
		if (!join_buffer(buffer, readed))
			return (NULL);
		temp = ft_strchr(*buffer, '\n');
		if (temp)
			break ;
	}
	temp = get_line(buffer);
	next_line(buffer);
	if (*temp == '\0')
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(char));
		*buffer = '\0';
	}
	return (read_line(&buffer, fd));
}
