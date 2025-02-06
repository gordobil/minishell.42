/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:11:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/10/14 13:38:56 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putptr(unsigned long p)
{
	int	count;

	count = 0;
	count += ft_putstr("0x");
	if (p == 0)
		count += ft_putchar('0');
	else
		count += ft_puthex(p, 'x');
	return (count);
}
