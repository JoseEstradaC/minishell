/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:24 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/01 16:19:30 by jarredon         ###   ########.fr       */
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

void	execute_command(t_command *cmd)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		execve(get_path(cmd->args[0]),
			cmd->args, NULL);
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

void	pipe_commands(t_command_table *tab, int fdin, int fdout, int tmpout)
{
	int	i;
	int	fdpipe[2];

	i = -1;
	while (++i < tab->number_of_commands)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == tab->number_of_commands - 1)
		{
			if (tab->out_file)
				fdout = open(tab->out_file, O_WRONLY);
			else
				fdout = dup(tmpout);
		}
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		execute_command(tab->commands[i]);
	}
}

void	execute(t_command_table *tab)
{
	int	tmpin;
	int	tmpout;
	int	fdin;

	tmpin = dup(0);
	tmpout = dup(1);
	if (tab->input_file)
		fdin = open(tab->input_file, O_RDONLY);
	else
		fdin = dup(tmpin);
	pipe_commands(tab, fdin, 0, tmpout);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}
