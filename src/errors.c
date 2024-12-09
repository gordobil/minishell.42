/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:06:42 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/09 12:35:07 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_messages(int error, char *str)
{
	if (error == -1)
		ft_printf("error: unclosed quotes\n");
	else if (error == -2)
		ft_printf("error: unclosed double quotes\n");
	else if (error == -3)
		ft_printf("%s: No such file or directory\n", str);
	else if (error == -4)
		ft_printf("%s: Error\n", str);
	else if (error == -5)
		ft_printf("cd: too many arguments\n");
	else if (error == -6)
		ft_printf("cd: %s: No such file or directory\n", str);
}
