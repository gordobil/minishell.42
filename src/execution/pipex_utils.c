/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:00:37 by mafarto-          #+#    #+#             */
/*   Updated: 2025/02/07 18:03:29 by mafarto-         ###   ########.fr       */
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
	if (!paths)
	{
		execve(*current->command, current->command, 0);
		if (!paths)
			ft_printf("%s: No such file or directory\n", *current->command);
	}
	if (!current->next
		&& is_text(current, env_list, var_jump(current->command)) == 1)
		building_redir(current, env_list);
	else
		execveloop(current->command, paths, current->mini->env_str);
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

void	building_redir(t_pipes *pipes, t_envp *envp)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (pipes->outfile->file)
	{
		dup2(pipes->outfile->fd, STDOUT_FILENO);
		close(pipes->outfile->fd);
		building_execute(pipes->mini, pipes, envp, var_jump(pipes->command));
	}
	else if (pipes->append->file)
	{
		dup2(pipes->append->fd, STDOUT_FILENO);
		close(pipes->append->fd);
		building_execute(pipes->mini, pipes, envp, var_jump(pipes->command));
	}
	else
		building_execute(pipes->mini, pipes, envp, var_jump(pipes->command));
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
