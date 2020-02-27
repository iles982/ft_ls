/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:30:31 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/25 21:32:22 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_files_t(t_data *arr, int max, t_ls *ls)
{
	int		i;
	t_data	tmp;

	i = 0;
	while (max--)
	{
		i = 0;
		while (i < ls->i)
		{
			if (arr[i].time_t - arr[i + 1].time_t < 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
	}
}
