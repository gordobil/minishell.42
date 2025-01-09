/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:45:59 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/02 13:45:59 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	envp_position(t_envp *var)
{
	while (var != NULL)
	{
		if (var->position > 0 && var->position > var->prev->position + 1)
		{
			while (var->position > var->prev->position + 1)
				var->position = var->position - 1;
		}
		var = var->next;
	}
}

void	unset_middle_var(t_envp *var)
{
	t_envp	*del;

	del = var;
	var = var->prev;
	del->prev->next = del->next;
	del->next->prev = del->prev;
	envp_position(var);
	free(del);
}

t_envp	*unset_edge_var(t_envp *var, t_envp *envp)
{
	if (var->next == NULL && var->prev != NULL)
	{
		var = var->prev;
		free(var->next);
		var->next = NULL;
	}
	else if (var->prev == NULL && var->next != NULL)
	{
		var = var->next;
		free(var->prev);
		var->prev = NULL;
		var->position = 0;
		envp_position(var);
		return (var);
	}
	else if (var->prev == NULL && var->next == NULL)
	{
		free(var);
		var = NULL;
		envp = NULL;
	}
	return (NULL);
}

t_envp	*unset_var(char *variable, t_envp *envp)
{
	t_envp	*var;
	t_envp	*del;
	t_envp	*ret;

	var = envp;
	ret = NULL;
	while (var != NULL)
	{
		if (ft_strcmp(var->variable, variable) == 0)
		{
			free(var->content);
			free(var->variable);
			if (var->next == NULL || var->prev == NULL)
				ret = unset_edge_var(var, envp);
			else
				unset_middle_var(var);
		}
		if (var->next == NULL)
			break ;
		var = var->next;
	}
	if (ret == NULL)
		return (get_edge_node(var, 's'));
	return (ret);
}

void	ms_unset(t_pipes *pipe, t_envp *envp)
{
	int	i;

	i = 0;
	while (pipe->command[++i] != NULL)
		envp = unset_var(pipe->command[i], envp);
	pipe->mini->envp = envp;
}
