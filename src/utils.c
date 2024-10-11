/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:50:12 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/11 18:50:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*mini_title(void)
{
	char	*title;
	char	buffer[4096];

	title = ft_strjoin(BLUE"minishell: "CYAN"~", getcwd(buffer, 4096));
	title = ft_strjoin(title, BLUE"¬ "WHITE);
	return (title);
}