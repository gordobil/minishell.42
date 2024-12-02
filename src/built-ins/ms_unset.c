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

void	ms_unset(t_pipes *pipe, t_envp *envp)
{
	t_envp	*p_envp;
	int		i;

	i = 1;
	while (pipe->command[i] != NULL)
	{
		p_envp = envp;
		while (p_envp != NULL)
		{
			if (ft_strcmp(p_envp->variable, pipe->command[i]) == 0)
			{
				p_envp->prev->next = p_envp->next;
				p_envp->next->prev = p_envp->prev;
				free(p_envp->content);
				free(p_envp->variable);
				free(p_envp);
				break ;
			}
			p_envp = p_envp->next;
		}
		i++;
	}
}