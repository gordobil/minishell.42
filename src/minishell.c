/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/08 12:26:55 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printttttttt(t_mini	*mini)
{
	while (mini->pipes != NULL)
	{
		ft_printf("NODE [%d]\n\n%m", mini->pipes->position, mini->pipes->command);
		ft_printf("\nFiles:\nin:%s out:%s app:%s\n\n.............\n\n", mini->pipes->infile, mini->pipes->outfile, mini->pipes->append);
		mini->pipes = mini->pipes->next;
	}
	ft_printf("File count: %d\n", mini->file_c);
	if (mini->files)
		ft_printf("%m\n", mini->files);
	ft_printf("Delimiter count: %d\n", mini->del_c);
	if (mini->in_delimiter)
		ft_printf("%m\n", mini->in_delimiter);
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
		ft_printf("\nMATRIX\n----------------\n%m----------------\n\n", mini.arg_matrix);
		if (mini.arg_matrix)
		{
			pipe_info(mini.arg_matrix, &mini, 0);
			printttttttt(&mini);
		}
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
