/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_arg_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:18:44 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/29 18:01:20 by ngordobi         ###   ########.fr       */
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
		while (str[i] != '\0' && str[i] != '<' && str[i] != '>'
			&& str[i] != ' ' && str[i] != '	' && str[i] != '\n'
			&& str[i] != '$' && str[i] != '"' && str[i] != '\'')
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
		&& str[j] != '\0' && str[j] != '<' && str[j] != '>' && str[j] != '"'
		&& str[j] != '\'' && str[j] != ' ' && str[j] != '	' && str[j] != '\n'
		&& str[j] != '$')
	{
		k++;
		j++;
	}
	if (envp->variable[k] == '\0' && (str[j] == '\0' || str[j] == '<'
			|| str[j] == '"' || str[j] == '\'' || str[j] == '>'
			|| str[j] == ' ' || str[j] == '	' || str[j] == '\n'
			|| str[j] == '$'))
		str = found_var(envp->content, str, i, j);
	if (envp->next == NULL && ft_strcmp(str, comp) == 0)
		str = var_404(str, i, comp);
	return (str);
}

char	*replace_vars(t_mini *mini, char *str)
{
	t_envp	*envp;
	char	*comp;
	int		i;

	i = -1;
	while (str[++i] != '\0' && str)
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
			i = -1;
		}
	}
	return (str);
}

void	arg_vars(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini->arg_matrix[i] != NULL)
	{
		j = 0;
		while (mini->arg_matrix[i][j] != '\0')
		{
			if (mini->arg_matrix[i][j] == '$')
			{
				mini->arg_matrix[i] = replace_vars(mini, mini->arg_matrix[i]);
				break ;
			}
			j++;
		}
		i++;
	}
}
