/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:53:44 by mafarto-          #+#    #+#             */
/*   Updated: 2025/02/07 12:44:24 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	close_pipes_and_wait(int command_count, int **pipes, t_mini *mini)
{
	int		i;
	int		status;
	t_pipes	*current;

	i = 0;
	status = 0;
	while (i < command_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	current = mini->pipes;
	while (current != NULL)
	{
		waitpid(current->pids, &status, 0);
		current = current->next;
	}
	mini->last_ret = status >> 8;
}

int	cheatriang_tool(int	***pipes, t_pipes **current)
{
	int	command_count;

	command_count = 0;
	while (*current)
	{
		*current = (*current)->next;
		command_count++;
	}
	*pipes = malloc(sizeof(int *) * (command_count - 1));
	create_pipes_for_pipeline(command_count, *pipes);
	return (command_count);
}

void	execute_pipeline(t_pipes *pipeline, t_envp *env_list)
{
	int		command_count;
	int		**pipes;
	t_pipes	*curr;
	int		i;

	command_count = -1;
	curr = pipeline;
	command_count = cheatriang_tool(&pipes, &curr);
	curr = pipeline;
	children_signals(curr->mini);
	i = -1;
	while (i++ >= -1 && curr)
	{
		curr->pids = fork();
		if (curr->pids == -1)
			return (perror("Error forking process"), exit(EXIT_FAILURE));
		if (curr->pids == 0)
		{
			setup_redirections(i, pipes, curr, command_count);
			close_pipes_and_wait(command_count, pipes, pipeline->mini);
			execute_single_command(curr, env_list);
		}
		curr = curr->next;
	}
	close_pipes_and_wait(command_count, pipes, pipeline->mini);
}
