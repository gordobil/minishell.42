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

int	is_it_a_var(char *str)
{
	int	i;
	int	v;

	if (str[0] == '<' || str[0] == '>' || str[0] == '"' || str[0] == '\''
		|| str[0] == '=' || (str[0] >= '0' && str[0] <= '9'))
		return (0);
	i = 0;
	v = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			v++;
		i++;
	}
	return (v);
}

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
	int	j;

	j = 0;
	while (mini->arg_matrix[i] != NULL
		&& ms_strcmp(mini->arg_matrix[i], "|") != 0)
	{
		if (mini->arg_matrix[i][0] != '<' && mini->arg_matrix[i][0] != '>'
			&& ms_strcmp(mini->arg_matrix[i], "|" ) && j < arguments
			&& mini->pipes->command)
		{
			mini->pipes->command[j] = rm_quotes(mini->arg_matrix[i], 0);
			j++;
		}
		else if ((mini->arg_matrix[i][0] == '<'
			|| mini->arg_matrix[i][0] == '>'))
			if (file_count(mini->arg_matrix, i, 'r') < 0)
				k = file_saving(mini, i, k);
		i++;
	}
	if (mini->pipes->command)
		mini->pipes->command[j] = NULL;
	if (k > 0)
		mini->files[k] = NULL;
	return (k);
}

int	plain_command(char **arg_matrix, t_mini *mini)
{
	int	i;
	int	j;

	mini->comm_c = 1;
	i = 0;
	j = 0;
	while (arg_matrix[j] != NULL)
	{
		if (ms_strcmp(arg_matrix[j], "|") != 0)
		{
			mini->pipes->command[i] = rm_quotes(arg_matrix[i], 0);
			i++;
		}
		j++;
	}
	save_vars(mini->pipes, mini->pipes->var_c);
	mini->pipes->command[i] = NULL;
	mini->pipes->prev = NULL;
	mini->pipes->next = NULL;
	mini->files = NULL;
	if (ms_strcmp(arg_matrix[j - 1], "|") == 0)
		return (error_messages(-9, NULL), -2);
	return (0);
}

int	pipe_info(char **arg_matrix, t_mini *mini, int i, int j)
{
	int		position;

	i = 0;
	position = -1;
	init_structs(mini, i, -1);
	while (arg_matrix[i] != NULL && ++position < mini->arg_c)
	{
		init_structs(mini, i, position);
		if (mini->pipes->args == mini->arg_c
			|| (mini->pipes->args == mini->arg_c - 1
			&& ms_strcmp(mini->arg_matrix[mini->pipes->args], "|") == 0))
			return (plain_command(arg_matrix, mini));
		j = dup_args(j, mini, i, mini->pipes->args);
		update_nodes(mini, position);
		i = count_args(arg_matrix, mini->pipes, i, 'i');
		save_vars(mini->pipes, mini->pipes->var_c);
		i = pipes_end(arg_matrix, i, mini);
		if (i < 0)
			break ;
		mini->pipes = mini->pipes->next;
	}
	update_nodes(mini, -1);
	return (i);
}
