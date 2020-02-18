/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:50:02 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:30:05 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				do_minus_xx(t_printf *data)
{
	if (data->hash == 1)
		ft_putstr("0X");
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
	}
	do_width(data);
	data->result += ft_strlen(data->data);
}

void				do_no_minus_xx(t_printf *data)
{
	if (data->zero == 1 && data->hash == 1)
		ft_putstr("0X");
	do_width(data);
	if (data->hash == 1 && data->zero == 0)
		ft_putstr("0X");
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
	}
	data->result += ft_strlen(data->data);
}

void				init_xx(t_printf *data)
{
	data->len = ft_strlen(data->data);
	data->difference = data->precision - data->len;
	if (data->hash == 1)
	{
		data->len += 2;
		data->result += 2;
	}
}

unsigned long long	do_big_x_2(va_list list, char *str, t_printf *data)
{
	unsigned long long type;

	if (change_type(str, data->k) == 1)
		type = (unsigned long int)va_arg(list, unsigned long long);
	else if (change_type(str, data->k) == 2)
		type = (unsigned char)va_arg(list, unsigned long long);
	else if (change_type(str, data->k) == 3)
		type = (unsigned short int)va_arg(list, unsigned long long);
	else
		type = (unsigned long long int)va_arg(list, unsigned long long);
	return (type);
}

void				do_big_x(char *str, va_list list, t_printf *data)
{
	unsigned long long		type;

	if (spec_check(str, data->k) == 0)
		type = (unsigned int)va_arg(list, unsigned long long);
	else
		type = do_big_x_2(list, str, data);
	if (type == 0 && data->precision != -1)
	{
		write(1, "0", 1);
		data->result++;
		return ;
	}
	if (data->precision != -1)
		big_x(data, type);
	else
		data->data = ft_strnew(1);
	init_xx(data);
	if (data->minus == 1)
		do_minus_xx(data);
	else
		do_no_minus_xx(data);
	free(data->data);
}
