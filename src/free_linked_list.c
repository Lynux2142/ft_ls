/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:52:50 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/06 16:35:24 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_linked_list(t_list **list)
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
