/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2025/01/14 14:24:07 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	building_execute(t_mini *mini, t_pipes *pipe, t_envp *envp)
{
	if (pipe != NULL && pipe->command != NULL && pipe->command[0] != NULL)
	{
		if (ft_strcmp(pipe->command[0], "cd") == 0)
			ms_cd(pipe, envp);
		else if (ft_strcmp(pipe->command[0], "echo") == 0)
			ms_echo(pipe);
		else if (ft_strcmp(pipe->command[0], "env") == 0)
			ms_env(envp, pipe);
		else if (ft_strcmp(pipe->command[0], "export") == 0)
			ms_export(pipe, envp);
		else if (ft_strcmp(pipe->command[0], "pwd") == 0)
			ms_pwd(envp, pipe);
		else if (ft_strcmp(pipe->command[0], "unset") == 0)
			ms_unset(pipe, envp);
		else if (pipe->args == pipe->var_c)
			add_vars(pipe, mini);
		else
			return (-1);
	}
	return (0);
}

void	execveloop(char **str, char **path)
{
	char	*bin;
	int		count;

	while (is_it_a_var(*str) > 0)
		*str++;
	count = 0;
	while (path[count] != 0)
	{
		bin = ft_strcat(path[count], *str);
		execve(bin, str, 0);
		free (bin);
		count++;
	}
	ft_printf("%s: command not found\n", *str);
	exit(127);
}

void	pipex(t_pipes *pipes, t_envp *envp)
{
	int		status;
	int		id;
	char	**path;

	if (!pipes || !pipes->command || !pipes->command[0] || envp == NULL)
		return ;
	path = get_pathsenv(envp);
	envp = get_edge_node(pipes->mini->envp, 's');
	if (pipes->next == NULL)
	{
		if (building_execute(pipes->mini, pipes, envp) == -1)
		{
			id = fork();
			if (id == 0)
				execveloop(pipes->command, path);
			waitpid(id, &status, 0);
		}
	}
	else
	{
		execute_pipeline(pipes, envp);
	}
	free_matrix(path);
}
