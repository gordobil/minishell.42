/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2024/12/17 14:30:08 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* t_envp	*litnew(char **variable, t_envp *envp)
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
} */

int	building_execute(t_mini *mini, t_pipes *pipe, t_envp *envp)
{
	if (pipe != NULL && pipe->command != NULL && pipe->command[0] != NULL)
	{
		if (ft_strcmp(pipe->command[0], "cd") == 0)
			ms_cd(pipe, envp);
		else if (ft_strcmp(pipe->command[0], "echo") == 0)
			ms_echo(pipe);
		else if (ft_strcmp(pipe->command[0], "env") == 0)
			ms_env(envp);
		else if (ft_strcmp(pipe->command[0], "export") == 0)
			ms_export(pipe, envp);
		else if (ft_strcmp(pipe->command[0], "pwd") == 0)
			ms_pwd(envp);
		else if (ft_strcmp(pipe->command[0], "unset") == 0)
			ms_unset(pipe, envp);
		else if (pipe->args == pipe->var_c)
			add_vars(pipe, mini);
		else
			return (-1);
	}
	return (0);
}

void	execveloop(char **str, char **path)
{
	char	*bin;
	int		count;

	while (is_it_a_var(*str) > 0)
		*str++;
	count = 0;
/* 	if (ft_strcmp(*str, "/bin/") == 0)
	{
		printf("Concha entro\n");
		bin = "ls";
		execve(*str, bin, 0);
	} */
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

	if (!pipes || !pipes->command || !pipes->command[0])
		return ;
	while (ft_strcmp(envp->variable, "PATH") != 0)
		envp = envp->next;
	path = ft_split(envp->content, ':');
	count = -1;
	while (path[++count] != 0)
		path[count] = ft_strjoin(path[count], "/");
	while (envp->prev != NULL && envp->position != 0)
		envp = envp->prev;
	if (building_execute(pipes->mini, pipes, envp) == -1)
	{
		id = fork();
		if (id == 0)
			execveloop(pipes->command, path);
		waitpid(id, &status, 0);
	}
}
