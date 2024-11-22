/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:31:20 by ngordobi          #+#    #+#             */
/*   Updated: 2024/01/09 14:12:32 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, ft_strlen(s1));
	s2[ft_strlen(s1)] = '\0';
	return (s2);
}
