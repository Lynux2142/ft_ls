/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:01:52 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/15 14:07:04 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_linked_file_list(t_list **list)
{
	t_list	*current;
	t_list	*tmp;

	current = *list;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_memdel((void**)&((t_file*)tmp->content)->name);
		ft_memdel((void**)&((t_file*)tmp->content)->stat);
		ft_memdel((void**)&tmp->content);
		ft_memdel((void**)&tmp);
	}
}

void	free_linked_dir_list(t_list **list)
{
	t_list	*current;
	t_list	*tmp;

	current = *list;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_memdel((void**)&((t_file*)tmp->content)->name);
		ft_memdel((void**)&tmp->content);
		ft_memdel((void**)&tmp);
	}
}

void	free_time(char **file_date, char **file_time)
{
	int i;

	i = -1;
	while (file_date[++i])
		ft_memdel((void**)&file_date[i]);
	ft_memdel((void**)&file_date);
	i = -1;
	while (file_time[++i])
		ft_memdel((void**)&file_time[i]);
	ft_memdel((void**)&file_time);
}
