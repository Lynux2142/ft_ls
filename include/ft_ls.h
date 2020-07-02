/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:59:20 by lguiller          #+#    #+#             */
/*   Updated: 2020/07/01 14:56:44 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include "libft.h"
# include <errno.h>

# include <stdio.h>

#define DEFAULT_PATH "."

void			sort_file_list(t_list *file_list);
void			print_file(char *dir_name);
void			explore(char *dir_name);
void			free_linked_list(t_list **list);

#endif
