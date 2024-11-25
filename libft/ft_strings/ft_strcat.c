/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:37:16 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/25 11:45:45 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strcat(char *src, char *str)
{
	int		i;
	int		j;
	int		size;
	int		src_size;
	char	*dest;

	src_size = ft_strlen(src);
	size = src_size + ft_strlen(str);
	dest = ft_calloc(size + 1, sizeof(int));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < size && i < src_size)
		dest[i] = src[i];
	j = -1;
	while (++i < size && ++j < ft_strlen(str))
		dest[i] = str[j];
	dest[i] = '\0';
	return (dest);
}
