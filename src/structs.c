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

void	single_comm(char **arg_matrix, t_mini *mini)
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

int	count_args(char **arg_matrix, t_mini *mini, int i, char ret)
{
	int	count;

	count = 0;
	while (arg_matrix[++i] != NULL)
	{
		if (arg_matrix[i][0] == '|' && arg_matrix[i][1] == '\0')
			break ;
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
			count++;
		else if (arg_matrix[i][0] == '<')
		{
			if (mini->infile != NULL)
				free(mini->infile);
			mini->infile = ft_strdup(arg_matrix[i]);
		}
		else if (arg_matrix[i][0] == '>')
		{
			if (mini->infile != NULL)
				free(mini->infile);
			mini->outfile = ft_strdup(arg_matrix[i]);
		}
	}
	if (ret == 'i')
		return (i);
	return (count);
}

void	dup_args(char **arg_matrix, t_mini *mini, int i)
{
	int	j;

	j = 0;
	while ((arg_matrix[i][0] != '|' && arg_matrix[i][1] != '\0')
		&& arg_matrix[i] != NULL)
	{
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
			mini->pipes->command[j] = ft_strdup(arg_matrix[i]);
		i++;
		j++;
	}
	mini->pipes->command[j] = NULL;
}

void	pipe_info(char **arg_matrix, t_mini *mini)
{
	t_pipes	*prev_node;
	int		i;
	int		position;

	i = 0;
	position = 0;
	while (arg_matrix[i] != NULL)
	{
		mini->pipes = malloc(sizeof(t_pipes));
		mini->pipes->mini = mini;
		mini->pipes->position = position;
		mini->pipes->command = malloc((count_args(arg_matrix, mini, i - 1, 'c') + 1)
				* sizeof(char *));
		ft_printf("MALLOCS\n");
		if (count_args(arg_matrix, mini, i - 1, 'c') == mini->arg_c)
			return (single_comm(arg_matrix, mini));
		ft_printf("1 ARG\n");
		dup_args(arg_matrix, mini, i);
		ft_printf("DUP ARGS\n");
		if (position == 0)
			mini->pipes->prev = NULL;
		else
		{
			mini->pipes->prev = prev_node;
			mini->pipes->prev->next = mini->pipes;
		}
		prev_node = mini->pipes;
		ft_printf("PREV NODE\n");
		if (arg_matrix[i + 1] == NULL)
		{
			mini->pipes->next = NULL;
			break ;
		}
		i = count_args(arg_matrix, mini, i - 1, 'i');
		if (arg_matrix[i][0] == '|')
			i++;
		ft_printf("---------------i:%d---------------\n", i);
		ft_printf("%m", mini->pipes->command);
		mini->pipes = mini->pipes->next;
		position++;
		ft_printf("\n");
	}
}
