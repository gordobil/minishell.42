/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:04:13 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/12 00:04:13 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_envp	*get_last(char *variable, t_envp *envp)
{
	t_envp	*last;

	last = envp;
	while (last->next != NULL)
		last = last->next;
	while (last != NULL)
	{
		if (ft_strcmp(variable, last->variable) == 0)
			break ;
		last = last->prev;
	}
	return (last);
}

t_envp	*get_first(char *variable, t_envp *envp)
{
	t_envp	*first;

	first = envp;
	while (first != NULL)
	{
		if (ft_strcmp(variable, first->variable) == 0)
			break ;
		first = first->next;
	}
	return (first);
}

char	*get_var(char *arg)
{
	char	*var;
	int		i;

	if (is_it_a_var(arg) > 0)
	{
		i = 0;
		while (arg[i] != '=' && arg[i] != '\0')
			i++;
		var = ft_substr(arg, 0, i);
	}
	else
		var = ft_strdup(arg);
	return (var);
}

void	ms_export(t_pipes *pipes, t_envp *envp)
{
	t_envp	*first;
	t_envp	*last;
	char	*var;
	int		i;

	add_vars(pipes, pipes->mini);
	i = 0;
	while (pipes->command[++i] != NULL)
	{
		var = get_var(pipes->command[i]);
		first = get_first(var, envp);
		if (first != NULL)
		{
			last = get_last(var, envp);
			if (last != NULL && first->position != last->position)
			{
				free(first->content);
				first->content = ft_strdup(last->content);
				envp = unset_var(var, first->next);
			}
			first->exported = 1;
		}
		free(var);
	}
	pipes->mini->envp = envp;
}
