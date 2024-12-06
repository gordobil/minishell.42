/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:27:59 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/06 18:57:00 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_files(t_pipes *pipe)
{
	if (pipe->infile->file != NULL)
		close_fds(pipe->infile->fd, pipe->infile->file);
	free(pipe->infile);
	if (pipe->outfile->file != NULL)
		close_fds(pipe->outfile->fd, pipe->outfile->file);
	free(pipe->outfile);
	if (pipe->append->file != NULL)
		close_fds(0, pipe->append->file);
	free(pipe->append);
	if (pipe->delimiter->file != NULL)
		close_fds(pipe->delimiter->fd, pipe->delimiter->file);
	free(pipe->delimiter);
}

void	free_pipes(t_pipes *pipe)
{
	int	i;

	while (pipe != NULL)
	{
		i = -1;
		if (pipe->command)
			free_matrix(pipe->command);
		if (pipe->vars)
			free_matrix(pipe->vars);
		free_files(pipe);
		if (pipe->position > 0)
			free(pipe->prev);
		if (pipe->next == NULL)
		{
			free(pipe);
			break ;
		}
		pipe = pipe->next;
	}
}

void	free_envp(t_envp *envp)
{
	while (envp->position > 0)
		envp = envp->prev;
	while (envp != NULL)
	{
		free(envp->content);
		free(envp->variable);
		if (envp->prev != NULL)
			free(envp->prev);
		if (envp->next == NULL)
		{
			free(envp);
			break ;
		}
		envp = envp->next;
	}
}

void	freeing(t_mini *mini)
{
	namefiles(1);
	free_pipes(mini->pipes);
	free_matrix(mini->arg_matrix);
	if (mini->files)
		free_matrix(mini->files);
	if (mini->delimiters)
		free_matrix(mini->delimiters);
}
