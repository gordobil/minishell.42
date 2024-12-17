/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:14:25 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/25 12:14:25 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_vars(t_pipes *pipe, int count)
{
	int		i;
	int		j;

	if (count <= 0)
		return ;
	pipe->vars = malloc((count + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (j < count && pipe->command[i] != NULL)
	{
		if (is_it_a_var(pipe->command[i]) > 0)
		{
			pipe->vars[j] = ft_strdup(pipe->command[i]);
			j++;
		}
		i++;
	}
	pipe->vars[j] = NULL;
}

char	*rm_quotes(char *arg)
{
	int		len;
	char	*new_arg;

	if (arg[0] == '\'' || arg[0] == '"')
	{
		len = ft_strlen(arg);
		new_arg = ft_substr(arg, 1, len - 2);
		return (new_arg);
	}
	return (ft_strdup(arg));
}


int	count_args(char **arg_matrix, t_pipes *pipe, int i, char ret)
{
	pipe->args = 0;
	while (arg_matrix[i] != NULL)
	{
		if (ms_strcmp(arg_matrix[i], "|") == 0)
			break ;
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
			pipe->args++;
		if (is_it_a_var(arg_matrix[i]) > 0 && ret == 'c')
			pipe->var_c++;
		i++;
	}
	if (ret == 'i')
		return (i);
	return (pipe->args);
}

int	ms_strcmp_pipes(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[0] == '|' && s2[0] == '|')
	{
		if (ft_strcmp(s1, s2) == 0)
			return (0);
		while (s1[i] == '|' || s1[i] == ' ' || s1[i] == '	')
			i++;
		while (s2[j] == '|' || s2[i] == ' ' || s2[i] == '	')
			j++;
		if (s1[i] == '\0' && s2[j] == '\0')
			return (0);
	}
	return (-1);
}

int	ms_strcmp(char *s1, char *s2)
{
	int	i;

	if (ms_strcmp_pipes(s1, s2) == 0)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = 0;
	if ((s1[i] == '<' || s1[i] == '>' ) && (s2[i] == '<' || s2[i] == '>' ))
		i++;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] != s2[i])
			break ;
	}
	if (i == ft_strlen(s1) && i == ft_strlen(s2)
		&& s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (-1);
}
