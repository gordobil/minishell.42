/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:28:01 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/27 15:29:54 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	free(file);
	if (fd != 0 && fd != -1)
		close(fd);
}
