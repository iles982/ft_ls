/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclarita <tclarita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:02:09 by tclarita          #+#    #+#             */
/*   Updated: 2020/02/21 20:19:32 by tclarita         ###   ########.fr       */
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
	flags->i = 1;
	flags->l = 0;
	flags->a = 0;
	flags->t = 0;
	flags->r = 0;
	flags->rr = 0;
	flags->max_len_group = 0;
	flags->max_len_owner = 0;
	flags->max_len_links = 0;
	flags->max_len_size = 0;
	flags->max_len_name = 0;
}

void	check_len(t_data *data, t_flags *flags)
{
	if (ft_int_len(data->link) > flags->max_len_links)
		flags->max_len_links = ft_int_len(data->link) + 1;
	if (ft_strlen(data->usid) > flags->max_len_owner)
		flags->max_len_owner = ft_strlen(data->usid) + 1;
	if (ft_strlen(data->grid) > flags->max_len_group)
		flags->max_len_group = ft_strlen(data->grid) + 1;
	if (ft_int_len(data->size) > flags->max_len_size)
		flags->max_len_links = ft_int_len(data->link) + 1;
	if (ft_strlen(data->name) > flags->max_len_name)
		flags->max_len_name = ft_strlen(data->name) + 1;
}

void		ft_lstrev(t_data **alst)
{
	t_data	*prev;
	t_data	*cur;
	t_data	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

void	ft_lstswap(t_data *lst1, t_data *lst2)
{
	t_data *tmp;

	tmp = lst1;
	lst2 = lst1;
	lst1 = lst2;
	ft_printf("%s, %s\n", lst1->name, lst2->name);
}

t_data	*sort_t(t_data *data, t_flags *flags)
{
	t_data	*begin_list;
	t_data	*cur;
	t_data	*next;
	t_data	*tmp;
	t_data	*prev;

	cur = data;
	prev = cur;
	begin_list = data;
	while (data->next)
	{
		if (data->time_t > data->next->time_t)
			ft_lstswap(data, data->next);
		data = data->next;
	}
	exit(0);
	return (begin_list);
}
