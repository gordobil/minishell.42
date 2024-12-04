/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:11:48 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/02 14:41:33 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_mini	*mini)
{
	//pipex(mini->pipes, mini->envp);


////////////  B U I L T - I N S   T E S T I N G  ////////////
	int	comm = building_comp(mini->pipes->command[0]);
	if (comm == -1)
		return ;
	else if (comm == 3)
		ms_cd(mini->pipes, mini->envp);
	else if (comm == 4)
		ms_echo(mini->pipes);
	else if (comm == 5)
		ms_unset(mini->pipes, mini->envp);

}

void	parsing(t_mini *mini, char **envp)
{
	arg_vars(mini);
	pipe_info(mini->arg_matrix, mini, 0);
	if (mini->del_c > 0)
		delimiters(mini);
	open_fds(mini);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rdline;
	t_mini	*mini;

	ft_printf ("\n");
	mini = malloc(sizeof(t_mini));
	load_envp(mini, envp);
	while (1)
	{
		rdline = rdl_management();
		if (!rdline || ft_strcmp(rdline, "exit") == 0)
			break ;
		add_history(rdline);
		if (split_args(rdline, mini) == 0 && mini->arg_c > 0)
		{
			parsing(mini, envp);
			execute(mini);
			printttttttt(mini);
			freeing(mini);
		}
		free(rdline);
	}
	free_envp(mini->envp);
	free(mini);
	if (rdline)
		free(rdline);
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}

//valgrind --leak-check=yes ./minishell
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
