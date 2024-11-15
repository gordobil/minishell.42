/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:48 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/15 11:26:26 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freeing()
{
	namefiles(1);
}

void	executing()
{
	return ;
}

void	parsing(t_mini *mini, char **envp)
{
	load_envp(mini, envp);
	pipe_info(mini->arg_matrix, mini, 0);
	if (mini->del_c > 0)
		delimiters(mini);

	printttttttt(mini);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rdline;
	t_mini	mini;

	ft_printf ("\n");
	while (1)
	{
		signal(SIGINT, rdl_signals);
		signal(SIGQUIT, SIG_IGN);
		rdline = readline(mini_title());
		if (!rdline || ft_strcmp(rdline, "exit") == 0)
			break ;
		add_history(rdline);
		mini.arg_matrix = split_args(rdline, &mini);
		if (mini.arg_matrix)
		{
			parsing(&mini, envp);
			executing();
			freeing();
		}
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
