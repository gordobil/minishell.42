/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:15:27 by mafarto-          #+#    #+#             */
/*   Updated: 2024/12/02 12:40:56 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	building_comp(char *str)
{
	if (ft_strcmp(str, "pwd") == 0)
		return (0);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (2);
	if (ft_strcmp(str, "cd") == 0)
		return (3);
	if (ft_strcmp(str, "echo") == 0)
		return (4);
	return (-1);
}
