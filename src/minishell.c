/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:48 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/07 21:35:28 by ngordobi         ###   ########.fr       */
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
		if (delimiters(mini, mini->pipes) < 0)
			return(-2);
	if (open_fds(mini) != 0)
		return (-3);
	if (mini->pipes->next == NULL && mini->pipes->prev == NULL)
		add_vars(mini->pipes, mini);
	return (0);
}

t_mini	*init_mini(char **envp)
{
	t_mini	*mini;

	ft_printf ("\n");
	mini = malloc(sizeof(t_mini));
	load_envp(mini, envp);
	return (mini);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rdline;
	t_mini	*mini;
	int		exit;

	mini = init_mini(envp);
	while (1)
	{
		rdline = rdl_management();
		if (!rdline)
			break ;
		exit = ms_exit(rdline);
		if (exit <= 0)
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
	return (end_mini(mini, rdline), 0);
}
