/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/31 15:17:01 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			pipe_info(mini.arg_matrix, &mini);
			while (mini.pipes != NULL)
			{
				ft_printf("%m\n", mini.pipes->command);
				mini.pipes = mini.pipes->next;
			}
			ft_printf("\nfiles:%d\n%m\n\nin:%s out:%s\n", mini.file_c, mini.files, mini.infile, mini.outfile);
		}
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
