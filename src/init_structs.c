/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:02:08 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/08 12:02:08 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			mini->in_delimiter[j] = ft_strdup(mini->arg_matrix[i]);
			j++;
		}
		i++;
	}
	mini->in_delimiter[j] = NULL;
}

void	start_structs(t_mini *mini)
{
	int	i;

	mini->pipes = NULL;
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
		mini->in_delimiter = malloc((mini->del_c + 1) * sizeof(char *));
		save_delimiters(mini);
	}
	else
		mini->in_delimiter = NULL;
}

int	init_structs(t_mini *mini, int i, int position)
{
	int	arguments;

	arguments = 0;
	if (position == -1)
		start_structs(mini);
	else
	{
		mini->pipes = malloc(sizeof(t_pipes));
		mini->pipes->mini = mini;
		mini->pipes->position = position;
		mini->pipes->infile = NULL;
		mini->pipes->outfile = NULL;
		mini->pipes->append = NULL;
		arguments = count_args(mini->arg_matrix, mini, i, 'c');
		mini->pipes->command = malloc((arguments + 1) * sizeof(char *));
	}
	return (arguments);
}
