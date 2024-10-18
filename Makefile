# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 12:12:49 by ngordobi          #+#    #+#              #
#    Updated: 2024/10/18 20:57:50 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CC_FLAGS			=	-g -Wall -Wextra -Werror
RL_FLAGS			=	-I/usr/include/readline -lreadline

LIBFT				=	libft.a

SRC_PATH			=	./src/
SPLIT_PATH			=	./src/split_args/
LIBFT_PATH			=	./libft/

SOURCES				=	$(SRC_PATH)minishell.c \
						$(SRC_PATH)parser.c \
						$(SRC_PATH)rdl_utils.c \
						$(SPLIT_PATH)split_args.c \
						$(SPLIT_PATH)count_args.c \
						$(SPLIT_PATH)measure_args.c \

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
					@make fclean --no-print-directory -C $(LIBFT_PATH)
					echo "$(WHITE) · $(BLUE)Minishell executable removed.$(WHITE)\n"

re:					fclean all
.PHONY:				all clean fclean re
