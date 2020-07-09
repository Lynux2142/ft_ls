/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:16:11 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/09 15:36:11 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_file_list(int *flag, t_list *file_list)
{
	t_list	*i;
	t_list	*j;
	void	*tmp;
	int		cmp;

	i = file_list;
	while (i != NULL)
	{
		j = file_list;
		while (j != NULL)
		{
			cmp = ft_strcmp(((t_file*)i->content)->name,
				((t_file*)j->content)->name);
			if (flag[3] ? cmp > 0 : cmp < 0)
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
