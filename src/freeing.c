/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:27:59 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/17 13:54:31 by ngordobi         ###   ########.fr       */
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
	matrix = NULL;
}

void	free_envp(t_envp *envp)
{
	if (!envp)
		return ;
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

void	free_files(t_pipes *pipe)
{
	close_fds(pipe->infile->fd, pipe->infile->file);
	free(pipe->infile);
	close_fds(pipe->outfile->fd, pipe->outfile->file);
	free(pipe->outfile);
	close_fds(pipe->append->fd, pipe->append->file);
	free(pipe->append);
	close_fds(pipe->delimiter->fd, pipe->delimiter->file);
	free(pipe->delimiter);
}

void	free_pipes(t_pipes *pipe)
{
	while (pipe != NULL)
	{
		if (pipe->command)
			free_matrix(pipe->command);
		if (pipe->vars != NULL)
			free_matrix(pipe->vars);
		pipe->var_c = 0;
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

void	freeing(t_mini *mini)
{
	namefiles(1);
	free_pipes(mini->pipes);
	free_matrix(mini->arg_matrix);
	mini->arg_c = 0;
	mini->comm_c = 0;
	if (mini->files != NULL)
		free_matrix(mini->files);
	mini->file_c = 0;
	if (mini->delimiters != NULL)
		free_matrix(mini->delimiters);
	mini->del_c = 0;
}
