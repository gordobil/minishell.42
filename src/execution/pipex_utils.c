/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:00:37 by mafarto-          #+#    #+#             */
/*   Updated: 2025/02/05 18:41:13 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_pathsenv(t_envp *envp)
{
	char	**paths;
	int		count;

	while (envp && strcmp(envp->variable, "PATH") != 0)
		envp = envp->next;
	if (envp && envp->content)
	{
		paths = ft_split(envp->content, ':');
		if (!paths)
			return (NULL);
		count = -1;
		while (paths[++count] != NULL)
		{
			paths[count] = ft_strjoin(paths[count], "/");
			if (!paths[count])
				return (free_matrix(paths), NULL);
		}
	}
	else
		return (NULL);
	return (paths);
}

void	execute_single_command(t_pipes *current, t_envp *env_list)
{
	char	**paths;

	paths = get_pathsenv(env_list);
	if (paths && building_execute(current->mini, current, env_list,
			var_jump(current->command)) == -1)
	{
		execveloop(current->command, paths, current->mini->env_str);
	}
	if (paths)
		free_matrix(paths);
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

int	check_vars(char **command, int i, t_mini *mini)
{
	t_pipes	*pipes;
	int		j;

	pipes = mini->pipes;
	while (command[++i] != NULL)
	{
		if (is_it_a_var(command[i]) < 0)
		{
			while (pipes != NULL)
			{
				j = -1;
				if (pipes->vars != NULL)
					while (pipes->vars[++j] != NULL)
						unset_var(get_var(pipes->vars[j]), mini->envp);
				pipes = pipes->next;
			}
			return (error_messages(-15, command[i]), -1);
		}
	}
	return (0);
}
