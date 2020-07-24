# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/26 14:00:46 by lguiller          #+#    #+#              #
#    Updated: 2020/07/24 13:44:20 by lguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##  VARIABLES   ##
##################

OPE_SYS			= $(shell uname)
NAME			= ft_ls

SRCS1			= ft_ls.c
SRCS1			+= sort_file.c
SRCS1			+= print_file.c
SRCS1			+= recursive_exploration.c
SRCS1			+= free_function.c
SRCS1			+= flag_parsing.c
SRCS1			+= concat_path_and_file.c
SRCS1			+= print_tools.c
SRCS1			+= print_tools2.c
SRCS1			+= get_length.c
SRCS1			+= get_dir_name.c
SRCS1			+= print_error.c
SRCS1			+= create_print_args.c
SRCS1			+= tools.c

SRCS			= $(addprefix $(SRCS_DIR)/, $(SRCS1))
OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS1:.c=.o))

SRCS_DIR		= ./src
OBJS_DIR		= ./obj
LIBFT_DIR		= ./libft
INCLUDES_DIR	= ./include

LIBFT			= $(LIBFT_DIR)/libft.a
HEADER			= $(INCLUDES_DIR)/ft_ls.h

FLAGS			= -Wall -Wextra -Werror -g
CC				= clang

INCLUDES		= $(addprefix -I, $(INCLUDES_DIR) $(LIBFT_DIR))

##################
##    COLORS    ##
##################

_BLACK		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_VIOLET		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_CLEAR		= "\033[2K"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"

##################
##   TARGETS    ##
##################

.PHONY: all launch clean fclean re norme title
.SILENT:

all: launch

launch: title
	$(MAKE) $(LIBFT)
	echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	$(MAKE) $(NAME)
	echo $(_GREEN)"\nDone."$(_END)$(_SHOW_CURS)

$(OBJS_DIR):
	mkdir $@

$(LIBFT): FORCE
	$(MAKE) -sC libft
	echo

FORCE:

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	printf $<

clean:
	$(MAKE) -sC libft clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) -sC libft fclean
	$(RM) $(NAME)

re:
	$(MAKE) -s fclean
	$(MAKE) -s

norme:
	norminette $(SRCS) $(INCLUDES_DIR)/*.h
	$(MAKE) -C libft norme

title:
	echo $(_RED)
	echo "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"
	echo
	echo "              :::::::::: :::::::::::           :::        ::::::::        "
	echo "             :+:            :+:               :+:       :+:    :+:        "
	echo "            +:+            +:+               +:+       +:+                "
	echo "           :#::+::#       +#+               +#+       +#++:++#++          "
	echo "          +#+            +#+               +#+              +#+           "
	echo "         #+#            #+#               #+#       #+#    #+#            "
	echo "        ###            ###    ########## ########## ########              "
	echo
	echo "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"
	printf $(_YELLOW)
	echo "                                                           2018 © lguiller"
	echo $(_END)
