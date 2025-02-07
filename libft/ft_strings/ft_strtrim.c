/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:46:46 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/23 20:03:35 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	trim_start(const char *s1, const char *set)
{
	int	start;
	int	stop;
	int	i;
	int	j;

	start = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		stop = start;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				start++;
				break ;
			}
			j++;
		}
		if (start == stop)
			break ;
		i++;
	}
	return (start);
}

int	trim_end(const char *s1, const char *set, int end)
{
	int	i;
	int	stop;

	end--;
	while (end != 0)
	{
		i = 0;
		stop = end;
		while (set[i] != '\0')
		{
			if (s1[end] == set[i])
			{
				end--;
				break ;
			}
			i++;
		}
		if (end == stop)
			break ;
	}
	return (end);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*s2;

	if (s1[0] == '\0' || !s1 || !set)
		return (ft_strdup(""));
	start = trim_start(s1, set);
	end = trim_end(s1, set, ft_strlen(s1));
	s2 = ft_substr(s1, start, end - start + 1);
	return (s2);
}
