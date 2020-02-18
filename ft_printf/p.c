/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:31:23 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:23:13 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_p_2(t_printf *data)
{
	data->len = ft_strlen(data->data);
	data->result += ft_strlen(data->data);
	if (data->minus == 1)
		do_minus_c(data);
	else
		do_no_minus_c(data);
}

void	do_p1(t_printf *data)
{
	while (data->width > 3)
	{
		write(1, " ", 1);
		data->width--;
		data->result++;
	}
	ft_putstr(data->data);
	data->result += 3;
	while (data->precision > 1)
	{
		write(1, "0", 1);
		data->precision--;
		data->result++;
	}
}

void	do_p2(t_printf *data)
{
	ft_putstr(data->data);
	data->result += 3;
	while (data->precision > 1)
	{
		write(1, "0", 1);
		data->precision--;
		data->result++;
	}
	while (data->width > 3)
	{
		write(1, " ", 1);
		data->width--;
		data->result++;
	}
}

void	do_p3(t_printf *data, unsigned long long type)
{
	char				*tmp;
	char				*tmp2;

	tmp2 = get_p(type);
	if (tmp2[0] == '0')
		tmp = "0x1";
	else
		tmp = "0x";
	while ((size_t)data->precision > ft_strlen(tmp2))
	{
		tmp = ft_strjoin(tmp, "0");
		data->precision--;
	}
	data->data = ft_strjoin(tmp, tmp2);
	free(tmp2);
}

void	do_p(va_list list, t_printf *data)
{
	unsigned long long	type;

	type = va_arg(list, unsigned long long);
	if (type == 0 && data->precision != -1)
	{
		data->data = ft_strnew(3);
		data->data = ft_strcpy(data->data, "0x0");
		if (data->minus == 0)
			do_p1(data);
		else
			do_p2(data);
		free(data->data);
		return ;
	}
	else if (data->precision == -1)
	{
		data->data = ft_strnew(2);
		data->data = ft_strcpy(data->data, "0x");
	}
	else
		do_p3(data, type);
	do_p_2(data);
	free(data->data);
}
