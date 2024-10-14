/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/14 12:17:48 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "./libft.h"

//COLORS
# define BLUE "\033[1;94m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0m"

typedef struct s_mini
{
	char	*rdline;
}				t_mini;

//MAIN
void	rdl_signals(int sig);
int		parser(char *rdline);

//UTILS
char	*mini_title(void);
char	**arg_split(const char *s);

#endif
