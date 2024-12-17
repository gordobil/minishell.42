/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:54:47 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/11 23:54:47 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_env(t_envp *envp, t_pipes *pipe)
{
	t_envp	*var;

	if (!envp || envp == NULL)
		return ;
	var = envp;
	if (pipe->command[1] != NULL)
	{
		if (ft_strcmp(pipe->command[1], "-a") == 0)
			printtt_envp(var);
		error_messages(-5, "env");
		return ;
	}
	while (var != NULL)
	{
		if (var->exported == 1 && var->variable != NULL
			&& var->content != NULL)
			ft_printf("%s=%s\n", var->variable, var->content);
		var = var->next;
	}
}
