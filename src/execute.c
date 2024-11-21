/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:09 by mafarto-          #+#    #+#             */
/*   Updated: 2024/11/21 12:36:59 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execveloop(char **str, char **path)
{
    char	*bin;
    int		count;

    count = 0;
    while (path[count] != 0)
    {
        bin = ft_strrcat(path[count], *str);
    	execve(bin, str, 0);
    	count++;
    }
    free (bin);
    ft_printf("%s: command not found\n", *str);
    exit(127);
}

void pipex(char **str, t_envp *envp)
{
    int     status;
    int     id;
    char    **path;

    id = fork();
    while (ft_strncmp(envp->variable, "PATH", 4) != 0)
        envp = envp->next;
    path = ft_split(envp->content, ':');
    if (id == 0)
    {
        //ft_printf("%m", path);
        execveloop(str, path);
    }
    waitpid(id,&status,0);
}
