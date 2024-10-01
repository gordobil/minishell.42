/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/01 11:37:55 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_mini *mini)
{
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		i = 0;

	mini->arg_count = argc;
	mini->args = argv;
	mini->envp = envp;
	while(envp[i])
		printf("%s\n", envp[i++]);
	if (check_args(mini) != 0)
    	return (-1);
  	minishell(mini);
  	return (0);
}
