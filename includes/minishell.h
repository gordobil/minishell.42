/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:27:39 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/02 14:20:06 by ngordobi         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
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
	int				exported;
	struct s_envp	*prev;
	struct s_envp	*next;
}				t_envp;

typedef struct s_files
{
	char			*file;
	int				fd;
}				t_files;

typedef struct s_pipes
{
	char			**command;
	int				args;
	int				position;
	int				var_c;
	char			**vars;
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
	int				arg_c;
	char			**arg_matrix;
	int				file_c;
	char			**files;
	int				del_c;
	char			**delimiters;
	int				comm_c;
	t_pipes			*pipes;
	t_envp			*envp;
}				t_mini;

//SPLIT_ARGS
int		split_args(char *str, t_mini *mini);
int		arg_jump(char *s, int i);

//SPLIT_ARGS_UTILS
int		check_unclosed(char *s);
int		jump_spaces(char *s, int i);
int		empty_quotes(char *s, int i);
int		jump_empty(char *s, int i);

//PARSING_UTILS
void	save_vars(t_pipes *pipe, int count);
char	*rm_quotes(char *arg);
int		count_args(char **arg_matrix, t_pipes *pipe, int i, char ret);
int		ms_strcmp(char *s1, char *s2);

//RDL
char	*rdl_management(void);
void	rdl_signals(int sig);
char	*mini_title(void);

//ENVP
void	load_envp(t_mini *mini, char **envp);
int		add_vars(t_pipes *pipe, t_mini *mini);

//ENVP_ARG_REPLACE
void	arg_vars(t_mini *mini);
char	*replace_vars(t_mini *mini, char *str);

//STRUCTS
void	pipe_info(char **arg_matrix, t_mini *mini, int i, int j);
int		is_it_a_var(char *str);

//STRUCTS_INIT
int		init_structs(t_mini *mini, int i, int position);

//DELIMITERS
void	delimiters(t_mini *mini);
char	*namefiles(int del);

//FILES
int		file_count(char **args, int i, char ret);
int		file_saving(t_mini *mini, int i, int k);
int		open_fds(t_mini *mini);

//FILES_UTILS
char	*get_namefile(char *file, char type);
void	close_fds(int fd, char *file);

//EXECUTE
void	execute(t_mini	*mini);
void	pipex(t_pipes *pipes, t_envp *envp);
void	execveloop(char **str, char **path);

//BUILT-INS
int		ms_cd(t_pipes *pipe, t_envp *envp);
void	ms_echo(t_pipes *pipe);
void	ms_env(t_envp *envp);
void	ms_export(t_pipes *pipes, t_envp *envp);
void	ms_pwd(t_envp *envp);
void	ms_unset(t_pipes *pipe, t_envp *envp);
void	unset_var(char *variable, t_envp *envp);

//FREEING
void	freeing(t_mini *mini);
void	free_matrix(char **matrix);
void	free_envp(t_envp *envp);

//ERRORS
int		error_messages(int error, char *str);

//UTILS
void	printttttttt(t_mini	*mini);
void	printtt_envp(t_envp *envp);

#endif
