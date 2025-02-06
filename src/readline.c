/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:44:57 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/15 11:44:57 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	g_signals;

void	rdl_new_line(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*mini_title(void)
{
	char	*title;
	char	*start;
	char	buffer[4096];

	start = ft_strjoin(BLUE"minishell: "YELLOW, getcwd(buffer, 4096));
	title = ft_strjoin(start, BLUE"\n ¬ "WHITE);
	free (start);
	return (title);
}

char	*rdl_management(void)
{
	char	*title;
	char	*line;

	signal(SIGINT, rdl_new_line);
	signal(SIGQUIT, SIG_IGN);
	title = mini_title();
	line = readline(title);
	free(title);
	return (line);
}
