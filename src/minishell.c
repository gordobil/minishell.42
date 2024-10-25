/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/25 11:27:33 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	arg_type(char *arg)
{
	if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
		return ('2');
	else if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		return ('q');
	else if (arg[0] == '<' && arg[1] != '<')
		return ('i');
	else if (arg[0] == '>' && arg[1] != '>')
		return ('o');
	else if (arg[0] == '<' && arg[1] == '<')
		return ('d');
	else if (arg[0] == '>' && arg[1] == '>')
		return ('a');
	else if (arg[0] == '|' && arg[1] == '\0')
		return ('p');
	else if (arg[0] == '$' && arg[1] != '\0')
		return ('v');
	else
		return (0);
}

t_args	*arg_info(char **arg_matrix)
{
	t_args	*args;
	t_args	*prev_node;
	int		i;

	i = 0;
	while (arg_matrix[i] != NULL)
	{
		args = malloc(sizeof(t_args));
		args->arg = arg_matrix[i];
		args->position = i;
		args->type = arg_type(arg_matrix[i]);
		if (i == 0)
			args->prev = NULL;
		else
			args->prev = prev_node;
		if (arg_matrix[i + 1] == NULL)
			args->next = NULL;
		prev_node = args;
		args = args->next;
		i++;
	}
	while (args->prev != NULL)
		args = args->prev;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*rdline;

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
		ft_printf("%m\n", mini.arg_matrix);
		/* if (mini.arg_matrix != NULL)
			mini.args = arg_info(mini.arg_matrix); */
		/* while (mini.args != NULL)
		{
			ft_printf("[%d|%c]%s/\n", mini.args->position, mini.args->type, mini.args->arg);
			mini.args = mini.args->next;
		} */
		//free_mini(&mini);
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
