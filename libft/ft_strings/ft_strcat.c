/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:37:16 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/27 19:42:10 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strcat(char *src, char *str)
{
	int		count;
	int		size;
	char	*dest;

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
