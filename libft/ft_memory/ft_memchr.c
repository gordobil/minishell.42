/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:39:42 by ngordobi          #+#    #+#             */
/*   Updated: 2024/01/09 11:42:51 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char		ch;
	const char	*str;

	str = s;
	ch = (char)c;
	while (n > 0)
	{
		if (*str == ch)
			return ((void *)str);
		n--;
		str++;
	}
	return (0);
}
