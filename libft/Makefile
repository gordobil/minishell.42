# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 16:12:44 by ngordobi          #+#    #+#              #
#    Updated: 2024/01/28 18:14:41 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a

CC					=	gcc
CCFLAGS				=	-Wall -Wextra -Werror

CHAR_PATH			=	./ft_characters/
FD_PATH				=	./ft_fds/
INT_PATH			=	./ft_integers/
MEM_PATH			=	./ft_memory/
STR_PATH			=	./ft_strings/
PF_PATH				=	./ft_printf/

SOURCES				=	$(CHAR_PATH)ft_isalpha.c \
						$(CHAR_PATH)ft_isdigit.c \
						$(CHAR_PATH)ft_isalnum.c \
						$(CHAR_PATH)ft_isascii.c \
						$(CHAR_PATH)ft_isprint.c \
						$(CHAR_PATH)ft_toupper.c \
						$(CHAR_PATH)ft_tolower.c \
						$(FD_PATH)ft_putchar_fd.c \
						$(FD_PATH)ft_putstr_fd.c \
						$(FD_PATH)ft_putendl_fd.c \
						$(FD_PATH)ft_putnbr_fd.c \
						$(INT_PATH)ft_itoa.c \
						$(INT_PATH)ft_atoi.c \
						$(MEM_PATH)ft_memset.c \
						$(MEM_PATH)ft_memcpy.c \
						$(MEM_PATH)ft_memmove.c \
						$(MEM_PATH)ft_memchr.c \
						$(MEM_PATH)ft_memcmp.c \
						$(MEM_PATH)ft_calloc.c \
						$(STR_PATH)ft_strlen.c \
						$(STR_PATH)ft_strlcpy.c \
						$(STR_PATH)ft_strcat.c \
						$(STR_PATH)ft_strlcat.c \
						$(STR_PATH)ft_strcmp.c \
						$(STR_PATH)ft_strncmp.c \
						$(STR_PATH)ft_strnstr.c \
						$(STR_PATH)ft_strchr.c \
						$(STR_PATH)ft_strrchr.c \
						$(STR_PATH)ft_bzero.c \
						$(STR_PATH)ft_strdup.c \
						$(STR_PATH)ft_substr.c \
						$(STR_PATH)ft_strjoin.c \
						$(STR_PATH)ft_strtrim.c \
						$(STR_PATH)ft_strmapi.c \
						$(STR_PATH)ft_striteri.c \
						$(STR_PATH)ft_split.c \

PF_SOURCES			=	$(PF_PATH)ft_printf.c \
						$(PF_PATH)ft_putchar.c \
						$(PF_PATH)ft_putstr.c \
						$(PF_PATH)ft_putmatrix.c \
						$(PF_PATH)ft_putnbr.c \
						$(PF_PATH)ft_putunbr.c \
						$(PF_PATH)ft_puthex.c \
						$(PF_PATH)ft_putptr.c \

OBJECTS				=	$(SOURCES:%.c=%.o)
PF_OBJECTS			=	$(PF_SOURCES:%.c=%.o)

INCLUDE				=	../includes/libft.h

#COLORS
WHITE				=	\033[0m

.SILENT:

all:				$(NAME) tidy

$(NAME):			$(OBJECTS) $(PF_OBJECTS)
					ar rcs $(NAME) $(OBJECTS) $(PF_OBJECTS)

tidy:				
					mkdir -p ./objects/
					mkdir -p $(PF_PATH)objects/
					mv $(OBJECTS) ./objects/
					mv $(PF_OBJECTS) $(PF_PATH)objects/
					mv $(NAME) ../
					echo "$(WHITE)\n · Libft compilation complete.\n"
clean:
					rm -rf ./objects/
					rm -rf $(PF_PATH)objects/
					rm -rf *.o
					rm -rf $(PF_PATH)*.o
					echo "\n$(WHITE) · Libft objects removed."
					
fclean:				clean
					rm -rf $(NAME)
					rm -rf ../$(NAME)
					echo "$(WHITE) · Libft executable removed."

re:					fclean all
.PHONY:				all tidy clean fclean re
