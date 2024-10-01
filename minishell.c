/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/30 11:57:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *args)
{
	return ;
}

int	check_args(char *args)
{
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;
	int		i = 0;

	while(envp[i])
		printf("%s\n", envp[i++]);
//	info->args = readline("minishell¬");
	if (check_args(info->args) != 0)
    	return (-1);
  	minishell(info->args);
  	return (0);
}
