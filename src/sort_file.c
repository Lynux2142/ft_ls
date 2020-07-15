/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:16:11 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/15 15:54:35 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	switch_test(int *flag, t_file *a, t_file *b)
{
	int cmp;

	cmp = 0;
	if (flag[4])
		cmp = b->stat->st_mtime - a->stat->st_mtime;
	if (cmp == 0 || !flag[4])
		cmp = ft_strcmp(a->name, b->name);
	return (flag[3] ? cmp > 0 : cmp < 0);
}

void		sort_file_list(int *flag, t_list *file_list)
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
			if (switch_test(flag, (t_file*)i->content, (t_file*)j->content))
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
