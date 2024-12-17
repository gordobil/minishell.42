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
		if (var->prev != NULL && var->position > var->prev->position + 1)
		{
			while (var->position > var->prev->position + 1)
				var->position = var->position - 1;
		}
		var = var->next;
	}
}

void	unset_var(char *variable, t_envp *envp)
{
	t_envp	*var;
	t_envp	*del;

	var = envp;
	while (var != NULL)
	{
		if (ft_strcmp(var->variable, variable) == 0)
		{
			free(var->content);
			free(var->variable);
			if (var->next == NULL)
			{
				var = var->prev;
				free(var->next);
				var->next = NULL;
				break ;
			}
			else if (var->prev == NULL)
			{
				del = var;
				var = var->next;
				free(var->prev);
				var->prev = NULL;
				var->position--;
				envp_position(var);
				envp = envp->next;
				free(envp->prev);
			}
			else
			{
				del = var;
				var = var->prev;
				del->prev->next = del->next;
				del->next->prev = del->prev;
				envp_position(var);
				free(del);
			}
		}
		var = var->next;
	}
}

void	ms_unset(t_pipes *pipe, t_envp *envp)
{
	int	i;

	i = 1;
	while (pipe->command[i] != NULL)
	{
		unset_var(pipe->command[i], envp);
		i++;
	}
}
