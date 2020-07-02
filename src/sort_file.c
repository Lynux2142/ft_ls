/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:16:11 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/02 14:33:42 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_file_list(t_list *file_list)
{
	t_list	*i;
	t_list	*j;
	void	*tmp;

	i = file_list;
	while (i != NULL)
	{
		j = file_list;
		while (j != NULL)
		{
			if (i->content && j->content
				&& ft_strcmp(i->content, j->content) < 0)
			{
				tmp = i->content;
				i->content = j->content;
				j->content = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
}
