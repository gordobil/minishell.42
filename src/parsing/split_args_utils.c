/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:01:14 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/06 18:01:14 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_unclosed(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i = arg_jump(s, i);
		if (i < 0)
			return (i);
	}
	return (0);
}

int	jump_spaces(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '	')
		i++;
	return (i);
}

int	empty_quotes(char *s, int i)
{
	int		start;
	char	q;

	if (s[i] == '"' || s[i] == '\'')
	{
		start = i;
		q = s[i];
		while (s[i] == q && s[i] != '\0')
			i++;
		if (s[i] != '\0' && ((i - start) % 2 != 0))
			i--;
		else if (s[i] != '\0' && ((i - start) % 2 == 0))
			if (i != jump_spaces(s, i))
				return (empty_quotes(s, jump_spaces(s, i)));
	}
	return (i);
}

int	jump_empty(char *s, int i)
{
	i = jump_spaces(s, i);
	i = empty_quotes(s, i);
	return (i);
}

int	all_same_quotes(char *s)
{
	int		i;
	char	q;
	i = jump_spaces(s, 0);
	if (s[i] == '\'' || s[i] == '"')
		q = s[i];
	else
		return (0);
	while (s[i] == q && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (1);
	return (-1);
}