/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:48 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/22 11:52:19 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_mini	*mini)
{
	pipex(mini->pipes->command, mini->envp);
}

void	parsing(t_mini *mini, char **envp)
{
	load_envp(mini, envp);
	pipe_info(mini->arg_matrix, mini, 0);
	if (mini->del_c > 0)
		delimiters(mini);
}
	//printttttttt(mini);

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
		mini.arg_matrix = split_args(rdline, &mini);
		if (mini.arg_matrix)
		{
			parsing(&mini, envp);
			execute(&mini);
			freeing(&mini);
		}
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}

//valgrind --leak-check=yes ./minishell
