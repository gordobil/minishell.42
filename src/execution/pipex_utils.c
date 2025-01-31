/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:00:37 by mafarto-          #+#    #+#             */
/*   Updated: 2025/01/31 11:10:28 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_pathsenv(t_envp *envp)
{
	char	**paths;
	int		count;

	paths = NULL;
	while (envp && strcmp(envp->variable, "PATH") != 0)
		envp = envp->next;
	if (envp && envp->content)
	{
		paths = ft_split(envp->content, ':');
		count = -1;
		while (paths[++count] != NULL)
			paths[count] = ft_strjoin(paths[count], "/");
	}
	return (paths);
}

void	execute_single_command(t_pipes *current, char **paths, t_envp *env_list)
{
	char	*temp;
	char	**term;
	t_envp	*env_temp;

	env_temp = env_list;
	while (env_temp->next)
	{
		if (ft_strcmp(env_temp->variable, "TERM") == 0
			|| ft_strcmp(env_temp->variable, "USER") == 0)
		{
			temp = ft_strcat(temp, "\n");
			temp = ft_strcat(temp, env_temp->variable);
			temp = ft_strcat(temp, "=");
			temp = ft_strcat(temp, env_temp->content);
			temp = ft_strcat(temp, "\n");
		}
		env_temp = env_temp->next;
	}
	term = ft_split(temp, '\n');
	if (building_execute(current->mini, current, env_list) == -1)
	{
		execveloop(current->command, paths, term);
	}
	exit(EXIT_SUCCESS);
}
