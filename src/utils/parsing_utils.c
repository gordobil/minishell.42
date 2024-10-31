/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:53:52 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/31 14:53:52 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_count(char **args, int i, char ret)
{
	int	j;
	int	count;

	count = 0;
	while (args[i] != NULL)
	{
		j = i - 1;
		if (args[i][0] == '<' || args[i][0] == '>')
		{
			while (j >= 0 && ms_strcmp(args[i], args[j]) != 0)
				j--;
			if (j < 0)
				count++;
			if (ret != 'c')
				return (j);
		}
		i++;
	}
	if (ret != 'c')
		return (0);
	return (count);
}

int	count_args(char **arg_matrix, t_mini *mini, int i, char ret)
{
	int	count;

	count = 0;
	while (arg_matrix[i] != NULL)
	{
		if (ft_strcmp(arg_matrix[i], "|") == 0)
			break ;
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
			count++;
		else if (arg_matrix[i][0] == '<')
			mini->infile = ft_strdup(arg_matrix[i]);
		else if (arg_matrix[i][0] == '>')
			mini->outfile = ft_strdup(arg_matrix[i]);
		i++;
	}
	if (ret == 'i')
		return (i);
	return (count);
}

int	ms_strcmp(char *s1, char *s2)
{
	int	i;

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
