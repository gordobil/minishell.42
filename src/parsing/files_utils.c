/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:28:01 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/17 13:53:29 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	close_fds(int fd, char *file)
{
	if (file != NULL)
		free(file);
	if (fd != 0 && fd != -1)
		close(fd);
}

int	count_files(t_mini *mini, int i, int k)
{
	if (mini->arg_matrix[i][1] != '<')
	{
		mini->files[k] = ft_strdup(mini->arg_matrix[i]);
		if (k < mini->file_c)
			k++;
	}
	return (k);
}