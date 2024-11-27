/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarto- <mafarto-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:15:27 by mafarto-          #+#    #+#             */
/*   Updated: 2024/11/26 15:02:46 by mafarto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	building_comp(char *str)
{
	if	(ft_strcmp(str, "pwd") == 0)
		return(0);
	if	(ft_strcmp(str, "export") == 0)
		return(1);
	if	(ft_strcmp(str, "env") == 0)
		return(2);
	return (-1);

}
