/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:28:01 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/27 12:57:31 by ngordobi         ###   ########.fr       */
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

void	close_fds(t_files *file)
{
	if (file->file != NULL)
		free(file->file);
	file->fd = 0;
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
