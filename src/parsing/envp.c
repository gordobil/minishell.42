/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:38 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/30 20:23:30 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nodes_envp(t_envp *envp_p, t_envp *prev, int i, char **envp)
{
	if (i == 0 && envp_p->position == 0)
		envp_p->prev = NULL;
	else
	{
		envp_p->prev = prev;
		envp_p->prev->next = envp_p;
	}
	if (envp[i + 1] == NULL)
		envp_p->next = NULL;
}

void	load_var_cont(char **envp, t_envp *envp_p, int i)
{
	int	j;
	int	k;

	j = 0;
	while (envp[i][j] != '=')
		j++;
	envp_p->variable = ft_substr(envp[i], 0, j);
	k = ++j;
	while (envp[i][j] != '\0')
		j++;
	envp_p->content = ft_substr(envp[i], k, j - k);
}

void	load_envp(t_mini *mini, char **envp)
{
	int		i;
	int		j;
	t_envp	*prev;
	t_envp	*envp_p;

	i = 0;
	mini->last_ret = 0;
	mini->envp = malloc(sizeof(t_envp));
	if (!mini->envp)
		return ;
	envp_p = mini->envp;
	while (envp[i] != NULL)
	{
		envp_p->position = i;
		envp_p->exported = 1;
		load_var_cont(envp, envp_p, i);
		nodes_envp(envp_p, prev, i, envp);
		prev = envp_p;
		i++;
		envp_p = envp_p->next;
		envp_p = malloc (sizeof(t_envp));
	}
	free(envp_p);
}

int	add_vars(t_pipes *pipe, t_mini *mini)
{
	int		i;
	int		j;
	t_envp	*envp;
	t_envp	*prev;

	if (!pipe->vars)
		return (-1);
	envp = mini->envp;
	while (envp->next != NULL)
		envp = envp->next;
	i = -1;
	while (pipe->vars[++i] != NULL)
	{
		prev = envp;
		envp = envp->next;
		envp = malloc(sizeof(t_envp));
		if (!envp)
			return (-1);
		envp->position = prev->position + 1;
		envp->exported = 0;
		load_var_cont(pipe->vars, envp, i);
		nodes_envp(envp, prev, i, pipe->vars);
	}
	return (0);
}

t_envp	*get_edge_node(t_envp *envp, char edge)
{
	if (envp == NULL)
		return (NULL);
	if (edge == 's')
	{
		while (envp->prev != NULL && envp->position > 0)
			envp = envp->prev;
	}
	else if (edge == 'e')
	{
		while (envp->next != NULL)
			envp = envp->next;
	}
	return (envp);
}
