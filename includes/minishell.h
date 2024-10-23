/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/23 20:47:36 by ngordobi         ###   ########.fr       */
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
# define BLUE "\033[1;34m"
# define YELLOW "\033[0;32m"
# define WHITE "\033[0m"

struct	s_mini;

typedef struct s_args
{
	char			*arg;
	int				position;
	char			type;
	struct s_mini	*mini;
	void			*next;
	void			*prev;
}				t_args;

typedef struct s_mini
{
	char	*rdline;
	char	**arg_matrix;
	int		arg_c;
	t_args	*args;
}				t_mini;

//MAIN
char	**split_args(char *str, t_mini *mini);
//void	free_mini(t_mini *mini);

//RDL_UTILS
void	rdl_signals(int sig);
char	*mini_title(void);
void	error_message(int error);

/* ARGUMENT TYPES:
	2 = double quotation____ " "
	q = quotation marks_____ ' '
	i = infile______________ <
	o = outfile_____________ >
	d = delimiter___________ <<
	a = append to output____ >>
	v = variable_____________ $
	p = pipe_________________ |
*/

#endif
