/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:34:58 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/11 19:28:09 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(char *rdline)
{
	if (ft_strncmp("0", rdline, 2) == 0)
		printf ("0 ok\n");
	else
		return (-1);
	return (0);
}