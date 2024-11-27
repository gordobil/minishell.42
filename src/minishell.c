/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:48 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/27 19:46:50 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_mini	*mini)
{
	//pipex(mini->pipes, mini->envp);
}

void	parsing(t_mini *mini, char **envp)
{
	load_envp(mini, envp);
	pipe_info(mini->arg_matrix, mini, 0);
	if (mini->del_c > 0)
		delimiters(mini);
	open_fds(mini);
	//printttttttt(mini);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rdline;
	t_mini	mini;

	ft_printf ("\n");
	while (1)
	{
		rdline = rdl_management();
		if (!rdline || ft_strcmp(rdline, "exit") == 0)
			break ;
		add_history(rdline);
		if (split_args(rdline, &mini) == 0 && mini.arg_c > 0)
		{
			parsing(&mini, envp);
			execute(&mini);
			freeing(&mini);
		}
		free(rdline);
	}
	if (rdline)
		free(rdline);
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}

//valgrind --leak-check=yes ./minishell
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
