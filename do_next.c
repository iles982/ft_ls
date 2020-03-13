/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_next.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:15:56 by tclarita          #+#    #+#             */
/*   Updated: 2020/03/13 13:23:08 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_next(t_data *data, t_ls *ls, t_flags *flags, char *path)
{
	if (flags->rr == 1)
		flag_rr(data, ls, flags, path);
	else
		just_do_it(data, ls, flags, path);
}

void	kostil(t_flags *flags, t_ls *ls, char *name)
{
	if (flags->l == 0)
		write(1, "\n", 1);
	ls->path = get_path_2(ls->path, name, ls);
}
