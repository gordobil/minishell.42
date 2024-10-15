/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:50:12 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/11 18:50:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rdl_signals(int sig)
{
	(void)sig;
	ft_printf("/n");
	rl_replace_line("", 0);
	rl_on_new_line();
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

int	arg_errors(int error)
{
	if (error == 0)
		ft_printf ("\n");
	else if (error == -1)
		ft_printf ("error: unclosed simple quotes.");
	else if (error == -2)
		ft_printf ("error: unclosed double quotes.");
	else if (error == -3)
		ft_printf ("error: error reading commands.");
	return (error);
}
