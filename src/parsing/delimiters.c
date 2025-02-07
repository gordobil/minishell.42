/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:05:41 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/11 12:05:41 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*namefiles(int del)
{
	char		*namefile;
	char		*num;
	static int	count;

	if (del == 0)
	{
		count++;
		num = ft_itoa(count);
		namefile = ft_strjoin(".temp_file_", num);
		free(num);
		return (namefile);
	}
	else if (del == 1)
	{
		while (count > 0)
		{
			num = ft_itoa(count);
			namefile = ft_strjoin(".temp_file_", num);
			unlink(namefile);
			free(namefile);
			free(num);
			count--;
		}
	}
	return (NULL);
}

t_pipes	*save_files(t_pipes *command, char *namefile, int fd, int i)
{
	close(fd);
	if (ft_strcmp(command->mini->delimiters[i], command->delimiter->file) == 0)
	{
		if (command->delimiter->file != NULL)
		{
			free (command->delimiter->file);
			command->delimiter->file = NULL;
		}
		if (command->infile->file == NULL)
		{
			command->delimiter->file = ft_strdup(namefile);
			open(command->delimiter->file, O_RDONLY);
		}
		command->delimiter->fd = fd;
		if (command->mini->comm_c > 1 && command->next != NULL)
		{
			command = command->next;
			while (command->delimiter->file == NULL && command->next != NULL)
				command = command->next;
		}
	}
	return (command);
}

int	del_cmp(char *delimiter, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (delimiter[i] == '<')
		i++;
	while (delimiter[i] == ' ' || delimiter[i] == '	')
		i++;
	j = 0;
	while (delimiter[i] == line[j] && delimiter[i] != '\0' && line[j] != '\0')
	{
		i++;
		j++;
	}
	if (delimiter[i] == '\0' && line[j] == '\0')
		return (0);
	return (-1);
}

int	write_line(t_mini *mini, int fd, int i)
{
	char	*line;

	while (1)
	{
		line = readline(YELLOW"> "WHITE);
		if (!line)
		{
			error_messages(-16, rm_arrows(mini->delimiters[i]));
			return (-1);
		}
		if (del_cmp(mini->delimiters[i], line) == 0)
			return (1);
		line = replace_vars(mini, line, 0);
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free (line);
	}
	return (0);
}

int	delimiters(t_mini *mini, t_pipes *command)
{
	char	*namefile;
	int		fd;
	int		i;
	int		rdl_ret;

	i = -1;
	rdl_ret = 0;
	while (mini->delimiters[++i] != NULL)
	{
		if (command == NULL)
			break ;
		namefile = namefiles(0);
		fd = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (fd)
		{
			rdl_ret = write_line(mini, fd, i);
			if (rdl_ret == 1)
				command = save_files(command, namefile, fd, i);
			close(fd);
		}
		free(namefile);
		if (rdl_ret == -1)
			return (-1);
	}
	return (0);
}
