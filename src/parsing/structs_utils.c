/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:58:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/28 11:58:39 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_args_utils(t_mini **mini, int *j)
{
	if (ft_strcmp((*mini)->pipes->command[*j], "") == 0)
		free((*mini)->pipes->command[*j]);
	else
		j++;
}

void	mini_is_null(t_mini **mini, int *i)
{
	(*mini)->pipes->command[*i] = NULL;
	(*mini)->pipes->prev = NULL;
	(*mini)->pipes->next = NULL;
	(*mini)->files = NULL;
}
