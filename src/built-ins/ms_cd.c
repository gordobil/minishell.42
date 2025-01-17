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

#include "../../includes/minishell.h"

char	*get_path(t_pipes *pipe, int i)
{
	i++;
	if ((pipe->command[i] == NULL || ft_strcmp(pipe->command[i], "~") == 0)
		&& pipe->command[i + 1] == NULL)
		return (ft_strdup("/"));
	else if (pipe->command[i] != NULL && ft_strcmp(pipe->command[i], "~") != 0
		&& pipe->command[i + 1] == NULL)
		return (ft_strdup(pipe->command[i]));
	else if (pipe->command[i] != NULL && pipe->command[i + 1] != NULL)
		return (error_messages(-5, "cd"), NULL);
	return (NULL);
}

int	ms_cd(t_pipes *pipe, t_envp *envp, int i)
{
	char	*path;
	char	buffer[4096];
	t_envp	*var;

	path = get_path(pipe, i);
	if (path == NULL)
		return (-1);
	else if (chdir(path) != 0)
	{
		error_messages(-6, path);
		return (free(path), -2);
	}
	var = envp;
	while (ft_strcmp(var->variable, "PWD") != 0)
		var = var->next;
	free (var->content);
	var->content = ft_strdup(getcwd(buffer, 4096));
	return (free(path), 0);
}
