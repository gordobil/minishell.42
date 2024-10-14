/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:50:19 by ngordobi          #+#    #+#             */
/*   Updated: 2024/02/02 17:38:23 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_matrix(char **matrix, int i)
{
		while (i-- >= 0)
			free(matrix[i]);
		return (matrix);
}

int	arg_start(const char *s, int j)
{
	while (s[j] == ' ')
		j++;
	if (s[j] == '"' || s[j] == '\'')
		j++;
	return (j);
}

char	**split_args(const char *s)
{
	int		arg_c;
	int		arg_l;
	int		i;
	int		j;
	char	**matrix;

	arg_c = arg_count(s);
	if (arg_c < 0 || s[0] == '\0')
		return (NULL);
	matrix = malloc((arg_c + 1) * sizeof(char *));
	if (!matrix || !s)
		return (NULL);
	i = 0;
	arg_l = 0;
	while (i < arg_c)
	{
		j = arg_start(s, j);
		if (s[j] == '\0')
			break ;
		arg_l = arg_len(s, j);
		if (arg_l == -1)
			return (free_matrix(matrix, i));
		matrix[i] = ft_substr(s, j, arg_l);
		if (!matrix[i])
			return (free_matrix(matrix, i));
		j = arg_jump();
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
