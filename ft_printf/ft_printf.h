/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:52:54 by tclarita          #+#    #+#             */
/*   Updated: 2020/01/29 08:55:44 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_printf
{
	long long	type;
	int			precision;
	int			width;
	int			result;
	int			minus;
	int			plus;
	int			hash;
	int			zero;
	int			space;
	int			i;
	int			k;
	int			k2;
	int			len;
	int			difference;
	char		*data;
}				t_printf;

void			do_type(t_printf *data, char *str, va_list list);
void			start_solution(t_printf *data, char *str, va_list list);
int				ft_printf(const char *format, ...);
int				ft_find_percent(char *str, int i, t_printf *data);
void			get_zero_value(t_printf *data);
int				ft_find_type(char *str, int i);
void			get_new_data(t_printf *data, char *str);
int				start_printf(char *str, t_printf *data, va_list list);
int				check_width(char *str, int i, int k);
int				check_precision(char *str, int k);
int				spec_check(char *str, int k);
void			do_int(char *str, va_list list, t_printf *data);
int				change_type(char *str, int k);
char			*ft_itoa_unsinged(unsigned long long n);
void			do_o(char *str, va_list list, t_printf *data);
void			do_u(char *str, va_list list, t_printf *data);
void			ft_trans_to_o(unsigned long long i, t_printf *data);
void			ft_putnbr_u(unsigned long long n);
char			*ft_get_x(unsigned long long i);
void			do_x(char *str, va_list list, t_printf *data);
char			*ft_big_x(char *str);
void			do_big_x(char *str, va_list list, t_printf *data);
void			do_c(va_list list, t_printf *data);
void			do_s(va_list list, t_printf *data);
char			symbol_type_x(int i);
char			*get_p(unsigned long long i);
void			do_p(va_list list, t_printf *data);
void			print(t_printf *data);
void			do_width(t_printf *data);
void			do_precision(t_printf *data);
void			init_o(t_printf *data);
void			do_no_minus_c(t_printf *data);
void			do_minus_c(t_printf *data);
void			do_width_c(t_printf *data);
int				check_hashtag_flag(char *str, int i);
int				check_space_flag(char *str, int i);
int				check_zero_flag(char *str, int i);
int				check_plus_flag(char *str, int i);
int				check_minus_flags(char *str, int i);
void			do_minus_int(t_printf *data);
void			check_it(t_printf *data);
void			check_2(t_printf *data, long long type);
void			int_init(t_printf *data, long long type);
void			do_width_spec(t_printf *data, long long type);
void			ft_find_percent_2(int k, t_printf *data);
int				find_i(char *str, int i, t_printf *data);
void			big_x(t_printf *data, long long type);
void			costil_2(t_printf *data, long long type);
void			do_f(char *str, va_list list, t_printf *data);
void			do_minus_f(t_printf *data, long double type);
void			do_no_minus_f(t_printf *data, long double type);
int				ft_get_f_len(long double type);
void			init_f(t_printf *data);
void			ft_putnbr_f(long double type, t_printf *data);
#endif
