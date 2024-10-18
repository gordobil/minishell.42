/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/18 21:03:46 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_init(t_mini *mini)
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
		split_args(rdline, &mini);
		ft_printf("%m\n", mini.args);
		if (mini.args[0] == NULL)
			break ;
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
  	return (0);
}
