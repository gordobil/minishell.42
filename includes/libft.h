/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:59:40 by ngordobi          #+#    #+#             */
/*   Updated: 2024/01/28 18:14:19 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

//CHARACTERS
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

//FDS
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

//INTEGERS
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

//MEMORY
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

//STRINGS
int			ft_strlen(const char *s);
size_t		ft_strlcpy(char	*dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
void		ft_bzero(void *s, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		**ft_split(const char *s, char czzzz);
char		*ft_strcat(char *src, char *str);

//FT_PRINTF
int			ft_printf(const char *arg, ...);
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putmatrix(char **matrix);
int			ft_putnbr(int n);
int			ft_putunbr(unsigned int n);
int			ft_puthex(unsigned long n, char arg_format);
int			ft_putptr(unsigned long p);

#endif
