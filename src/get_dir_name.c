/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:04:41 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/16 15:05:14 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*get_dir_name(char *path)
{
	char	*name;
	int		path_len;
	int		i;
	int		j;

	path_len = ft_strlen(path);
	i = path_len - 1;
	while (path[i])
	{
		if (path[i] == '/')
			break ;
		--i;
	}
	if (!(name = ft_strnew(path_len - 1 - i)))
		exit(42);
	j = 0;
	while (path[++i])
		name[j++] = path[i];
	return (name);
}
