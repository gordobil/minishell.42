/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:53:30 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/31 14:53:30 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rdl_signals(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	ft_printf("%s", mini_title());
	rl_redisplay();
}

char	*mini_title(void)
{
	char	*title;
	char	buffer[4096];

	title = ft_strjoin(BLUE"minishell: "YELLOW"~", getcwd(buffer, 4096));
	title = ft_strjoin(title, BLUE"\n ¬ "WHITE);
	return (title);
}

void	error_message(int error)
{
	if (error == -1)
		ft_printf("error: unclosed quotes\n");
	else if (error == -2)
		ft_printf("error: unclosed double quotes\n");
}


