/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:00:12 by ngordobi          #+#    #+#             */
/*   Updated: 2024/12/12 00:00:12 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_pwd(t_envp *envp)
{
	t_envp	*var;

	var = envp;
	while (ft_strcmp(envp->variable, "PWD") != 0)
		envp = envp->next;
	ft_printf("%s\n", envp->content);
}
