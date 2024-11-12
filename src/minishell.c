/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/12 14:00:11 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printttttttt(t_mini	*mini)
{
	t_pipes	*command = mini->pipes;

	ft_printf("Command count: %d\n\n", mini->comm_c);
	while (command != NULL)
	{
		ft_printf("NODE [%d]\n\n%m", command->position, command->command);
		ft_printf("\nFiles:\nin:%s out:%s app:%s del:%s\n\n.............\n\n", command->infile->file, command->outfile->file, command->append->file, command->delimiter->file);
		command = command->next;
	}
	ft_printf("File count: %d\n\n", mini->file_c);
	if (mini->files)
		ft_printf("%m\n", mini->files);
	ft_printf("Delimiter count: %d\n\n", mini->del_c);
	if (mini->delimiters)
		ft_printf("%m\n", mini->delimiters);
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
		if (mini.arg_matrix)
		{
			ft_printf("\nMATRIX\n----------------\n%m----------------\n\n", mini.arg_matrix);
			pipe_info(mini.arg_matrix, &mini, 0);
			if (mini.del_c > 0)
				delimiters(&mini);
			printttttttt(&mini);
			namefile_gen(1);
		}
		free(rdline);
	}
	ft_printf("exit\n\n");
	clear_history();
	return (0);
}
