/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 01:19:32 by jarredon          #+#    #+#             */
/*   Updated: 2022/06/03 01:20:42 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envp_to_list(char **envp)
{
	t_env	*list;
	t_env	*last;
	int		i;

	if (!envp || !(*envp))
		return (NULL);
	i = 0;
	list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->entry = ft_strdup(envp[i++]);
	last = list;
	while (envp[i])
	{
		last->next = (t_env *)malloc(sizeof(t_env));
		if (!last->next)
			return (NULL);
		last = last->next;
		last->entry = ft_strdup(envp[i++]);
	}
	last->next = NULL;
	return (list);
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		*env = (*env)->next;
		free(tmp->entry);
		free(tmp);
		tmp = *env;
	}
}

char	**list_to_envp(t_env *env)
{
	int		size;
	t_env	*ptr;
	char	**envp;
	int		i;

	size = 0;
	ptr = env;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i++] = ft_strdup(env->entry);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

//ft_split_free

char	*get_env_value(char *key, t_env *env)
{
	int	len_key;

	len_key = ft_strlen(key);
	while (env)
	{
		if (!ft_strncmp(env->entry, key, len_key)
			&& env->entry[len_key] == '=')
			return (&env->entry[len_key + 1]);
		env = env->next;
	}
	return (NULL);
}

int	add_to_env(char *entry, t_env **env)
{
	t_env	*new_node;
	t_env	*ptr;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (-1);
	new_node->entry = ft_strdup(entry);
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return (0);
	}
	ptr = *env;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_node;
	return (0);
}

int	del_from_env(char *key, t_env **env)
{
	int		len_key;
	t_env	*prev;
	t_env	*ptr;

	len_key = ft_strlen(key);
	prev = *env;
	if (*env && !ft_strncmp((*env)->entry, key, len_key)
		&& (*env)->entry[len_key] == '=')
	{
		*env = (*env)->next;
		free(prev->entry);
		free(prev);
		return (0);
	}
	ptr = (*env)->next;
	while (ptr)
	{
		if (!ft_strncmp(ptr->entry, key, len_key)
			&& ptr->entry[len_key] == '=')
		{
			prev->next = ptr->next;
			free(ptr->entry);
			free(ptr);
			return (0);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (-1);
}
