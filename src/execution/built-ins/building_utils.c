/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:54:57 by mafarto-          #+#    #+#             */
/*   Updated: 2025/01/31 18:26:15 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	building_utils(t_mini *mini, t_pipes *pipe, int i)
{
	if (ft_strcmp(pipe->command[i], "$?") == 0)
		return (("%d: command not found\n", mini->last_ret), 0);
	else if (pipe->args == pipe->var_c)
		return (add_vars(pipe, mini), 0);
}
