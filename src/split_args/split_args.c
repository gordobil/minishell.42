/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:06:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/15 12:06:17 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_matrix(char **matrix, int i)
{
	while (i-- >= 0)
		free(matrix[i]);
	free(matrix);
	return (arg_errors(-3));
}

/* int	next_arg(const char *s, int j)
{
	if (s[j - 1] == '"' || s[j - 1] == '\'')
		j = arg_jump(s, j - 1);
	else
		j = arg_jump(s, j);
	return (j);
} */

int	quote_aux(const char *s, int i, int count)
{
	if (s[i - 1] == '"')
	{
		count++;
		while (s[i] != '"')
			i++;
		count++;
	}
	else if (s[i - 1] == '\'')
	{
		count++;
		while (s[i] != '\'')
			i++;
		count++;
	}
	return (count);
}

int quote_count(const char *s, int j)
{
	int	i;
	int	simp;
	int	doub;

	if (s[j] != '"' && s[j] != '\'')
		return (j);
	i = 0;
	simp = 0;
	doub = 0;
	while (i <= j)
	{
		if (s[i] == '"')
			doub += quote_aux(s, i, doub);
		else if (s[i] == '\'')
			simp += quote_aux(s, i, simp);
		i++;
	}
	if ((s[j] == '"' && doub % 2 == 0) || (s[j] == '\'' && simp % 2 == 0))
		return (j + 1);
	else
		return (j);
}

int	arg_start(const char *s, int j)
{
	while (s[j] == ' ')
		j++;
	if (s[j] == '"' || s[j] == '\'')
		j++;
	return (j);
}

int	split_args(const char *s, t_mini *mini)
{
	int		arg_l;
	int		i;
	int		j;

	mini->arg_c = arg_count(s);
printf("args:%d\n\n", mini->arg_c);
	if (mini->arg_c <= 0)
		return (arg_errors(mini->arg_c));
	mini->args = malloc((mini->arg_c + 1) * sizeof(char *));
	if (!mini->args || !s || s[0] == '\0')
		return (arg_errors(-3));
	i = -1;
	j = 0;
	while (s[j] != '\0')
	{
		j = arg_start(s, j);
		arg_l = arg_len(s, j);
printf("s:%d len:%d\n", j, arg_l);
		if (arg_l == -1)
			return (free_matrix(mini->args, i));
		mini->args[i] = ft_substr(s, j, arg_l);
		if (!mini->args[i])
			return (free_matrix(mini->args, i));
		j += arg_l;
		j = quote_count(s, j);
printf("e:%d\n\n", j);
	}
	mini->args[i] = NULL;
}
