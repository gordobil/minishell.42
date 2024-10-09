/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:26 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/09 19:16:23 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ms_title(void)
{
	char	*title;
	char	buffer[4096];

	title = ft_strjoin(BLUE"minishell:"WHITE"~", getcwd(buffer, 4096));
	title = ft_strjoin(title, BLUE"¬ "WHITE);
	return (title);
}

int	main(void)
{
	t_mini	*mini;
	int		i = 0;

	while (1)
	{
		mini->rdline = readline(ms_title());
		break ;
	}
  	return (0);
}
