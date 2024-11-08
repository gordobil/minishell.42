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

int	file_management(t_mini *mini, int i, int k)
{
	t_pipes	*pipe;

	pipe = mini->pipes;
	if (mini->arg_matrix[i][1] != '<')
	{
		mini->files[k] = ft_strdup(mini->arg_matrix[i]);
		if (k < mini->file_c)
			k++;
	}
	if (mini->arg_matrix[i][0] == '<' && mini->arg_matrix[i][1] != '<')
		mini->pipes->infile = ft_strdup(mini->arg_matrix[i]);
	else if (mini->arg_matrix[i][0] == '>' && mini->arg_matrix[i][1] != '>')
		mini->pipes->outfile = ft_strdup(mini->arg_matrix[i]);
	else if (mini->arg_matrix[i][0] == '>' && mini->arg_matrix[i][1] == '>')
		mini->pipes->append = ft_strdup(mini->arg_matrix[i]);
	if (mini->pipes->outfile != NULL)
		mini->pipes->append = NULL;
	return (k);
}

int	file_count(char **args, int i, char ret)
{
	int	j;
	int	count;

	count = 0;
	while (args[i] != NULL)
	{
		j = i - 1;
		if (args[i][0] == '>' || (args[i][0] == '<' && args[i][1] != '<'))
		{
			while (j >= 0 && ms_strcmp(args[i], args[j]) != 0)
				j--;
			if (j < 0)
				count++;
			if (ret == 'r')
				return (j);
		}
		if (args[i][0] == '<' && args[i][1] == '<' && ret == 'r')
			return (-1);
		i++;
	}
	if (ret == 'r')
		return (0);
	return (count);
}

int	count_args(char **arg_matrix, t_mini *mini, int i, char ret)
{
	int	count;

	count = 0;
	while (arg_matrix[i] != NULL)
	{
		if (ms_strcmp(arg_matrix[i], "|") == 0)
			break ;
		if (arg_matrix[i][0] != '<' && arg_matrix[i][0] != '>')
			count++;
		i++;
	}
	if (ret == 'i')
		return (i);
	return (count);
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
