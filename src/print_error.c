/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 13:24:11 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/20 15:01:40 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(char *file_name, int errnum)
{
	char	*err_file;

	err_file = get_dir_name(file_name);
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(err_file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errnum), 2);
	free(err_file);
}
