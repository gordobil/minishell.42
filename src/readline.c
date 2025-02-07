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

void	rdl_new_line(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	ft_printf("%s", mini_title());
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

void	update_children_signals(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		ft_printf("\n");
	g_signals = signal;
}

void	*children_signals(t_mini *mini)
{
	t_pipes	*pipe;

	pipe = mini->pipes;
	signal(SIGINT, update_children_signals);
	signal(SIGQUIT, update_children_signals);
}
