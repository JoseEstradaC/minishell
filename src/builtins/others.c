/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:31:12 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/03 15:28:26 by jarredon         ###   ########.fr       */
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
		printf("%s", args[i]);
		if (i < ac - 1)
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
}

char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	len_key;

	len_key = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len_key)
			&& envp[i][len_key] == '=')
			return (&envp[i][len_key + 1]);
		i++;
	}
	return (NULL);
}

int	ft_cd(char *path, char ***envp)
{
	char	*old_pwd;
	char	*pwd;
	char	buffer[200];
	
	if (chdir(path) == -1)
		return (-1);
	old_pwd = ft_strjoin("OLDPWD=", get_env_value("PWD", *envp));
	getcwd(buffer, 200);
	pwd = ft_strjoin("PWD=", buffer);
	ft_unset("OLDPWD", envp);
	ft_export(old_pwd, envp);
	ft_unset("PWD", envp);
	ft_export(pwd, envp);
	free(old_pwd);
	free(pwd);
	return (0);
}

void	ft_pwd(void)
{
	char	buffer[200];

	getcwd(buffer, 200);
	printf("%s\n", buffer);
}
