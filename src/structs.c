/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:58:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/28 11:58:39 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_nodes(t_mini *mini, int position)
{
	static t_pipes	*prev_node;

	if (position == -1)
	{
		mini->comm_c = mini->pipes->position + 1;
		while (mini->pipes->prev != NULL)
			mini->pipes = mini->pipes->prev;
	}
	else
	{
		if (position == 0)
			mini->pipes->prev = NULL;
		else
		{
			mini->pipes->prev = prev_node;
			mini->pipes->prev->next = mini->pipes;
		}
		prev_node = mini->pipes;
	}
}

int	dup_args(int k, t_mini *mini, int i, int arguments)
{
	int			j;

	j = 0;
	while (mini->arg_matrix[i] != NULL
		&& ms_strcmp(mini->arg_matrix[i], "|") != 0)
	{
		if (mini->arg_matrix[i][0] != '<' && mini->arg_matrix[i][0] != '>'
			&& ms_strcmp(mini->arg_matrix[i], "|") != 0 && j < arguments)
		{
			mini->pipes->command[j] = ft_strdup(mini->arg_matrix[i]);
			j++;
		}
		else if ((mini->arg_matrix[i][0] == '<'
			|| mini->arg_matrix[i][0] == '>'))
			if (file_count(mini->arg_matrix, i, 'r') < 0)
				k = file_management(mini, i, k);
		i++;
	}
	mini->pipes->command[j] = NULL;
	if (k > 0)
		mini->files[k] = NULL;
	return (k);
}

void	plain_command(char **arg_matrix, t_mini *mini)
{
	int	i;

	mini->comm_c = 1;
	i = 0;
	while (arg_matrix[i] != NULL)
	{
		mini->pipes->command[i] = ft_strdup(arg_matrix[i]);
		i++;
	}
	mini->pipes->command[i] = NULL;
	mini->pipes->prev = NULL;
	mini->pipes->next = NULL;
	mini->files = NULL;
}

void	pipe_info(char **arg_matrix, t_mini *mini, int k)
{
	int		i;
	int		position;
	int		arguments;

	i = 0;
	position = -1;
	init_structs(mini, i, -1);
	while (arg_matrix[i] != NULL && ++position < mini->arg_c)
	{
		arguments = init_structs(mini, i, position);
		if (arguments == mini->arg_c)
			return (plain_command(arg_matrix, mini));
		k = dup_args(k, mini, i, arguments);
		update_nodes(mini, position);
		i = count_args(arg_matrix, mini, i, 'i');
		if (arg_matrix[i] == NULL)
		{
			mini->pipes->next = NULL;
			break ;
		}
		else if (ms_strcmp(arg_matrix[i], "|") == 0)
			i++;
		mini->pipes = mini->pipes->next;
	}
	update_nodes(mini, -1);
}
