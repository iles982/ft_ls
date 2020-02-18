/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:03:38 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:30:25 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_minus_c(t_printf *data)
{
	ft_putstr(data->data);
	do_width_c(data);
}

void	do_no_minus_c(t_printf *data)
{
	if (data->width > data->len)
		do_width_c(data);
	ft_putstr(data->data);
}

void	do_s(va_list list, t_printf *data)
{
	char *type;

	type = va_arg(list, char *);
	if (type == NULL)
	{
		data->data = ft_strnew(7);
		data->data = ft_strcpy(data->data, "(null)");
	}
	else if (data->precision != -1)
	{
		data->data = ft_strnew(ft_strlen(type) + 1);
		if (!data->precision)
			data->data = ft_strcpy(data->data, type);
		else if (data->precision)
			ft_strncpy(data->data, type, data->precision);
	}
	else
		data->data = ft_strnew(1);
	data->len = ft_strlen(data->data);
	data->result += ft_strlen(data->data);
	if (data->minus == 1)
		do_minus_c(data);
	else
		do_no_minus_c(data);
	free(data->data);
}
