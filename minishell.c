/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/07 14:21:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_mini *mini)
{
	printf ("%s\n", mini->rdline);
	return ;
}

int	main(void)
{
	t_mini	*mini;
	int		i = 0;

	mini->rdline = readline("minishell¬ ");
	if (check_args(mini) != 0)
    	return (-1);
  	minishell(mini);
  	return (0);
}
