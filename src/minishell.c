/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/14 14:21:36 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rdl_signals(int sig)
{
	(void)sig;
	ft_printf("/n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*rdline;
	int		i = 0;

	ft_printf ("\n");
	while (1)
	{
		signal(SIGINT, rdl_signals);
		signal(SIGQUIT, SIG_IGN);
		rdline = readline(mini_title());
		if (!rdline || ft_strncmp(rdline, "exit", 5) == 0)
			break ;
		add_history(rdline);
		mini->args = split_args(rdline);
		ft_printf("%m\n", mini->args);
		if (mini->args[0] == NULL)
			break ;
		
		/* if (parser(rdline) != 0)
			break ; */
		free(rdline);
	}
	ft_printf("exit\n");
	clear_history();
  	return (0);
}
