/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:31:24 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/07 17:00:11 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipes
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
}		t_pipes;

int	exec_builtin(t_command *cmd, char ***envp);
int	input_delim(t_command_table *tab);

static int	execute_command(t_command *cmd, char ***envp)
{
	int		pid;

	if (exec_builtin(cmd, envp))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		execve(get_path(cmd->args[0], *envp), cmd->args, *envp);
		printf("command not found: %s\n", cmd->args[0]);
		exit(-1);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

static int	redirect_io(t_command_table *tab, int i, t_pipes *pipes)
{
	int	fdpipe[2];

	if (i == tab->number_of_commands - 1)
	{
		if (tab->out_file && ft_strlen(tab->out_type) == 1)
			pipes->fdout = open(tab->out_file,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tab->out_file && ft_strlen(tab->out_type) == 2)
			pipes->fdout = open(tab->out_file, O_WRONLY | O_APPEND);
		else
			pipes->fdout = dup(pipes->tmpout);
		if (pipes->fdout < 0)
		{
			perror(tab->out_file);
			return (-1);
		}
	}
	else
	{
		if (pipe(fdpipe) < 0)
			return (-1);
		pipes->fdout = fdpipe[1];
		pipes->fdin = fdpipe[0];
	}
	return (0);
}

static void	kill_children(int *children, int i, t_command_table *tab)
{
	int		wstatus;
	char	*n_status;

	waitpid(children[i], &wstatus, 0);
	n_status = ft_itoa(WEXITSTATUS(wstatus));
	set_env_value("?", n_status, tab->env);
	free(n_status);
	while (--i >= 0)
	{
		if (children[i] > 0)
			kill(children[i], SIGKILL);
	}
}

static int	pipe_commands(t_command_table *tab, t_pipes *pipes)
{
	int	i;
	int	ret;
	int	children[1024];

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
		children[i] = execute_command(tab->commands[i], tab->env);
	}
	kill_children(children, i - 1, tab);
	return (0);
}

int	execute(t_command_table *tab)
{
	t_pipes	pipes;
	int		ret;

	pipes.tmpin = dup(0);
	pipes.tmpout = dup(1);
	if (tab->input_file && ft_strlen(tab->input_type) == 1)
		pipes.fdin = open(tab->input_file, O_RDONLY);
	else if (tab->input_file && ft_strlen(tab->input_type) == 2)
		pipes.fdin = input_delim(tab);
	else
		pipes.fdin = dup(pipes.tmpin);
	if (pipes.fdin < 0)
	{
		perror(tab->input_file);
		close(pipes.tmpin);
		close(pipes.tmpout);
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
