/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:17:34 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/07 13:17:34 by ngordobi         ###   ########.fr       */
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
	pid_t			pids;
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
	char			**env_str;
	int				comm_c;
	t_pipes			*pipes;
	t_envp			*envp;
	int				last_ret;
}				t_mini;

/******************************** PARSING ********************************/
//SPLIT_ARGS
int		split_args(char *str, t_mini *mini);
int		arg_jump(char *s, int i, char q);

//SPLIT_ARGS_UTILS
int		jump_pipe(char *s, int i);
int		found_unexpected_token(char c);
int		jump_spaces(char *s, int i);
int		empty_quotes(char *arg);
int		file_found(char *s, int i);

//PARSING_UTILS
void	save_vars(t_pipes *pipe, int count);
int		count_args(char **arg_matrix, t_pipes *pipe, int i, char ret);
int		ms_strcmp(char *s1, char *s2);
char	*rm_arrows(char *str);

//RM_QUOTES
char	*rm_quotes(char *arg, int i, int j);
int		jump_single_quotes(char	*str, int i);

//RDL
char	*rdl_management(void);
void	rdl_new_line(int signal);
char	*mini_title(void);
void	*children_signals(t_mini *mini);

//ENVP
void	load_envp(t_mini *mini, char **envp);
void	nodes_envp(t_envp *envp_p, t_envp *prev, int i, char **envp);
int		add_vars(t_pipes *pipe, t_mini *mini);
t_envp	*get_edge_node(t_envp *envp, char edge);

//ENVP_ARG_REPLACE
void	arg_vars(t_mini *mini);
char	*replace_vars(t_mini *mini, char *str, int i);

//STRUCTS
int		pipe_info(char **arg_matrix, t_mini *mini, int i, int j);
int		is_it_a_var(char *str);

//STRUCTS_UTILS
void	mini_is_null(t_mini **mini, int *i);

//STRUCTS_INIT
int		init_structs(t_mini *mini, int i, int position);
int		pipes_end(char **arg_matrix, int i, t_mini *mini);

//DELIMITERS
int		delimiters(t_mini *mini, t_pipes *command);
char	*namefiles(int del);

//FILES
int		file_count(char **args, int i, char ret);
int		file_saving(t_mini *mini, int i, int k);
int		open_fds(t_mini *mini);

//FILES_UTILS
char	*get_namefile(char *file, char type);
void	close_fds(t_files *file);
int		count_files(t_mini *mini, int i, int k);

/******************************* EXECUTION *******************************/
//EXECUTE
void	pipex(t_pipes *pipes, t_envp *envp);
int		building_execute(t_mini *mini, t_pipes *pipe, t_envp *envp, int i);
void	execveloop(char **str, char **path, char **term);

//PIPEX_MINI
void	create_pipes_for_pipeline(int command_count, int **pipes);
void	setup_redirections(int i, int **pipes, t_pipes *current,
			int command_count);
void	close_pipes_and_wait(int command_count, int **pipes, t_mini *mini);
void	execute_pipeline(t_pipes *pipeline, t_envp *env_list);
int		is_text(t_pipes *pipe, t_envp *envp, int i);

//PIPEX_UTILS
char	**get_pathsenv(t_envp *envp);
void	execute_single_command(t_pipes *current, t_envp *env_list);
int		var_jump(char **command);
int		check_vars(char **command, int i, t_mini *mini);
void	building_redir(t_pipes *pipes, t_envp *envp);

//BUILT-INS
int		ms_cd(t_pipes *pipe, t_envp *envp, int i);
void	ms_echo(t_pipes *pipe, int i);
void	ms_pwd(t_envp *envp, t_pipes *pipe);
int		ms_env(t_envp *envp, t_pipes *pipe, int i, int print_export);
int		ms_exit(char *rdline);
void	ms_export(t_pipes *pipes, t_envp *envp, int i);
void	ms_unset(t_pipes *pipe, t_envp *envp, int i);
t_envp	*unset_var(char *variable, t_envp *envp);
char	*get_var(char *arg);

/********************************* MAIN **********************************/
//FREEING
void	freeing(t_mini *mini);
void	free_matrix(char **matrix);
void	free_envp(t_envp *envp);

//ERRORS
int		error_messages(int error, char *str);

//UTILS
void	ms_print_mini(t_mini *mini, int enviroment);
void	ms_print_pipes(t_pipes *command);
void	ms_print_envp(t_envp *envp);

#endif
