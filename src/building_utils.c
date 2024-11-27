/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:15:27 by mafarto-          #+#    #+#             */
/*   Updated: 2024/11/27 19:04:33 by ngordobi         ###   ########.fr       */
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
	return (-1);
}
