/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:02:09 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/18 01:54:57 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free(t_data *data)
{
	while (data->next)
	{
		free(data->name);
		free(data->mode);
		free(data->time);
		free(data->usid);
		free(data->grid);
		free(data);
		data = data->next;
	}
}

void	init_flags(t_flags *flags)
{
	flags->i = 0;
	flags->l = 0;
	flags->a = 0;
	flags->t = 0;
	flags->r = 0;
	flags->rr = 0;
}
