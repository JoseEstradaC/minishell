/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:24 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/03 16:42:03 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipes
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
}	t_pipes;

void	close_pipes(t_pipes *pipes)
{
	if (fcntl(pipes->tmpin, F_GETFD) != -1)
		close(pipes->tmpin);
	if (fcntl(pipes->tmpout, F_GETFD) != -1)
		close(pipes->tmpout);
	if (fcntl(pipes->fdin, F_GETFD) != -1)
		close(pipes->fdin);
	if (fcntl(pipes->fdout, F_GETFD) != -1)
		close(pipes->fdout);
}

// TODO poner envp
int	exec_builtin(t_command *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_echo(cmd->number_of_arguments, cmd->args);
	else if (!ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_cd(cmd->args[1], NULL);
	else if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_pwd();
	else if (!ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_export(cmd->args[1], NULL);
	else if (!ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_unset(cmd->args[1], NULL);
	else if (!ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0])))
		ft_env(NULL);
	else if (!ft_strncmp("exit", cmd->args[0], ft_strlen(cmd->args[0])))
		exit(0);
	else
		ret = 1;
	return (ret);
}

void	execute_command(t_command *cmd)
{
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		execve(get_path(cmd->args[0]), cmd->args, NULL);
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

int	redirect_io(t_command_table *tab, int i, t_pipes *pipes)
{
	int	ret;
	int	fdpipe[2];

	if (i == tab->number_of_commands - 1)
	{
		if (tab->out_file)
			pipes->fdout = open(tab->out_file, O_WRONLY | O_CREAT);
		else
			pipes->fdout = dup(pipes->tmpout);
		if (pipes->fdout < 0)
			return (-1);
	}
	else
	{
		ret = pipe(fdpipe);
		if (ret < 0)
			return (-1);
		pipes->fdout = fdpipe[1];
		pipes->fdin = fdpipe[0];
	}
	return (0);
}

int	pipe_commands(t_command_table *tab, t_pipes *pipes)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < tab->number_of_commands)
	{
		dup2(pipes->fdin, 0);
		close(pipes->fdin);
		ret = redirect_io(tab, i, pipes);
		if (ret < 0)
			return (-1);
		dup2(pipes->fdout, 1);
		close(pipes->fdout);
		execute_command(tab->commands[i]);
	}
	return (0);
}

int	execute(t_command_table *tab)
{
	t_pipes	pipes;
	int		ret;

	pipes.tmpin = dup(0);
	pipes.tmpout = dup(1);
	if (tab->input_file)
		pipes.fdin = open(tab->input_file, O_RDONLY);
	else
		pipes.fdin = dup(pipes.tmpin);
	if (pipes.fdin < 0)
	{
		close_pipes(&pipes);
		return (-1);
	}
	ret = 0;
	ret = pipe_commands(tab, &pipes);
	dup2(pipes.tmpin, 0);
	dup2(pipes.tmpout, 1);
	close(pipes.tmpin);
	close(pipes.tmpout);
	return (ret);
}
