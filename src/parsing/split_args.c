/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:01:05 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/04 13:18:51 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_jump(char *s, int i, char q)
{
	if (s[i] == '|')
		i = jump_pipe(s, i);
	else
	{
		if (s[i] == '<' || s[i] == '>')
			i = file_found(s, i);
		if (i < 0)
			return (i);
		while (s[i] != '\0' && ((q == '"' || q == '\'') || (s[i] != ' '
					&& s[i] != '|' && s[i] != '<' && s[i] != '>'
					&& s[i] != '\t' && s[i] != ';' && s[i] != '\\')))
		{
			if (q == '0' && (s[i] == '"' || s[i] == '\''))
				q = s[i];
			else if (s[i] == q && (s[i] == '"' || s[i] == '\''))
				q = '0';
			i++;
		}
		if (q == '\'')
			return (-1);
		else if (q == '"')
			return (-2);
	}
	return (i);
}

int	arg_size(char *s, int i, char mark)
{
	int		start;

	i = jump_separators(s, i);
	if (mark == 's')
		return (i);
	start = i;
	i = arg_jump(s, i, '0');
	if (mark == 'e' || i < 0)
		return (i);
	else
		return (i - start);
}

int	arg_count(char *s)
{
	int	i;
	int	count;
	int	start;

	if (s[0] == '\n' || s[0] == '\0')
		return (0);
	count = 0;
	i = jump_separators(s, 0);
	while (s[i] != '\0')
	{
		start = i;
		count++;
		i = arg_jump(s, i, '0');
		if (i < 0)
			return (i);
		i = jump_separators(s, i);
	}
	return (count);
}

char	*arg_dup(char *s, int j)
{
	char	*arg;

	arg = ft_substr(s, arg_size(s, j, 's'), arg_size(s, j, 'r'));
	if (empty_quotes(arg) == 1)
	{
		free (arg);
		arg = ft_strdup("''");
	}
	return (arg);
}

int	split_args(char *s, t_mini *mini)
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
		if (empty_quotes(s) == 1)
			mini->arg_matrix[i] = ft_strdup("''");
		else
			mini->arg_matrix[i] = arg_dup(s, j);
		if (!mini->arg_matrix[i])
			return (free_matrix(mini->arg_matrix), -1);
		j = arg_size(s, j, 'e');
	}
	mini->arg_matrix[i] = NULL;
	return (error_messages(-7, mini->arg_matrix[0]));
}
