/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:30:31 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/21 22:31:07 by tclarita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data		*revive_files(t_data **arr)
{
	t_data *start;
	int		i;
	t_data *tmp;

	i = 0;
	start = arr[0];
	tmp = start;
	while (arr[++i])
	{
		tmp->next = arr[i];
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (start);
}

void		sort_files_t(t_data **arr, int max)
{
	int		i;
	t_data	*tmp;

	i = 0;
	while (max--)
	{
		i = 0;
		while (arr[i + 1] != NULL)
		{
			if (arr[i]->time_t - arr[i + 1]->time_t < 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
	}
}

t_data		*reverse(t_data *start)
{
	t_data	*curr;
	t_data	*next;
	t_data	*prev;

	curr = start;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}
