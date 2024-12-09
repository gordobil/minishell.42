/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:55:19 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/25 12:55:19 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_saving(t_mini *mini, int i, int k)
{
	if (mini->arg_matrix[i][1] != '<')
	{
		mini->files[k] = ft_strdup(mini->arg_matrix[i]);
		if (k < mini->file_c)
			k++;
	}
	if (mini->arg_matrix[i][0] == '<' && mini->arg_matrix[i][1] != '<')
		mini->pipes->infile->file = ft_strdup(mini->arg_matrix[i]);
	else if (mini->arg_matrix[i][0] == '>' && mini->arg_matrix[i][1] != '>')
	{
		mini->pipes->outfile->file = ft_strdup(mini->arg_matrix[i]);
		if (mini->pipes->append->file != NULL)
			mini->pipes->append->file = NULL;
	}
	else if (mini->arg_matrix[i][0] == '>' && mini->arg_matrix[i][1] == '>')
	{
		mini->pipes->append->file = ft_strdup(mini->arg_matrix[i]);
		if (mini->pipes->outfile->file != NULL)
			mini->pipes->outfile->file = NULL;
	}
	else if (mini->arg_matrix[i][0] == '<' && mini->arg_matrix[i][1] == '<')
		mini->pipes->delimiter->file = ft_strdup(mini->arg_matrix[i]);
	return (k);
}

int	file_count(char **args, int i, char ret)
{
	int	j;
	int	count;

	count = 0;
	while (args[i] != NULL)
	{
		j = i - 1;
		if (args[i][0] == '>' || (args[i][0] == '<' && args[i][1] != '<'))
		{
			while (j >= 0 && ms_strcmp(args[i], args[j]) != 0)
				j--;
			if (j < 0)
				count++;
			if (ret == 'r')
				return (j);
		}
		if (args[i][0] == '<' && args[i][1] == '<' && ret == 'r')
			return (-1);
		i++;
	}
	if (ret == 'r')
		return (0);
	return (count);
}

int	in_out_files(t_pipes *pipe, char file)
{
	if (file == 'i')
	{
		pipe->infile->fd = open(get_namefile(pipe->infile->file, '<'),
				O_RDONLY);
		if (pipe->infile->fd < 0)
			return (error_messages(-3,
					get_namefile(pipe->infile->file, '<')), -1);
	}
	else if (file == 'o')
	{
		pipe->outfile->fd = open(get_namefile(pipe->outfile->file, '>'),
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (pipe->outfile->fd < 0)
			return (error_messages(-4,
					get_namefile(pipe->outfile->file, '>')), -1);
	}
	return (0);
}

int	open_fds(t_mini *mini)
{
	t_pipes	*pipe;

	pipe = mini->pipes;
	while (pipe != NULL)
	{
		if (pipe->infile->file != NULL)
			if (in_out_files(pipe, 'i') != 0)
				return (-1);
		if (pipe->outfile->file != NULL)
			if (in_out_files(pipe, 'o') != 0)
				return (-1);
		if (pipe->append->file != NULL)
		{
			pipe->infile->fd = open(get_namefile(pipe->append->file, '>'),
					O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			if (pipe->infile->fd < 0)
				pipe->infile->fd = open(get_namefile(pipe->append->file, '>'),
						O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		}
		if (pipe->delimiter->file != NULL)
			pipe->delimiter->fd = open(pipe->delimiter->file, O_RDONLY);
		pipe = pipe->next;
	}
	return (0);
}
