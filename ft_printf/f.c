/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 21:00:19 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/29 09:48:37 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

__int128_t		ft_atoi_f(char *str)
{
	__int128_t	res;
	__int128_t	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
		*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

void			f_precision(long double tmp, t_printf *data)
{
	__int128_t	tmp2;

	while (data->precision >= 1)
	{
		tmp *= 10;
		tmp2 = tmp;
		ft_putchar(tmp + '0');
		tmp -= tmp2;
		data->precision--;
		data->result++;
	}
}

void			ft_putnbr_f(long double type, t_printf *data)
{
	long double	tmp;
	__int128_t	tmp2;
	int			start;
	char		*str;

	tmp = type;
	start = 0;
	str = ft_strnew(25);
	while (tmp > 1)
		tmp /= 10;
	while (data->len >= 2)
	{
		tmp *= 10;
		if (start != 0)
			tmp -= tmp2 * 10;
		tmp2 = tmp;
		ft_putchar(tmp2 + '0');
		str[start] = tmp + '0';
		data->len--;
		start++;
	}
	write(1, ".", 1);
	tmp = type - ft_atoi_f(str);
	free(str);
	f_precision(tmp, data);
}

void			do_f(char *str, va_list list, t_printf *data)
{
	long double type;

	if (change_type(str, data->k) == 0 || change_type(str, data->k) == 1)
		type = (double)va_arg(list, double);
	if (change_type(str, data->k) == 5)
		type = (long double)va_arg(list, long double);
	if (type == 0)
		write(1, "No", 2);
	data->len = ft_get_f_len(type);
	data->len += data->precision + 1;
	data->result += data->len;
	init_f(data);
	if (data->minus == 1)
		do_minus_f(data, type);
	if (data->minus == 0)
		do_no_minus_f(data, type);
}
