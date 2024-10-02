# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 11:26:56 by ngordobi          #+#    #+#              #
#    Updated: 2024/10/02 12:30:21 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CC_FLAGS			=	-Wall -Wextra -Werror

SOURCES				=	minishell.c \
						check_args.c \

OBJECTS				= 	$(SOURCES:%.c=%.o)

INCLUDE				=	minishell.h

define MINISHELL
\033[0;33m

 ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    
▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    
▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    
▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    
▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒
░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░
░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░
░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   
       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░

$(END)
endef
export MINISHELL

.SILENT:

all:				$(NAME)

$(NAME):			$(OBJECTS) $(INCLUDE)
					$(CC) $(CC_FLAGS) $(OBJECTS) -o $(NAME)
					mkdir -p ./objects/
					mv $(OBJECTS) ./objects/
					echo "\n························ Compilation complete ·························"
					echo "$$MINISHELL"

clean:
					rm -rf ./objects/
					rm -rf *.o
					echo "\n·································"
					echo "\n · Objects correctly removed.\n"
					
fclean:				clean
					rm -rf $(NAME)
					echo " · Executable correctly removed.\n"

re:					fclean all
.PHONY:				all clean fclean re
