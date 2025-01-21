/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:01:05 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/21 11:35:41 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	word_jump_copy(const char *s, int i)
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
		while (s[i] != ' ' && s[i] != '|' && s[i] != '\0' && s[i] != '<'
			&& s[i] != '>' && s[i] != '	')
			i++;
	}
	return (i);
}

int	arg_jump_copy(char *s, int i)
{
	int	start;

	i = jump_spaces(s, i);
	start = i;
	if (s[i] == '"' || s[i] == '\'')
	{
		i++;
		while (s[i] != s[start])
		{
			i++;
			if (s[i] == '\0')
			{
				if (s[start] == '"')
					return (-2);
				return (-1);
			}
		}
		if (i == start + 1)
			return (arg_jump(s, i + 1));
		i++;
	}
	else
		i = word_jump(s, i);
	return (i);
}

int	arg_count_copy(char *s)
{
	int	i;
	int	count;
	int	start;

	if (s[0] == '\n' || s[0] == '\0' || check_unclosed(s) < 0)
		return (check_unclosed(s));
	i = jump_empty(s, 0);
	if (s[i] == '\0' || s[i] == '\n')
		return (1);
	count = 1;
	while (s[i] != '\0')
	{
		i = jump_empty(s, i);
		i = arg_jump(s, i);
		if (i <= 0)
			return (i);
		i = jump_empty(s, i);
		if (s[i] != '\0' && s[i] != '\n')
			count++;
		else
			break ;
	}
	return (count);
}

int	arg_size_copy(char *s, int i, char mark)
{
	int		start;
	int		q_start;
	char	q;

	i = jump_spaces(s, i);
	q_start = i;
	if (s[i] == '"' || s[i] == '\'')
		i = empty_quotes(s, i);
	if (mark == 's')
		return (i);
	start = i;
	i = arg_jump(s, i);
	if (mark == 'e' || i < 0)
		return (i);
	else
		return (i - start);
}

int	split_args_copy(char *s, t_mini *mini)
{
	int		i;
	int		j;

	if (!mini->envp)
		return (error_messages(-8, NULL));
	mini->arg_c = arg_count(s);
	if (mini->arg_c <= 0)
		return (error_messages(mini->arg_c, NULL), -1);
	mini->arg_matrix = malloc((mini->arg_c + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while (++i < mini->arg_c)
	{
		if (all_same_quotes(s) == 1)
			mini->arg_matrix[i] = ft_strdup("''");
		else
			mini->arg_matrix[i] = ft_substr(s, arg_size(s, j, 's'),
				arg_size(s, j, 'r'));
		if (!mini->arg_matrix[i])
			return (free_matrix(mini->arg_matrix), -1);
		j = arg_size(s, j, 'e');
	}
	mini->arg_matrix[i] = NULL;
	return (error_messages(-7, mini->arg_matrix[0]));
}
