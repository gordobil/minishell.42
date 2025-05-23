/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:17:58 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/15 13:17:58 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_delimiters(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini->arg_matrix[i] != NULL)
	{
		if (mini->arg_matrix[i][0] == '<' && mini->arg_matrix[i][1] == '<')
		{
			mini->delimiters[j] = ft_strdup(mini->arg_matrix[i]);
			j++;
		}
		i++;
	}
	mini->delimiters[j] = NULL;
}

void	start_structs(t_mini *mini)
{
	int	i;

	mini->pipes = NULL;
	mini->comm_c = 0;
	mini->file_c = file_count(mini->arg_matrix, 0, 'c');
	if (mini->file_c > 0)
		mini->files = malloc((mini->file_c + 1) * sizeof(char *));
	else
		mini->files = NULL;
	i = -1;
	mini->del_c = 0;
	while (mini->arg_matrix[++i] != NULL)
	{
		if (mini->arg_matrix[i][0] == '<' && mini->arg_matrix[i][1] == '<')
			mini->del_c++;
	}
	if (mini->del_c > 0)
	{
		mini->delimiters = malloc((mini->del_c + 1) * sizeof(char *));
		save_delimiters(mini);
	}
	else
		mini->delimiters = NULL;
}

int	init_structs(t_mini *mini, int i, int position)
{
	if (position == -1)
		start_structs(mini);
	else
	{
		mini->pipes = malloc(sizeof(t_pipes));
		mini->pipes->mini = mini;
		mini->pipes->position = position;
		mini->pipes->command = NULL;
		mini->pipes->pids = -1;
		mini->pipes->args = 0;
		mini->pipes->var_c = 0;
		mini->pipes->vars = NULL;
		mini->pipes->infile = malloc(sizeof(t_files));
		mini->pipes->infile->file = NULL;
		mini->pipes->outfile = malloc(sizeof(t_files));
		mini->pipes->outfile->file = NULL;
		mini->pipes->append = malloc(sizeof(t_files));
		mini->pipes->append->file = NULL;
		mini->pipes->delimiter = malloc(sizeof(t_files));
		mini->pipes->delimiter->file = NULL;
		count_args(mini->arg_matrix, mini->pipes, i, 'c');
		if (mini->pipes->args > 0)
			mini->pipes->command = malloc((mini->pipes->args + 1)
					* sizeof(char *));
	}
}

int	pipes_end(char **arg_matrix, int i, t_mini *mini)
{
	if (arg_matrix[i] == NULL)
	{
		mini->pipes->next = NULL;
		return (-1);
	}
	if (ms_strcmp(arg_matrix[i], "|") == 0)
		i++;
	if (arg_matrix[i] == NULL)
	{
		mini->pipes->next = NULL;
		return (error_messages(-9, NULL), -2);
	}
	return (i);
}
