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

void	dup_args(char **arg_matrix, t_mini *mini, int i, int arguments)
{
	int			j;
	static int	k;

	j = 0;
	while (ft_strcmp(arg_matrix[i], "|") != 0 && arg_matrix[i] != NULL)
	{
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>'
			&& ft_strcmp(arg_matrix[i], "|") != 0 && j < arguments)
		{
			mini->pipes->command[j] = ft_strdup(arg_matrix[i]);
			j++;
		}
		else if ((arg_matrix[i][0] == '<' || arg_matrix[i][0] == '>')
				&& (k < mini->file_c) && file_count(arg_matrix, i, 'r') < 0)
		{
			mini->files[k] = ft_strdup(arg_matrix[i]);
			k++;
		}
		i++;
		if (arg_matrix[i] == NULL || ft_strcmp(arg_matrix[i], "|") == 0)
			break ;
	}
	mini->pipes->command[j] = NULL;
	mini->files[k] = NULL;
}

void	single_command(char **arg_matrix, t_mini *mini)
{
	int	i;

	i = 0;
	while (arg_matrix[i] != NULL)
	{
		mini->pipes->command[i] = ft_strdup(arg_matrix[i]);
		i++;
	}
	mini->pipes->command[i] = NULL;
	mini->pipes->prev = NULL;
	mini->pipes->next = NULL;
	mini->files[0] = NULL;
}

int	init_structs(t_mini *mini, int i, int position)
{
	int	arguments;

	arguments = 0;
	if (position == -1)
	{
		mini->infile = NULL;
		mini->outfile = NULL;
		mini->pipes = NULL;
		mini->file_c = file_count(mini->arg_matrix, 0, 'c');
		if (mini->file_c <= 0)
			mini->files = NULL;
		else
			mini->files = malloc((mini->file_c + 1) * sizeof(char *));
	}
	else
	{
		mini->pipes = malloc(sizeof(t_pipes));
		mini->pipes->mini = mini;
		mini->pipes->position = position;
		
		arguments = count_args(mini->arg_matrix, mini, i, 'c');
		mini->pipes->command = malloc((arguments + 1) * sizeof(char *));
	}
	return (arguments);
}

void	pipe_info(char **arg_matrix, t_mini *mini)
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
			return (single_command(arg_matrix, mini));
		dup_args(arg_matrix, mini, i, arguments);
		update_nodes(mini, position);
		i = count_args(arg_matrix, mini, i, 'i');
		if (arg_matrix[i] == NULL)
		{
			mini->pipes->next = NULL;
			break ;
		}
		else if (ft_strcmp(arg_matrix[i], "|") == 0)
			i++;
		mini->pipes = mini->pipes->next;
	}
	update_nodes(mini, -1);
}
