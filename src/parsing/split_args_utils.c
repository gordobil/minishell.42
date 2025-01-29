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

int	jump_spaces(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '	')
		i++;
	return (i);
}

int	empty_quotes(char *arg)
{
	int 	i;
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

/* int	all_same_quotes(char *s)
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
} */

int	file_found(char *s, int i)
{
	i++;
	if (s[i - 1] == '<' && s[i] == '<')
		i++;
	else if (s[i - 1] == '>' && s[i] == '>')
		i++;
	i = jump_spaces(s, i);
	return (i);
}
