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

#include "../includes/minishell.h"

int	file_management(t_mini *mini, int i, int k)
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

char	*get_namefile(char *file, char type)
{
	while (*file == type)
		file++;
	while (*file == ' ' || *file == '	')
		file++;
	if (*file == '\0')
		return (NULL);
	return (file);
}

void	open_fds(t_mini *mini)
{
	t_pipes	*pipe;

	pipe = mini->pipes;
	while (pipe != NULL)
	{
		if (pipe->infile->file != NULL)
		{
			pipe->infile->fd = open(get_namefile(pipe->infile->file, '<'),
					O_RDONLY);
			if (pipe->infile->fd < 0)
			{
				ft_printf("bash: %s: No such file or directory\n",
					pipe->outfile->file);
				return (-1);
			}
		}
		if (pipe->outfile->file != NULL)
		{
			pipe->outfile->fd = open(get_namefile(pipe->outfile->file, '>'),
					O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			if (pipe->outfile->fd < 0)
			{
				ft_printf("minishell: %s: Error\n", pipe->outfile->file);
				return (-1);
			}
		}
		if (pipe->append->file != NULL)
		{ 
			pipe->infile->fd = open(get_namefile(pipe->append->file, '>'),
					O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			if (pipe->infile->fd < 0)
				pipe->infile->fd = open(get_namefile(pipe->append->file, '>'),
						O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		}
		if (pipe->delimiter->file != NULL)
			pipe->delimiter->fd = open(get_namefile(pipe->delimiter->file, '>'),
					O_RDONLY);
		pipe = pipe->next;
	}
}

void	close_fds(int fd, char *file)
{
	free(file);
	if (fd != 0 && fd != -1)
		close(fd);
}
