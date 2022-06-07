/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:31:12 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/07 08:37:54 by jarredon         ###   ########.fr       */
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

	if (!path)
		path = get_env_value("HOME", *envp);
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
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

int	ft_exit(t_command_table *table)
{
	int	ret;

	if (table->commands[0]->number_of_arguments > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-1);
	}
	else if (table->commands[0]->args[1] == NULL)
	{
		free_table(table);
		return (0);
	}
	else if (ft_str_is_numeric(table->commands[0]->args[1]))
	{
		ret = ft_atoi(table->commands[0]->args[1]);
		return ((int)((unsigned char)ret));
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (-1);
	}
}
