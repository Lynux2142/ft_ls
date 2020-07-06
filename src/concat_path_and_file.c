/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_path_and_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:56:14 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/06 14:58:12 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*concat_path_and_file(char *path, char *filename)
{
	char	*dir_name;

	dir_name = ft_strnew(ft_strlen(path) + ft_strlen(filename) + 2);
	ft_strcat(dir_name, path);
	ft_strcat(dir_name, "/");
	ft_strcat(dir_name, filename);
	return (dir_name);
}

