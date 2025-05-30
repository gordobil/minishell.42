# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 12:12:49 by ngordobi          #+#    #+#              #
#    Updated: 2024/12/02 14:19:24 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CC_FLAGS			=	-Wall -Wextra -Werror
RL_FLAGS			=	-I/usr/include/readline -lreadline

LIBFT				=	libft.a

SRC_PATH			=	./src/
PRS_PATH			=	./src/parsing/
EXC_PATH			=	./src/execution/
BI_PATH				=	./src/execution/built-ins/
LIBFT_PATH			=	./libft/

SOURCES				=	$(SRC_PATH)errors.c \
						$(SRC_PATH)freeing.c \
						$(SRC_PATH)minishell.c \
						$(SRC_PATH)readline.c \
						$(SRC_PATH).print_mini.c \
						$(PRS_PATH)delimiters.c \
						$(PRS_PATH)envp.c \
						$(PRS_PATH)envp_arg_replace.c \
						$(PRS_PATH)files.c \
						$(PRS_PATH)files_utils.c \
						$(PRS_PATH)parsing_utils.c \
						$(PRS_PATH)rm_quotes.c \
						$(PRS_PATH)split_args.c \
						$(PRS_PATH)split_args_utils.c \
						$(PRS_PATH)structs.c \
						$(PRS_PATH)structs_utils.c \
						$(PRS_PATH)structs_init.c \
						$(EXC_PATH)execute.c \
						$(EXC_PATH)pipex_mini.c \
						$(EXC_PATH)pipex_utils.c \
						$(BI_PATH)ms_cd.c \
						$(BI_PATH)ms_echo.c \
						$(BI_PATH)ms_env.c \
						$(BI_PATH)ms_exit.c \
						$(BI_PATH)ms_export.c \
						$(BI_PATH)ms_pwd.c \
						$(BI_PATH)ms_unset.c \
						
OBJECTS				= 	$(SOURCES:%.c=%.o)

INCLUDES			=	./includes/minishell.h \
						./includes/libft.h \

#COLORS
BLUE				=	\033[1;34m
BOLD_BLUE			=	\033[0;34m
WHITE				=	\033[0m

define MINISHELL
$(BOLD_BLUE)

   ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    
  ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    
  ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    
  ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    
  ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
  ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
  ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
  ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   
         ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░
$(WHITE)
$(END)
endef
export MINISHELL

.SILENT:

all:				$(NAME) $(LIBFT)

$(NAME):			$(OBJECTS) $(LIBFT) $(INCLUDES)
					$(CC) $(CC_FLAGS) $(OBJECTS) $(LIBFT) $(RL_FLAGS) -o $(NAME)
					mkdir -p $(SRC_PATH).objects/
					mv $(OBJECTS) $(SRC_PATH).objects/
					echo "\n························· Compilation complete ··························"
					echo "$$MINISHELL"

$(LIBFT):
					@make --no-print-directory -C $(LIBFT_PATH)

clean:
					rm -rf $(SRC_PATH).objects/
					rm -rf $(SRC_PATH)*.o
					rm -rf $(SRC_PATH).print_mini.o
					rm -rf $(PRS_PATH)*.o
					rm -rf $(EXC_PATH)*.o
					rm -rf $(BI_PATH)*.o
					@make clean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell objects removed.$(WHITE)\n"
					
fclean:				clean
					rm -rf $(NAME)
					rm -rf $(LIBFT)
					rm -rf .temp_file_*
					@make fclean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell executable removed.$(WHITE)\n"

re:					fclean all
.PHONY:				all clean fclean re
