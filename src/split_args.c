/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:01:05 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/12 13:07:28 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_jump(const char *s, int i)
{
	if (s[i] == '|')
		while (s[i] == '|' || s[i] == ' ' || s[i] == '	')
			i++;
	else
	{
		if (s[i] == '<' || s[i] == '>')
		{
			i++;
			if (s[i - 1] == '<' && s[i] == '<')
				i++;
			else if (s[i - 1] == '>' && s[i] == '>')
				i++;
			while (s[i] == ' ' || s[i] == '	')
				i++;
		}
		while (s[i] != ' ' && s[i] != '"' && s[i] != '|' && s[i] != '\''
			&& s[i] != '\0' && s[i] != '<' && s[i] != '>' && s[i] != '	')
			i++;
	}
	return (i);
}

int	arg_jump(const char *s, int i)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"')
		{
			i++;
			if (s[i] == '\0')
				return (-2);
		}
		i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'')
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

	if (s[0] == '\n' && s[1] == '\0')
		return (0);
	i = 0;
	count = 0;
	while (s[i] == ' ' || s[i] == '	')
		i++;
	if (s[i] != '\0')
		count = 1;
	while (s[i] != '\0')
	{
		i = arg_jump(s, i);
		if (i <= 0)
			return (i);
		while (s[i] == ' ' || s[i] == '	')
			i++;
		if (s[i] != '\0')
			count++;
		else
			break ;
	}
	return (count);
}

int	arg_size(char *s, int i, char mark)
{
	int	start;

	while (s[i] == ' ' || s[i] == '	')
		i++;
	if (mark == 's')
		return (i);
	start = i;
	i = arg_jump(s, i);
	if (mark == 'e' || i < 0)
		return (i);
	else
		return (i - start);
}

char	**split_args(char *s, t_mini *mini)
{
	char	**args;
	int		i;
	int		j;

	mini->arg_c = arg_count(s);
	if (mini->arg_c <= 0)
		return (error_messages(mini->arg_c), NULL);
	args = malloc((mini->arg_c + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while (++i < mini->arg_c)
	{
		args[i] = malloc((arg_size(s, j, 'r') + 1) * sizeof(char));
		if (!(args[i]))
		{
			i++;
			while (--i >= 0)
				free(args[i]);
			return (free(args), NULL);
		}
		args[i] = ft_substr(s, arg_size(s, j, 's'), arg_size(s, j, 'r'));
		j = arg_size(s, j, 'e');
	}
	args[i] = NULL;
	return (args);
}
