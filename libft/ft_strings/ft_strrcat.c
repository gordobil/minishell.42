/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:45 by mafarto-          #+#    #+#             */
/*   Updated: 2024/11/19 14:43:46 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char    *ft_strrcat(char *src, char *str)
{
    int count;
    int size;
    char *dest;

    count = 0;
    size = ft_strlen(src) + ft_strlen(str);
    dest = malloc(sizeof(int) * (size + 1));
    while (count < size)
    {
        if (count < ft_strlen(src))
            dest[count] = src[count];
        else
            dest[count] = str[count - ft_strlen(src)];
        count++;
    }
    dest[count] = '\0';
    return (dest);
}