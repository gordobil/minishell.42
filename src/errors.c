/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:06:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/01/21 11:23:48 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_messages(int error, char *str)
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
		ft_printf("%s: too many arguments\n", str);
	else if (error == -6)
		ft_printf("cd: %s: No such file or directory\n", str);
	else if (error == -7 && str[0] == '|')
		ft_printf("error: syntax error near unexpected token `|'\n");
	else if (error == -7 && str[0] != '|')
		return (0);
	else if (error == -8)
		ft_printf("error: no enviroment variables\n");
	else if (error == -9)
		ft_printf("error: unclosed pipe\n");
	return (error);
}
