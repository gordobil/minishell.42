/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:34:27 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/16 19:15:34 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes(const char *s, int j, int count)
{
	if (s[j - 1] == '"')
	{
		while (s[j] != '"')
		{
			count++;
			j++;
			if (s[j] == '\0')
				return (-1);
		}
	}
	else if (s[j - 1] == '\'')
	{
		while (s[j] != '\'')
		{
			count++;
			j++;
			if (s[j] == '\0')
				return (-1);
		}
	}
	return (count);
}

int	arg_len(const char *s, int j)
{
	int	count;

	count = 0;
	if ((s[j - 1] == '"' || s[j - 1] == '\'')
		&& quote_count(s, j - 1) == j - 1)
		count = quotes(s, j, count);
	else
	{
		while (s[j] != ' ' && s[j] != '"' && s[j] != '\'' && s[j] != '\0')
		{
			count++;
			j++;
		}
	}
	return (count);
}