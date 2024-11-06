/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/06 13:47:27 by ngordobi         ###   ########.fr       */
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

typedef struct s_pipes
{
	char			**command;
	int				position;
	char			*infile;
	char			*outfile;
	struct s_mini	*mini;
	struct s_pipes	*next;
	struct s_pipes	*prev;
}				t_pipes;

typedef struct s_mini
{
	char	**arg_matrix;
	int		arg_c;
	int		file_c;
	char	**files;
	t_pipes	*pipes;
}				t_mini;

//MAIN
char	**split_args(char *str, t_mini *mini);
void	pipe_info(char **arg_matrix, t_mini *mini, int k);

//RDL_UTILS
void	rdl_signals(int sig);
char	*mini_title(void);
void	error_messages(int error);

//PARSING_UTILS
int		file_count(char **args, int i, char ret);
int		file_management(t_mini *mini, int i, int k);
int		count_args(char **arg_matrix, t_mini *mini, int i, char ret);
int		ms_strcmp(char *s1, char *s2);

#endif
