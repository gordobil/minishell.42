/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:21 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/07 15:20:39 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ms_exit(char *rdl)
{
	int		i;
	int		j;
	char	*exit;

	i = jump_spaces(rdl, 0);
	j = 0;
	exit = ft_strdup("exit");
	while (rdl[i] != '\0' && exit[j] != '\0' && rdl[i] == exit[j])
	{
		i++;
		j++;
	}
	if (exit[j] == '\0' && rdl[jump_spaces(rdl, i)] == '\0')
		return (0);
	else if ((rdl[i] == ' ' || rdl[i] == '	')
		&& (rdl[jump_spaces(rdl, i)] != '\0' || exit[j] == '\0'))
		return (error_messages(-5, "exit"), -1);
	else
		return (1);
}
