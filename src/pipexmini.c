/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexmini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:53:44 by mafarto-          #+#    #+#             */
/*   Updated: 2025/01/22 20:19:34 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes_for_pipeline(int command_count, int **pipes)
{
	int	i;

	i = 0;
	while (i < command_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("Error creating pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	setup_redirections(int i, int **pipes, t_pipes *current,
	int command_count)
{
	if (current->infile->file)
		dup2(current->infile->fd, STDIN_FILENO);
	else if (current->delimiter->file)
		dup2(current->delimiter->fd, STDIN_FILENO);
	else if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (current->outfile->file)
		dup2(current->outfile->fd, STDOUT_FILENO);
	else if (current->append->file)
		dup2(current->append->fd, STDOUT_FILENO);
	else if (current->next)
		dup2(pipes[i][1], STDOUT_FILENO);
}

void	close_pipes_and_wait(int command_count, int **pipes, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < command_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	i = 0;
	while (i < command_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}

int	cheatriang_tool(int	***pipes, pid_t **pids,	t_pipes **current)
{
	int	command_count;

	command_count = 0;
	while (*current)
	{
		*current = (*current)->next;
		command_count++;
	}
	*pipes = malloc(sizeof(int *) * (command_count - 1));
	*pids = malloc(sizeof(pid_t) * command_count);
	create_pipes_for_pipeline(command_count, *pipes);
	return (command_count);
}

void	execute_pipeline(t_pipes *pipeline, t_envp *env_list)
{
	int		command_count;
	int		**pipes;
	pid_t	*pids;
	t_pipes	*current;
	int		i;

	command_count = -1;
	current = pipeline;
	command_count = cheatriang_tool(&pipes, &pids, &current);
	current = pipeline;
	i = -1;
	while (i++ >= -1 && current)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("Error forking process"), exit(EXIT_FAILURE));
		if (pids[i] == 0)
		{
			setup_redirections(i, pipes, current, command_count);
			close_pipes_and_wait(command_count, pipes, pids);
			execute_single_command(current, get_pathsenv(env_list), env_list);
		}
		current = current->next;
	}
	close_pipes_and_wait(command_count, pipes, pids);
}
