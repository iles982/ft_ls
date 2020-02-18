/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:58:50 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/18 14:34:47 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_arg(t_flags *flags, char *str)
{
	t_ls		*ls;
	t_data		*data;
	t_data		*start;

	
	ls = (t_ls *)malloc(sizeof(t_ls));
	data = parse(ls, data, str);

}

int		main(int ac, char **av)
{
	t_data		*start;
	t_flags		flags[1];
	struct winsize	ws;

	init_flags(flags);
	if (ac != 1 && av[1][0] == '-')
		get_flags(flags, av);
	else
		flags->i++;
	if(ac == flags->i)
		do_arg(flags, "./");
	else
		while (ac > flags->i)
		{
			do_arg(flags, av[flags->i]);
			write(1, "\n", 1);
			flags->i++;
		}
	ioctl(0, TIOCGWINSZ, &ws);
	ft_printf ("lines %d\n", ws.ws_row);
    ft_printf ("columns %d\n\n\n", ws.ws_col);
	return (0);
}
