/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:23:04 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/06 20:41:27 by jestrada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *entry, char ***envp)
{
	char	*new_entry[2];
	char	**new_env;
	int		i;

	i = 0;
	while (entry[i] && (ft_isalnum(entry[i]) || ft_isset(entry[i], "_?"))
		&& entry[i] != '=')
		i++;
	if (entry[i] != '=')
	{
		ft_putstr_fd("Invalid variable name\n", 2);
		return ;
	}
	new_entry[0] = entry;
	new_entry[1] = NULL;
	new_env = join_split(*envp, new_entry);
	ft_split_free(*envp);
	*envp = new_env;
}

void	ft_unset(char *key, char ***envp)
{
	del_str_split(key, envp);
}

void	ft_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
