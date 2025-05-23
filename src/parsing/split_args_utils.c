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

int	found_unexpected_token(char c)
{
	if (c == '\'')
		return (-1);
	else if (c == '"')
		return (-2);
	else if (c == '|')
		return (-7);
	else if (c == '\0')
		return (-9);
	else if (c == ';')
		return (-10);
	else if (c == '\\')
		return (-11);
	else if (c == '<')
		return (-13);
	else if (c == '>')
		return (-14);
	return (0);
}

int	jump_pipe(char *s, int i)
{
	i++;
	i = jump_spaces(s, i);
	if (s[i] == '|' || s[i] == '\0' || s[i] == ';' || s[i] == '\\')
		return (found_unexpected_token(s[i]));
	return (i);
}

int	jump_spaces(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '	')
		i++;
	return (i);
}

int	empty_quotes(char *arg)
{
	int		i;
	char	q;

	i = 0;
	while (arg[i] != '\0' && (arg[i] == '\'' || arg[i] == '"'))
	{
		q = arg[i];
		if (arg[i + 1] == q)
			i += 2;
		else
			break ;
	}
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	file_found(char *s, int i)
{
	i++;
	if ((s[i - 1] == '<' && s[i] == '<') || (s[i - 1] == '>' && s[i] == '>'))
		i++;
	i = jump_spaces(s, i);
	if (s[i] == ';' || s[i] == '\\' || s[i] == '<' || s[i] == '>')
		return (found_unexpected_token(s[i]));
	return (i);
}
