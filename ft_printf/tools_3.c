/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 01:16:42 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/26 10:24:46 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_big_x(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'a')
			str[i] = ('A');
		else if (str[i] == 'b')
			str[i] = ('B');
		else if (str[i] == 'c')
			str[i] = ('C');
		else if (str[i] == 'd')
			str[i] = ('D');
		else if (str[i] == 'e')
			str[i] = ('E');
		else if (str[i] == 'f')
			str[i] = ('F');
		i++;
	}
	return (str);
}

char	*get_p(unsigned long long i)
{
	unsigned long long	l;
	unsigned long long	k;
	unsigned long long	b;
	int					j;
	char				*str;

	str = ft_strnew(30);
	b = 0;
	l = 0;
	k = i;
	if (k == 16)
		write(1, "0", 1);
	if (k < 16)
		ft_putchar(symbol_type_x(k));
	while (k > 16)
	{
		k = i;
		i = i / 16;
		j = k - i * 16;
		str[l] = symbol_type_x(j);
		l++;
	}
	str = ft_strrev(str);
	return (str);
}

char	symbol_type_x(int i)
{
	char tmp;

	if (i < 10)
		tmp = i + '0';
	if (i == 10)
		tmp = 'a';
	if (i == 11)
		tmp = ('b');
	if (i == 12)
		tmp = ('c');
	if (i == 13)
		tmp = ('d');
	if (i == 14)
		tmp = ('e');
	if (i == 15)
		tmp = ('f');
	return (tmp);
}

char	*x_str(unsigned long long i, char *str)
{
	int					l;
	unsigned long long	j;
	unsigned long long	k;

	l = 0;
	k = i;
	while (k >= 16)
	{
		k = i;
		i = i / 16;
		j = k - i * 16;
		str[l] = symbol_type_x(j);
		l++;
	}
	return (str);
}

char	*ft_get_x(unsigned long long i)
{
	unsigned long long	l;
	unsigned long long	b;
	char				*str;

	str = ft_strnew(15);
	b = 0;
	l = 0;
	if (i == 16)
		write(1, "0", 1);
	if (i < 9)
		str[0] = i + '0';
	if (i < 16 && i > 10)
		str[0] = symbol_type_x(i);
	if (i > 16)
		str = x_str(i, str);
	str = ft_strrev(str);
	return (str);
}
