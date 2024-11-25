/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2024/11/25 11:39:17 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	building_execute(int comand)
{
	if (comand == 0)
	{
		ft_printf("si\n");
		exit(1);
	}
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
		count++;
	}
	free (bin);
	ft_printf("%s: command not found\n", *str);
	exit(127);
}

void	pipex(char **str, t_envp *envp)
{
	int		status;
	int		id;
	char	**path;

	id = fork();
	while (ft_strcmp(envp->variable, "PATH") != 0)
		envp = envp->next;
	path = ft_split(envp->content, ':');
	if (id == 0)
	{
		if (building_comp(str[0]) >= 0)
			building_execute(building_comp(str[0]));
		execveloop(str, path);
	}
	waitpid(id, &status, 0);
	free_matrix(path);
}
