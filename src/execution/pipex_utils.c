/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:00:37 by mafarto-          #+#    #+#             */
/*   Updated: 2025/01/31 18:30:35 by mafarto-         ###   ########.fr       */
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
	if (building_execute(current->mini, current, env_list,
			var_jump(current->command)) == -1)
	{
		execveloop(current->command, paths, current->mini->env_str);
	}
	exit(EXIT_SUCCESS);
}

int	var_jump(char **command)
{
	int	i;

	i = 0;
	while (command[i] != NULL && is_it_a_var(command[i]) > 0)
		i++;
	return (i);
}
