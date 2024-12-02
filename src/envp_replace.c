/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:18:44 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/02 14:16:01 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_404(char *str, int i, char *comp)
{
	char	*start;
	char	*end;

	if ((str[i + 1] < '0' || str[i + 1] > '9') && ft_strcmp(comp, str) != 0)
		return (free(comp), i);
	start = ft_substr(str, 0, i);
	i++;
	if (str[i] < '0' || str[i] > '9')
	{
		while (str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != ' '
			&& str[i] != '	' && str[i] != '\n' && str[i] != '$')
			i++;
	}
	else
		i++;
	end = ft_substr(str, i, ft_strlen(str));
	free(str);
	str = ft_strjoin(start, end);
	free(start);
	free(end);
	free (comp);
	return (0);
}

char	*found_var(t_envp *envp, char *str, int i, int j)
{
	char	*new_str;
	char	*tail;

	if (i > 0)
	{
		new_str = ft_substr(str, 0, i);
		new_str = ft_strjoin(new_str, envp->content);
	}
	else
		new_str = ft_strdup(envp->content);
	if (str[j] != '\0')
	{
		tail = ft_substr(str, j, ft_strlen(str) - j);
		new_str = ft_strjoin(new_str, tail);
	}
	return (new_str);
}

char	*compare_var(char *str, t_envp *envp, int i)
{
	int	j;
	int	k;

	j = i + 1;
	k = 0;
	while (envp->variable[k] == str[j] && envp->variable[k] != '\0'
		&& str[j] != '\0' && str[j] != '<' && str[j] != '>'
		&& str[j] != ' ' && str[j] != '	' && str[j] != '\n' && str[j] != '$')
	{
		k++;
		j++;
	}
	if (envp->variable[k] == '\0')
		str = found_var(envp, str, i, j);
	return (str);
}

char	*replace_vars(t_mini *mini, char *str)
{
	t_envp	*envp;
	char	*comp;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			envp = mini->envp;
			while (envp != NULL)
			{
				comp = ft_strdup(str);
				str = compare_var(str, envp, i);
				if (ft_strcmp(comp, str) != 0)
					break ;
				envp = envp->next;
			}
			i = var_404(str, i, comp);
		}
		i++;
	}
	return (str);
}

void	arg_vars(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->arg_matrix[i] != NULL)
	{
		if (mini->arg_matrix[i][0] == '$' || mini->arg_matrix[i][0] == '"')
			mini->arg_matrix[i] = replace_vars(mini, mini->arg_matrix[i]);
		i++;
	}
}
