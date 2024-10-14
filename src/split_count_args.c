/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_count_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:16 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/14 15:25:50 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_jump(const char *s, int i)
{
	while (s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '\0')
		i++;
	return (i);
}

int	arg_jump(const char *s, int i)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i] != '\0')
		{
			i++;
			if (s[i] == '\0')
				return (-1);
		}
		i++;
	}
	else if (s[i] == '\'')		
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
		{
					i++;
			if (s[i] == '\0')
				return (-1);
		}
		i++;
	}
	else
		i = word_jump(s, i);
	return (i);
}

int	arg_count(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] != '\0')
		count = 1;
	while (s[i] != '\0')
	{
		i = arg_jump(s, i);
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
			count++;
		else
			break ;
	}
	return (count);
}
