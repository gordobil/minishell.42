/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:27:16 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/15 13:05:15 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		&& str[j] != ' ' && str[j] != '	' && str[j] != '\n')
	{
		k++;
		j++;
	}
	if (envp->variable[k] == '\0')
		str = found_var(envp, str, i, j);
	return (str);
}

char	*single_var(t_envp *envp, char *str)
{
	str++;
	while (envp != NULL && ft_strcmp(envp->variable, str) != 0)
		envp = envp->next;
	if (envp != NULL)
		return (ft_strdup(envp->content));
	else
		return (ft_strjoin("$", str));
}

char	*replace_vars(t_mini *mini, char *str)
{
	t_envp	*envp;
	char	*comp;
	int		i;

	if (str[0] == '$')
		return (single_var(mini->envp, str));
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
			free (comp);
		}
		i++;
	}
	return (str);
}
