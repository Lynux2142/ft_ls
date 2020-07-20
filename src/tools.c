/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:21:40 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/20 16:22:44 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	list_len(t_list *list)
{
	int	value;

	value = 0;
	while (list)
	{
		++value;
		list = list->next;
	}
	return (value);
}
