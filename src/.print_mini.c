/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .print_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:22:16 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/03 14:33:35 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ms_print_envp(t_envp *envp)
{
	while (envp->prev != NULL)
		envp = envp->prev;
	ft_printf("\n\n-------------------------------------\n		ENVP\n");
	ft_printf("-------------------------------------\n\n");
	while (envp != NULL)
	{
		ft_printf("[%d / %d] %s\n%s\n", envp->position, envp->exported,
			envp->variable, envp->content);
		ft_printf("   prev:%p node:%p next:%p\n", envp->prev, envp, envp->next);
		ft_printf("\n");
		envp = envp->next;
	}
}

void	ms_print_pipes(t_pipes *command)
{
	while (command != NULL)
	{
		ft_printf("NODE [%d]: %d\n", command->position, command->args);
		if (command->command)
			ft_printf("\n%m", command->command);
		else
			ft_printf ("\n");
		ft_printf("\nFiles:\nin:%s ", command->infile->file);
		ft_printf("out:%s ", command->outfile->file);
		ft_printf("app:%s ", command->append->file);
		ft_printf("del:%s\n\n", command->delimiter->file);
		ft_printf("var_c: %d\n", command->var_c);
		if (command->vars)
			ft_printf("%m", command->vars);
		ft_printf("\n....................................\n");
		command = command->next;
	}
}

void	ms_print_mini(t_mini *mini, int enviroment)
{
	t_pipes	*command;
	t_envp	*envp;

	command = mini->pipes;
	envp = mini->envp;
	ft_printf("\n\n-------------------------------------\n		MATRIX\n");
	ft_printf("-------------------------------------\n%m", mini->arg_matrix);
	ft_printf("-------------------------------------\n\n\n");
	ms_print_pipes(command);
	ft_printf("\nCommand count: %d\n\n", mini->comm_c);
	ft_printf("File count: %d\n\n", mini->file_c);
	if (mini->files)
		ft_printf("%m.........\n\n", mini->files);
	ft_printf("Delimiter count: %d\n\n", mini->del_c);
	if (mini->delimiters)
		ft_printf("%m.........\n\n", mini->delimiters);
	if (enviroment == 1)
		ms_print_envp(envp);
}
