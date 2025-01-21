/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:07:35 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/21 14:09:46 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*rm_quotes(char *arg, int i)
{
	int		j;
	int		k;
	char	q;
	char	*dup;
	char	*dup_2;

	if (ft_strcmp(arg, "''") == 0)
		return (arg);
	if (arg == NULL)
		return (ft_strdup(""));
	dup = NULL;
	dup_2 = NULL;
	while (arg[i] != '\0' && arg[i] != '"' && arg[i] != '\'')
		i++;
	if (arg[i] == '\0')
		return (arg);
	if (i > 0)
	{
		dup = ft_substr(arg, 0, i);
		q = arg[i];
	}
	j = ++i;
	while (arg[j] != '\0' && arg[j] != q)
		j++;
	if (j > i && dup == NULL)
		dup_2 = ft_substr(arg, i, j - i);
	else if (j > i && dup != NULL)
		dup_2 = ft_strjoin(dup, ft_substr(arg, i, j - i));
	else if (dup != NULL)
		dup_2 = ft_strdup(dup);
	if (dup != NULL)
		free(dup);
	k = ft_strlen(dup_2);
	i = ++j;
	while (arg[i] != '\0')
		i++;
	if (i > j && dup_2 == NULL)
		dup = ft_substr(arg, j, i - j);
	else if (i > j && dup_2 != NULL)
		dup = ft_strjoin(dup_2, ft_substr(arg, j, i - j));
	else if (dup_2 != NULL)
		dup = ft_strdup(dup_2);
	if (dup_2 != NULL)
		free(dup_2);
	free(arg);
	if (dup == NULL)
		return (ft_strdup(""));
	i = k - 1;
	while (dup[++k] != '\0')
		if (dup[k] == '"' || dup[k] == '\'')
			break ;
	if (dup[i] != '\0')
		return (rm_quotes(dup, k));
	return (dup);
}
