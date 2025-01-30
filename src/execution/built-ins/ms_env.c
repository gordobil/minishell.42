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

#include "../../../includes/minishell.h"

int	ms_env(t_envp *envp, t_pipes *pipe, int i, int print_export)
{
	t_envp	*var;

	i++;
	if (!envp || envp == NULL)
		return (-1);
	var = envp;
	if (pipe->command[i] != NULL)
	{
		if (ft_strcmp(pipe->command[i], "-a") == 0)
			printtt_envp(var);
		return (error_messages(-5, "env"));
	}
	while (var != NULL)
	{
		if (print_export == 0 && var->exported == 1
			&& var->variable != NULL && var->content != NULL)
			ft_printf("%s=%s\n", var->variable, var->content);
		else if (print_export == 1 && var->exported == 1
			&& var->variable != NULL)
		{
			if (var->content != NULL)
				ft_printf("declare -x %s=\"%s\"\n", var->variable, var->content);
			else
				ft_printf("declare -x %s\n", var->variable);
		}
		var = var->next;
	}
	return (0);
}
