/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 13:24:11 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/17 13:26:29 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(char *file_name, int errnum)
{
	char	*err_file;

	err_file = get_dir_name(file_name);
	fprintf(stderr, "ft_ls: %s: %s%c", err_file, strerror(errnum), 10);
	free(err_file);
}
