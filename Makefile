# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 12:12:49 by ngordobi          #+#    #+#              #
#    Updated: 2024/11/22 13:04:23 by mafarto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CC_FLAGS			=	-g -Wall -Wextra -Werror -O0 -g
RL_FLAGS			=	-I/usr/include/readline -lreadline

LIBFT				=	libft.a

SRC_PATH			=	./src/
LIBFT_PATH			=	./libft/

SOURCES				=	$(SRC_PATH)minishell.c \
						$(SRC_PATH)rdl.c \
						$(SRC_PATH)delimiters.c \
						$(SRC_PATH)envp.c \
						$(SRC_PATH)envp_replace.c \
						$(SRC_PATH)split_args_utils.c \
						$(SRC_PATH)split_args.c \
						$(SRC_PATH)structs.c \
						$(SRC_PATH)structs_init.c \
						$(SRC_PATH)freeing.c \
						$(SRC_PATH)execute.c \
						$(SRC_PATH)building_utils.c \
						$(SRC_PATH)printttttttt.c \

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
					mkdir -p $(SRC_PATH)objects/
					mv $(OBJECTS) $(SRC_PATH)objects/
					echo "\n························· Compilation complete ··························"
					echo "$$MINISHELL"

$(LIBFT):
					@make --no-print-directory -C $(LIBFT_PATH)

clean:
					rm -rf $(SRC_PATH)objects/
					rm -rf $(SRC_PATH)*.o
					@make clean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell objects removed.$(WHITE)\n"
					
fclean:				clean
					rm -rf $(NAME)
					rm -rf $(LIBFT)
					rm -rf .delimiter_file_*
					@make fclean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell executable removed.$(WHITE)\n"

re:					fclean all
.PHONY:				all clean fclean re
