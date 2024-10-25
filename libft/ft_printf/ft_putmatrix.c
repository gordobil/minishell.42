/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmatrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:33:27 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/14 13:33:27 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putmatrix(char **matrix)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (matrix[0] == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (matrix[i] != NULL)
	{
		count += ft_putstr(matrix[i]);
		count += ft_putchar('\n');
		i++;
	}
	return (count);
}
