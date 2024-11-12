/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:16:55 by codespace         #+#    #+#             */
/*   Updated: 2024/11/12 17:08:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    load_name(char **envp, t_envp *envp_p, int i, int j)
{
    int k;

    k = j;
    while (envp[i][j] != '\0')
        j++;
    envp_p->name = malloc((j - k + 1) * sizeof(char));
    j = 0;
    while (envp[i][k] != '\0')
    {
        envp_p->name[j] = envp[i][k];
        j++;
        k++;
    }
    envp_p->name[j] = '\0';
}

int load_variable(char **envp, t_envp *envp_p, int i)
{
    int j;

    j = 0;
    while (envp[i][j] != '=')
        j++;
    envp_p->variable = malloc((j + 1) * sizeof(char));
    j = 0;
    while (envp[i][j] != '=')
    {
        envp_p->variable[j] = envp[i][j];
        j++;
    }
    envp_p->variable[j] = '\0';
    j++;
    return (j);
}

void    load_envp(t_mini *mini, char **envp)
{
    int     i;
    int     j;
    int     k;
    t_envp  *envp_p;
    t_envp  *prev;

    i = 0;
    mini->envp = NULL;
    envp_p = mini->envp;
    ft_printf("ENVP\n\n");
    while (envp[i] != NULL)
    {
        envp_p = malloc (sizeof(t_envp));
        envp_p->position = i;
    ft_printf("ENVP:%s\n", envp[i]);
    ft_printf("position:%d\n", envp_p->position);
        j = load_variable(envp, envp_p, i);
    ft_printf("variable:%s\n", envp_p->variable);
        load_name(envp, envp_p, i, j);
    ft_printf("name:%s\n\n", envp_p->name);
        if (i == 0)
            envp_p->prev = NULL;
        else
            envp_p->prev = prev;
        envp_p->prev->next = envp_p;
        if (envp[i + 1] == NULL)
            envp_p->next = NULL;
        prev = envp_p;
        i++;
        envp_p = envp_p->next;
    }
}
