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

void	rdl_signals(int sig)
{
	(void)sig;
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

	start = ft_strjoin(BLUE"minishell: "YELLOW"~", getcwd(buffer, 4096));
	title = ft_strjoin(start, BLUE"\n ¬ "WHITE);
	free (start);
	return (title);
}

char	*rdl_management(void)
{
	char	*title;
	char	*line;

	signal(SIGINT, rdl_signals);
	signal(SIGQUIT, SIG_IGN);
	title = mini_title();
	line = readline(title);
	free(title);
	return (line);
}

void	error_messages(int error)
{
	if (error == -1)
		ft_printf("error: unclosed quotes\n");
	else if (error == -2)
		ft_printf("error: unclosed double quotes\n");
}
