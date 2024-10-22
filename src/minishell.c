/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/22 13:17:55 by ngordobi         ###   ########.fr       */
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
	int		i;

	i = 0;
	while (arg_matrix[i] != NULL)
	{
		args = malloc(sizeof(t_args));
		args->arg = arg_matrix[i];
		args->position = i;
		args->type = arg_type(arg_matrix[i]);
	}
}

void	mini_init(t_mini *mini)
{
	mini->rdline = NULL;
	mini->args = NULL;
	mini->arg_c = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*rdline;

	ft_printf ("\n");
	mini_init(&mini);
	while (1)
	{
		signal(SIGINT, rdl_signals);
		signal(SIGQUIT, SIG_IGN);
		rdline = readline(mini_title());
		if (!rdline || ft_strncmp(rdline, "exit", 5) == 0)
			break ;
		add_history(rdline);
		mini.arg_matrix = split_args(rdline, &mini);
		mini.args = arg_info(mini.arg_matrix);
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
