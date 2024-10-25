/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:17:13 by ngordobi          #+#    #+#             */
/*   Updated: 2024/01/10 13:43:18 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nedlen;
	char	*hayst;

	i = 0;
	nedlen = ft_strlen(needle);
	hayst = (char *)haystack;
	if (nedlen == 0 || haystack == needle)
		return (hayst);
	while ((hayst[i] != '\0') && (i < len))
	{
		j = 0;
		while ((hayst[i + j] == needle[j]) && (needle[j] != '\0')
			&& (hayst[i + j] != '\0') && (j + i < len))
			j++;
		if (j == nedlen)
			return (hayst + i);
		i++;
	}
	return (0);
}
