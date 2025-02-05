/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:06:42 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/05 17:33:59 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_unexpected_token(int error, char *str)
{
	if (error == -7 || error == -12)
		ft_printf("error: syntax error near unexpected token `|'\n");
	else if (error == -10)
		ft_printf("error: syntax error near unexpected token `;'\n");
	else if (error == -11)
		ft_printf("error: syntax error near unexpected token `\\'\n");
	else if (error == -13)
		ft_printf("error: syntax error near unexpected token `<'\n");
	else if (error == -14)
		ft_printf("error: syntax error near unexpected token `>'\n");
	return (error);
}

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
	else if (error == -8)
		ft_printf("error: no enviroment variables\n");
	else if (error == -9)
		ft_printf("error: unclosed pipe\n");
	else if (error == -15)
		ft_printf("export: `%s': not a valid identifier\n", str);
	else
		return (error_unexpected_token(error, str));
	return (error);
}
