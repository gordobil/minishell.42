/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:27:16 by ngordobi          #+#    #+#             */
/*   Updated: 2024/11/13 19:33:24 by ngordobi         ###   ########.fr       */
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
		new_str = ft_strjoin(new_str, envp->name);
	}
	else
		new_str = ft_strdup(envp->name);
	if (str[j] != '\0')
	{
		tail = ft_substr(str, j, ft_strlen(str) - j);
		new_str = ft_strjoin(new_str, tail);
	}
	return (new_str);
}

char	*replace_vars(t_mini *mini, char *str)
{
	t_envp	*envp;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			envp = mini->envp;
			while (envp != NULL)
			{
				j = i + 1;
				k = 0;
				while (envp->variable[k] == str[j] && envp->variable[k] != '\0'
						&& str[j] != '\0')
				{
					k++;
					j++;
				}
				if (envp->variable[k] == '\0')
				{
					str = found_var(envp, str, i, j);
					break ;
				}
				envp = envp->next;
			}
		}
		i++;
	}
	return (str);
}
