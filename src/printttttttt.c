/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printttttttt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:44:06 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/21 13:44:06 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printtt_envp(t_envp *envp)
{
	while (envp->prev != NULL)
		envp = envp->prev;

	ft_printf("\n\n-------------------------------------\n		ENVP\n-------------------------------------\n\n");
	while (envp != NULL)
	{
		ft_printf("[%d] %s\n%s\n\n", envp->position, envp->variable, envp->content);
		envp = envp->next;
	}
}

void	printttttttt(t_mini	*mini)
{
	t_pipes	*command = mini->pipes;
	t_envp	*envp = mini->envp;

	ft_printf("\n\n-------------------------------------\n		MATRIX\n-------------------------------------\n%m-------------------------------------\n\n\n", mini->arg_matrix);
	while (command != NULL)
	{
		ft_printf("NODE [%d]\n", command->position);
		if (command->command)
			ft_printf("\n%m", command->command);
		ft_printf("\nVariables[%d]", command->var_c);
		if (command->vars)
			ft_printf(":\n%m", command->vars);
		else
			ft_printf ("\n");
		ft_printf("\nFiles:\nin:%s out:%s app:%s del:%s\n\n....................................\n\n", command->infile->file, command->outfile->file, command->append->file, command->delimiter->file);
		command = command->next;
	}
	ft_printf("\nCommand count: %d\n\n\n", mini->comm_c);
	ft_printf("File count: %d\n\n", mini->file_c);
	if (mini->files)
		ft_printf("%m\n\n", mini->files);
	ft_printf("Delimiter count: %d\n\n", mini->del_c);
	if (mini->delimiters)
		ft_printf("%m\n\n", mini->delimiters);

	//print_envp(envp);
}
