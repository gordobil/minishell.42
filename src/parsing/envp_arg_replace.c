/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_arg_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:18:44 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/09 23:27:29 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_404(char *str, int i, char *comp)
{
	char	*start;
	char	*end;

	start = ft_substr(str, 0, i);
	i++;
	if (str[i] < '0' || str[i] > '9')
		while ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_')
			i++;
	else
		i++;
	end = ft_substr(str, i, ft_strlen(str));
	free(str);
	if (start || end)
		str = ft_strjoin(start, end);
	if (start)
		free(start);
	if (end)
		free(end);
	free (comp);
	return (str);
}

char	*found_var(char *content, char *str, int i, int j)
{
	char	*new_str;
	char	*tail;

	if (i > 0)
	{
		new_str = ft_substr(str, 0, i);
		new_str = ft_strjoin(new_str, content);
	}
	else
		new_str = ft_strdup(content);
	if (str[j] != '\0')
	{
		tail = ft_substr(str, j, ft_strlen(str) - j);
		new_str = ft_strjoin(new_str, tail);
	}
	return (new_str);
}

char	*compare_var(char *str, t_envp *envp, int i, char *comp)
{
	int		j;
	int		k;

	j = i + 1;
	k = 0;
	while (envp->variable[k] == str[j] && envp->variable[k] != '\0'
		&& ((str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
	{
		k++;
		j++;
	}
	if (envp->variable[k] == '\0' && ((str[j] < 'a' || str[j] > 'z')
			&& (str[j] < 'A' || str[j] > 'Z') && (str[j] < '0' || str[j] > '9')
			&& str[j] != '_'))
		str = found_var(envp->content, str, i, j);
	else if (envp->next == NULL && ft_strcmp(str, comp) == 0)
		str = var_404(str, i, comp);
	return (str);
}

char	*replace_vars(t_mini *mini, char *str, int i)
{
	t_envp	*envp;
	char	*comp;

	while (str[i] != '\0' && str)
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str = found_var(ft_itoa(mini->last_ret), str, i, i + 2);
			i = -1;
		}
		else if (str[i] == '$' && str[i + 1] != '?')
		{
			envp = mini->envp;
			comp = ft_strdup(str);
			while (envp != NULL && ft_strcmp(comp, str) == 0)
			{
				str = compare_var(str, envp, i, comp);
				envp = envp->next;
			}
			break ;
		}
		i++;
	}
	return (str);
}

void	arg_vars(t_mini *mini)
{
	int		i;
	int		j;
	int		q;

	i = 0;
	q = 0;
	while (mini->arg_matrix[i] != NULL)
	{
		j = 0;
		while (mini->arg_matrix[i][j] != '\0')
		{
			if (mini->arg_matrix[i][j] == '\'')
				j = jump_single_quotes(mini->arg_matrix[i], j);
			else if (mini->arg_matrix[i][j] == '$')
			{
				mini->arg_matrix[i] = replace_vars(mini,
						mini->arg_matrix[i], j);
				j = -1;
			}
			j++;
		}
		i++;
	}
}
