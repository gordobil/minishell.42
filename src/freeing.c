/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:27:59 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/25 13:08:54 by ngordobi         ###   ########.fr       */
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
	if (pipe->infile->file)
	{
		free(pipe->infile->file);
		close(pipe->infile->fd);
	}
	free(pipe->infile);
	if (pipe->outfile->file)
	{
		free(pipe->outfile->file);
		close(pipe->outfile->fd);
	}
	free(pipe->outfile);
	if (pipe->append->file)
	{
		free(pipe->append->file);
		close(pipe->append->fd);
	}
	free(pipe->append);
	if (pipe->delimiter->file)
	{
		free(pipe->delimiter->file);
		close(pipe->delimiter->fd);
	}
	free(pipe->delimiter);
}

void	free_pipes(t_pipes *pipe)
{
	int	i;

	while (pipe != NULL)
	{
		i = -1;
		while (pipe->command[++i] != NULL)
			free(pipe->command[i]);
		free(pipe->command);
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
	free_envp(mini->envp);
	free_pipes(mini->pipes);
	free_matrix(mini->arg_matrix);
	if (mini->files)
		free_matrix(mini->files);
	if (mini->delimiters)
		free_matrix(mini->delimiters);
}
