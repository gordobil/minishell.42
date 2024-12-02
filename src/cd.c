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

char	*path_substr(char *command, int i, int j)
{
	char	*path;

	path = NULL;
	if (j > 0)
		path = ft_substr(command, j, ft_strlen(command )- (j + 1));
	else if (j == 0)
		path = ft_substr(command, j, ft_strlen(command) - j);
	if (path != NULL)
		return (path);
	return (command);
}

int	del_quotes(char *path, char type)
{
	int		j;
	char	x_type;

	if (type == '"')
		x_type = '\'';
	else
		x_type = '"';
	j = 0;
	if (path[0] == '"' || path[0] == '\'')
	{
		while (path[j] == type)
			j++;
		if (path[j] == x_type)
			return (-1);
		return (j);
	}
	return (0);
}

char	*get_path(t_pipes *pipe)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	path = NULL;
	while (pipe->command[++i] != NULL)
	{
		j = del_quotes(pipe->command[i], pipe->command[1][0]);
		if (j < 0)
			return (pipe->command[i]);
		if (path == NULL && pipe->command[i][j] != '\0'
			&& pipe->command[i][j] != '"' && pipe->command[i][j] != '\'')
			path = path_substr(pipe->command[i], i, j);
		else if (path != NULL && pipe->command[i][j] != '\0'
				&& pipe->command[i] != NULL && pipe->command[i][j] != '"'
				&& pipe->command[i][j] != '\'')
			return (ft_printf("cd: too many arguments\n"), NULL);
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
		free(path);
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
