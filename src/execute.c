/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2024/11/27 19:46:04 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp	*litnew(char **variable, t_envp *envp)
{
	struct s_envp	*temp_envp;

	temp_envp = malloc(sizeof(struct s_envp));
	while (envp->prev->position != 0)
		envp = envp->prev;
	while (envp->next != NULL)
		envp = envp->next;
	temp_envp->position = envp->position + 1;
	temp_envp->prev = envp;
	envp->next = temp_envp;
	temp_envp->variable = variable[0];
	temp_envp->content = variable[1];
	temp_envp->exported = 0;
	temp_envp->next = NULL;
	return (envp);
}

void	print_envp(t_envp *envp)
{
	while (envp->prev->position != 0)
		envp = envp->prev;
	envp = envp->prev;
	while (envp != NULL)
	{
		if (envp->exported == 1)
			ft_printf("%s=%s\n", envp->variable, envp->content);
		envp = envp->next;
	}
}

void	building_execute(int comand, t_pipes *pipes, t_envp *envp)
{
	char	**temp;

	temp = ft_split(pipes->vars[0], '=');
	if (comand == 0)
	{
		while (ft_strcmp(envp->variable, "PWD") != 0)
			envp = envp->prev;
		ft_printf("%s\n", envp->content);
	}
	else if (comand == 1)
	{
		envp = litnew(temp, envp);
		return ;
	}
	else if (comand == 2)
		print_envp(envp);
	exit(0);
}

void	execveloop(char **str, char **path)
{
	char	*bin;
	int		count;

	count = 0;
	while (path[count] != 0)
	{
		bin = ft_strcat(path[count], *str);
		execve(bin, str, 0);
		free (bin);
		count++;
	}
	ft_printf("%s: command not found\n", *str);
	exit(127);
}

void	pipex(t_pipes *pipes, t_envp *envp)
{
	int		status;
	int		id;
	int		count;
	char	**path;

	while (ft_strcmp(envp->variable, "PATH") != 0)
		envp = envp->next;
	path = ft_split(envp->content, ':');
	count = -1;
	while (path[++count] != 0)
		path[count] = ft_strjoin(path[count], "/");
	if (building_comp(pipes->command[0]) >= 0)
	{
		printf("%s", pipes->command[0]);
		building_execute(building_comp(pipes->command[0]), pipes, envp);
	}
	id = fork();
	if (id == 0)
	{
		execveloop(pipes->command, path);
	}
	waitpid(id, &status, 0);
}
