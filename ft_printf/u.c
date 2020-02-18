/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 22:31:05 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/25 21:32:15 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_minus_u(t_printf *data)
{
	do_precision(data);
	ft_putstr(data->data);
	do_width(data);
	data->result += ft_strlen(data->data);
}

void	do_no_minus_u(t_printf *data)
{
	do_width(data);
	do_precision(data);
	ft_putstr(data->data);
	data->result += ft_strlen(data->data);
}

void	init_u(t_printf *data)
{
	data->len = ft_strlen(data->data);
	data->hash = 0;
	data->space = 0;
	data->plus = 0;
	data->difference = data->precision - data->len;
}

void	do_u(char *str, va_list list, t_printf *data)
{
	unsigned long long	type;

	if (spec_check(str, data->k) == 0)
		type = (unsigned int)va_arg(list, unsigned long long);
	else
	{
		if (change_type(str, data->k) == 1)
			type = (unsigned long int)va_arg(list, unsigned long long);
		else if (change_type(str, data->k) == 2)
			type = (unsigned char)va_arg(list, unsigned long long);
		else if (change_type(str, data->k) == 3)
			type = (unsigned short int)va_arg(list, unsigned long long);
		else if (change_type(str, data->k) == 4)
			type = (unsigned long long int)va_arg(list, unsigned long long);
	}
	if (data->precision == -1)
		data->data = ft_strnew(1);
	else
		data->data = ft_itoa_unsinged(type);
	init_u(data);
	if (data->minus == 1)
		do_minus_u(data);
	else
		do_no_minus_u(data);
	free(data->data);
}
