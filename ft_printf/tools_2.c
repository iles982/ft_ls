/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:45:29 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/29 07:42:29 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						change_type(char *str, int k)
{
	k = k - 1;
	while (str[k] == 'h' || str[k] == 'l' || str[k] == 'L')
	{
		if (str[k] == 'l' && str[k - 1] != 'l')
			return (1);
		else if (str[k] == 'h' && str[k - 1] == 'h')
			return (2);
		else if (str[k] == 'h' && str[k - 1] != 'h')
			return (3);
		else if (str[k] == 'l' && str[k - 1] == 'l')
			return (4);
		else if (str[k] == 'L')
			return (5);
	}
	return (0);
}

char					*ft_itoa_unsinged(unsigned long long n)
{
	unsigned long long	tmpn;
	int					len;
	int					negative;
	char				*str;

	tmpn = n;
	len = 2;
	negative = 0;
	while (tmpn /= 10)
		len++;
	len += negative;
	if ((str = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

unsigned long long		ft_squart(unsigned int i)
{
	unsigned long long	b;

	if (i == 0)
		return (1);
	b = 10;
	if (i > 1)
	{
		while (i != 1)
		{
			b = 10 * b;
			i--;
		}
	}
	return (b);
}

void					ft_trans_to_o(unsigned long long i, t_printf *data)
{
	unsigned long long	l;
	unsigned long long	k;
	unsigned long long	b;
	unsigned long long	j;
	int					f;

	b = 0;
	l = 0;
	k = i;
	data->data = ft_strnew(30);
	while (k > 8)
	{
		f = 1;
		k = i;
		i = i / 8;
		j = k - i * 8;
		data->data[l] = j + '0';
		l++;
	}
	data->data = ft_strrev(data->data);
	if (f == 1)
		return ;
	else
		data->data[0] = data->type + '0';
}

void					do_minus_int(t_printf *data)
{
	if (data->plus == 1 && ft_atoi(data->data) >= 0)
	{
		if (ft_atoi(data->data) >= 0)
			write(1, "+", 1);
		data->result++;
		data->len++;
	}
	else if (data->space == 1 && data->plus != 1 && ft_atoi(data->data) >= 0)
	{
		write(1, " ", 1);
		data->result++;
		data->len++;
	}
	if (data->precision != -1)
	{
		do_precision(data);
		ft_putstr(data->data);
		data->result += ft_strlen(data->data);
	}
	do_width(data);
}
