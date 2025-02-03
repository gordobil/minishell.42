/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:18 by ngordobi          #+#    #+#             */
/*   Updated: 2025/02/03 14:21:47 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	format(va_list list, const char *arg)
{
	int	count;

	count = 0;
	if (*arg == 'c')
		count = ft_putchar(va_arg(list, int));
	else if (*arg == 's')
		count = ft_putstr(va_arg(list, char *));
	else if (*arg == 'm')
		count = ft_putmatrix(va_arg(list, char **));
	else if (*arg == 'p')
		count = ft_putptr(va_arg(list, unsigned long));
	else if (*arg == 'd' || *arg == 'i')
		count = ft_putnbr(va_arg(list, int));
	else if (*arg == 'u')
		count = ft_putunbr(va_arg(list, unsigned int));
	else if (*arg == 'x' || *arg == 'X')
		count = ft_puthex(va_arg(list, unsigned int), *arg);
	else if (*arg == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *first_arg, ...)
{
	va_list	list;
	int		count;

	va_start(list, first_arg);
	count = 0;
	while (*first_arg)
	{
		if (*first_arg != '%')
			count += ft_putchar(*first_arg);
		else
		{
			first_arg++;
			count += format(list, first_arg);
		}
		first_arg++;
	}
	va_end(list);
	return (count);
}
