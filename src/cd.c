/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:37:56 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/29 13:37:56 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(t_pipes *pipe)
{
	int		i;
	int		j;
	char	*path;

	i = 1;
	path = NULL;
	while (pipe->command[i] != NULL)
	{
		if (path != NULL)
			ft_printf("gp:%s\n", path);
		j = 0;
		while (pipe->command[i][j] == '"' || pipe->command[i][j] == '\'')
			j++;
		if (path == NULL && pipe->command[i][j] != '\0')
			path = ft_substr(pipe->command[i], j,
					ft_strlen(pipe->command[i]) - j);
		else if (path != NULL && pipe->command[i][j] != '\0'
				&& pipe->command[i] != NULL)
			return (ft_printf("cd: too many arguments\n"), NULL);
		i++;
	}
	if (path == NULL)
		return (NULL);
	return (path);
}

int	cd(t_pipes *pipe, t_envp *envp)
{
	char	*path;
	char	buffer[4096];

	path = get_path(pipe);
	if (path == NULL)
		return (-1);
	if (chdir(path) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", path);
		return (-2);
	}
	while (envp->prev != 0)
		envp = envp->prev;
	while (ft_strcmp(envp->variable, "PWD") != 0)
		envp = envp->next;
	free (envp->content);
	envp->content = ft_strdup(getcwd(buffer, 4096));
	free(path);
	return (0);
}
