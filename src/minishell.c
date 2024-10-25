/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/25 13:58:03 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_args	*arg_info(char **arg_matrix)
{
	t_args	*args;
	t_args	*prev_node;
	int		i;

	i = 0;
	while (arg_matrix[i] != NULL)
	{
		args = malloc(sizeof(t_args));
		args->arg = ft_strdup(arg_matrix[i]);
		args->position = i;
		if (i == 0)
			args->prev = NULL;
		else
			args->prev = prev_node;
		prev_node = args;
		if (arg_matrix[i + 1] == NULL)
		{
			args->next = NULL;
			break ;
		}
		args = args->next;
		i++;
	}
	ft_printf("%s\n", args->arg);
	while (args->prev != NULL)
		args = args->prev;
	ft_printf("%s\n", args->arg);
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*rdline;
	t_args	*args;

	ft_printf ("\n");
	while (1)
	{
		signal(SIGINT, rdl_signals);
		signal(SIGQUIT, SIG_IGN);
		rdline = readline(mini_title());
		if (!rdline || ft_strncmp(rdline, "exit", 5) == 0)
			break ;
		add_history(rdline);
		mini.arg_matrix = split_args(rdline, &mini);
		if (mini.arg_matrix)
			args = arg_info(mini.arg_matrix);
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
