/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:00:37 by mafarto-          #+#    #+#             */
/*   Updated: 2025/01/21 11:08:05 by ngordobi         ###   ########.fr       */
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
	if (building_execute(current->mini, current, env_list) == -1)
	{
		execveloop(current->command, paths);
	}
	exit(EXIT_SUCCESS);
}