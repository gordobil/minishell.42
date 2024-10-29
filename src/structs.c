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
}

void	dup_args(char **arg_matrix, t_mini *mini, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while ((ft_strcmp(arg_matrix[i], "|") != 0) && (arg_matrix[i] != NULL)
			&& (mini->pipes->command[j] != NULL))
	{
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
		{
			mini->pipes->command[j] = ft_strdup(arg_matrix[i]);
			j++;
		}
		else
		{
			if (k < mini->file_c - 1)
			{
				mini->files[k] = ft_strdup(arg_matrix[i]);
				k++;
			}
			i++;
		}
		if (arg_matrix[i] == NULL || ft_strcmp(arg_matrix[i], "|") == 0)
			break ;
	}
	mini->pipes->command[j] = NULL;
	mini->files[k] = NULL;
}

int	count_args(char **arg_matrix, t_mini *mini, int i, char ret)
{
	int	count;

	count = 0;
	while (arg_matrix[i] != NULL)
	{
		if (ft_strcmp(arg_matrix[i], "|") == 0)
			break ;
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
			count++;
		else if (arg_matrix[i][0] == '<')
		{
			mini->file_c++;
			mini->infile = ft_strdup(arg_matrix[i]);
		}
		else if (arg_matrix[i][0] == '>')
		{
			mini->file_c++;
			mini->outfile = ft_strdup(arg_matrix[i]);
		}
		i++;
	}
	if (ret == 'i')
		return (i);
	return (count);
}

void	pipe_info(char **arg_matrix, t_mini *mini)
{
	t_pipes	*prev_node;
	int		i;
	int		position;
	int		arguments;

	mini->arg_matrix = NULL;
	mini->infile = NULL;
	mini->outfile = NULL;
	mini->pipes = NULL;
	mini->file_c = 0;
	i = 0;
	position = 0;
	while (arg_matrix[i] != NULL)
	{
		mini->pipes = malloc(sizeof(t_pipes));
		mini->pipes->mini = mini;
		mini->pipes->position = position;
		arguments = count_args(arg_matrix, mini, i, 'c');
		mini->pipes->command = malloc((arguments + 1) * sizeof(char *));
		mini->pipes->command[arguments] = NULL;
		mini->files = malloc(mini->file_c * sizeof(char *));
		ft_printf("1\n");
		if (arguments == mini->arg_c)
			return (single_command(arg_matrix, mini));
		ft_printf("2\n");
		dup_args(arg_matrix, mini, i);
		ft_printf("3\n");
		if (position == 0)
			mini->pipes->prev = NULL;
		else
		{
			mini->pipes->prev = prev_node;
			mini->pipes->prev->next = mini->pipes;
		}
		prev_node = mini->pipes;
		ft_printf("%m\n", mini->pipes->command);
		if (arg_matrix[count_args(arg_matrix, mini, i, 'i')] == NULL)
		{
			mini->pipes->next = NULL;
			break ;
		}
		i = count_args(arg_matrix, mini, i, 'i');
		if (ft_strcmp(arg_matrix[i], "|") == 0)
			i++;
		ft_printf("4\n");
		mini->pipes = mini->pipes->next;
		position++;
	}
}
