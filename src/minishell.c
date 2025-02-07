/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:48 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/07 15:19:12 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	end_mini(t_mini *mini, char *rdline)
{
	free_envp(mini->envp);
	free(mini);
	if (rdline)
		free(rdline);
	ft_printf("exit\n\n");
	clear_history();
}

int	parsing(t_mini *mini)
{
	arg_vars(mini);
	if (pipe_info(mini->arg_matrix, mini, 0, 0) == -2)
		return (-1);
	if (mini->del_c > 0)
		delimiters(mini);
	if (open_fds(mini) != 0)
		return (-2);
	if (mini->pipes->next == NULL && mini->pipes->prev == NULL)
		add_vars(mini->pipes, mini);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rdline;
	t_mini	*mini;
	int exit;

	ft_printf ("\n");
	mini = malloc(sizeof(t_mini));
	load_envp(mini, envp);
	while (1)
	{
		rdline = rdl_management();
		if (!rdline || (exit = ms_exit(rdline)) == 0)
			break ;
		else if (exit)
		{
			add_history(rdline);
			if (split_args(rdline, mini) == 0 && mini->arg_c > 0)
				if (parsing(mini) == 0)
					pipex(mini->pipes, mini->envp);
			if (mini->arg_c > 0)
				freeing(mini);
		}
		free(rdline);
	}
	end_mini(mini, rdline);
	return (0);
}
