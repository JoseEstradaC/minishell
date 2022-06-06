/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:31:12 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/06 15:39:29 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(int ac, char **args)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (ac > 1 && !ft_strncmp("-n", args[i], 3))
	{
		n = 1;
		i++;
	}
	while (i < ac)
	{
		ft_putstr_fd(args[i], 1);
		if (i < ac - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}

int	ft_cd(char *path, char ***envp)
{
	char	buffer[200];

	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	set_env_value("OLDPWD", get_env_value("PWD", *envp), envp);
	getcwd(buffer, 200);
	set_env_value("PWD", buffer, envp);
	return (0);
}

void	ft_pwd(void)
{
	char	buffer[200];

	getcwd(buffer, 200);
	printf("%s\n", buffer);
}
