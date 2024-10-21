/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/21 15:27:27 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int		i = 0;

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
		mini.args = split_args(rdline, &mini);
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
  	return (0);
}
