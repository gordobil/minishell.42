/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:04:13 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/12 00:04:13 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_export(t_pipes *pipes, t_envp *envp)
{
	t_envp	*var;
	char	*content;
	int		i;

	while (envp->prev != NULL)
		envp = envp->prev;
	i = 1;
	while (pipes->command[i] != NULL)
	{
		var = envp;
		while (var != NULL)
		{
			if (ft_strcmp(pipes->command[i], var->variable) == 0)
			{
				if (content != NULL)
					free(content);
				content = ft_strdup(var->content);
			}
			var = var->next;
		}
		var = envp;
		i++;
	}
}
