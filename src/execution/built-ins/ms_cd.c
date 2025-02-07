/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:37:56 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/29 13:37:56 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd_var(t_envp *envp, char *buffer)
{
	t_envp	*var;

	var = envp;
	while (ft_strcmp(var->variable, "PWD") != 0)
		var = var->next;
	free (var->content);
	var->content = ft_strdup(getcwd(buffer, 4096));
}

char	*replace_home(t_pipes *pipe, int i)
{
	char	*sub_command;
	t_envp	*var;

	var = pipe->mini->envp;
	while (ft_strcmp("HOME", var->variable) != 0 && var != NULL)
		var = var->next;
	i++;
	if (pipe->command[i] != NULL && ft_strcmp(pipe->command[i], "~") != 0)
	{
		sub_command = ft_substr(pipe->command[i], 1,
				ft_strlen(pipe->command[i]) - 1);
		free(pipe->command[i]);
		pipe->command[i] = ft_strdup(sub_command);
		free(sub_command);
	}
	else if (pipe->command[i] != NULL && ft_strcmp(pipe->command[i], "~") == 0)
	{
		free (pipe->command[i]);
		pipe->command[i] = ft_strdup(var->content);
	}
	return (ft_strdup(var->content));
}

char	*get_path(t_pipes *pipe, int i, char *home)
{
	if (pipe->command[i + 1] != NULL && pipe->command[i + 2] == NULL)
		return (ft_strdup(pipe->command[i + 1]));
	else if (pipe->command[i + 1] == NULL)
		return (home);
	else if (pipe->command[i + 1] != NULL && pipe->command[i + 2] != NULL)
		return (error_messages(-5, "cd"), NULL);
	return (NULL);
}

int	ms_cd(t_pipes *pipe, t_envp *envp, int i)
{
	char	*path;
	char	buffer[4096];
	t_envp	*var;
	char	*home;

	home = NULL;
	if (pipe->command[i + 1] == NULL || pipe->command[i + 1][0] == '~')
		home = replace_home(pipe, i);
	if (pipe->command[i + 1] != NULL)
		path = get_path(pipe, i, home);
	else
		path = ft_strdup(home);
	if (home)
		free(home);
	if (path == NULL)
		return (-1);
	if (chdir(path) != 0)
	{
		error_messages(-6, path);
		return (pipe->mini->last_ret = 1, free(path), -2);
	}
	update_pwd_var(envp, buffer);
	return (free(path), 0);
}
