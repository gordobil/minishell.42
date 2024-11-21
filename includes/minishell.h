/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/21 15:30:39 by ngordobi         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>
# include "./libft.h"

//COLORS
# define BLUE "\033[1;34m"
# define YELLOW "\033[0;32m"
# define WHITE "\033[0m"

struct	s_mini;

typedef struct s_envp
{
	char			*variable;
	char			*content;
	int				position;
	struct s_envp	*prev;
	struct s_envp	*next;
}				t_envp;

typedef struct s_files
{
	char	*file;
	int		fd;
}				t_files;

typedef struct s_pipes
{
	char			**command;
	int				position;
	t_files			*infile;
	t_files			*outfile;
	t_files			*append;
	t_files			*delimiter;
	struct s_mini	*mini;
	struct s_pipes	*next;
	struct s_pipes	*prev;
}				t_pipes;

typedef struct s_mini
{
	int		arg_c;
	char	**arg_matrix;
	int		file_c;
	char	**files;
	int		del_c;
	char	**delimiters;
	int		comm_c;
	t_pipes	*pipes;
	t_envp	*envp;
}				t_mini;

//MAIN
int		split_args(char *str, t_mini *mini);
void	pipe_info(char **arg_matrix, t_mini *mini, int k);
int		init_structs(t_mini *mini, int i, int position);
void	freeing(t_mini *mini);
void	free_matrix(char **matrix);

//ENVP
void	load_envp(t_mini *mini, char **envp);
char	*replace_vars(t_mini *mini, char *str);

//DELIMITERS
void	delimiters(t_mini *mini);
char	*namefiles(int del);

//RDL_UTILS
char	*rdl_management(void);
void	rdl_signals(int sig);
char	*mini_title(void);
void	error_messages(int error);

//SPLIT_UTILS
int		file_count(char **args, int i, char ret);
int		file_management(t_mini *mini, int i, int k);
int		count_args(char **arg_matrix, t_mini *mini, int i, char ret);
int		ms_strcmp(char *s1, char *s2);

//UTILS
void	printttttttt(t_mini	*mini);

#endif
