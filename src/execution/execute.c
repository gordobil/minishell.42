/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2025/02/05 14:57:32 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	building_execute(t_mini *mini, t_pipes *pipe, t_envp *envp, int i)
{
	if (pipe != NULL && pipe->command != NULL && pipe->command[i] != NULL)
	{
		if (ft_strcmp(pipe->command[i], "cd") == 0)
			ms_cd(pipe, envp, i);
		else if (ft_strcmp(pipe->command[i], "echo") == 0)
			ms_echo(pipe, i);
		else if (ft_strcmp(pipe->command[i], "pwd") == 0)
			ms_pwd(envp, pipe);
		else if (ft_strcmp(pipe->command[i], "env") == 0)
			ms_env(envp, pipe, i, 0);
		else if (ft_strcmp(pipe->command[i], "export") == 0
			&& pipe->command[i + 1] == NULL)
			ms_env(envp, pipe, i, 1);
		else if (ft_strcmp(pipe->command[i], "export") == 0
			&& pipe->command[i + 1] != NULL
			&& check_vars(pipe->command, i, mini) == 0)
			ms_export(pipe, envp, i);
		else if (ft_strcmp(pipe->command[i], "unset") == 0)
			ms_unset(pipe, envp, i);
		return (-1);
	}
	return (0);
}

void	execveloop(char **str, char **path, char **term)
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
	free_matrix(path);
	execve(*str, str, 0);
	ft_printf("%s: command not found\n", *str);
	exit(127);
}

int	comand_size(t_pipes	*pipes)
{
	int	command_count;

	command_count = 0;
	while (pipes->prev != NULL)
		pipes = pipes->prev;
	while (pipes)
	{
		command_count++;
		ft_printf("%d\n", comand_size);
		pipes = pipes->next;
	}
	return (command_count);
}

int	is_text(t_pipes *pipe, t_envp *envp, int i)
{
	if (ft_strcmp(pipe->command[i], "cd") == 0)
		return (0);
	else if (ft_strcmp(pipe->command[i], "echo") == 0)
		return (0);
	else if (ft_strcmp(pipe->command[i], "pwd") == 0)
		return (1);
	else if (ft_strcmp(pipe->command[i], "env") == 0)
		return (1);
	else if (ft_strcmp(pipe->command[i], "export") == 0)
		return (0);
	else if (ft_strcmp(pipe->command[i], "unset") == 0)
		return (0);
	return (1);
}

void	pipex(t_pipes *pipes, t_envp *envp)
{
	int		status;
	char	**path;

	if (!pipes || !pipes->command || !pipes->command[0] || envp == NULL)
		return ;
	envp = get_edge_node(pipes->mini->envp, 's');
	if (!pipes->next && is_text(pipes, envp, var_jump(pipes->command)) == 0)
		building_execute(pipes->mini, pipes, envp, var_jump(pipes->command));
	else
		execute_pipeline(pipes, envp);
}
