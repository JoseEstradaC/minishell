/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:24 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/01 15:06:47 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_tables(char **a, char **b);

static char	*check_dir(char *cmd, char **paths, int i)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp;
	char			*ret;

	dir = opendir(paths[i]);
	file = readdir(dir);
	while (file)
	{
		if (!ft_strncmp(file->d_name, cmd, ft_strlen(cmd) + 1))
		{
			tmp = ft_strjoin(paths[i], "/");
			ret = ft_strjoin(tmp, cmd);
			free(tmp);
			closedir(dir);
			ft_split_free(paths);
			return (ret);
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

static char	*get_path(char *cmd)
{
	char	**paths;
	char	*ret;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		ret = check_dir(cmd, paths, i);
		if (ret)
			return (ret);
	}
	ft_split_free(paths);
	return (NULL);
}

void	execute(t_command_table *tab)
{
	int		pid;
	int		i;

	i = -1;
	while (++i < tab->number_of_commands)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(get_path(tab->commands[i]->args[0]),
				tab->commands[i]->args, NULL);
			perror("execvp");
			exit(-1);
		}
		else if (pid < 0)
		{
			perror("fork");
			return ;
		}
		wait(NULL);
	}
}
