/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:28:07 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/23 20:48:00 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mini(t_mini *mini)
{
	int	i;
	
	printf ("1\n");
	free(mini->rdline);
	i = -1;
	while (mini->arg_matrix[++i] != NULL)
		free(mini->arg_matrix[i]);
	free(mini->arg_matrix);
	while (mini->args != NULL)
	{
		free(mini->args->arg);
		free(mini->args->prev);
		mini->args = mini->args->next;
	}
	free(mini->args);
}
