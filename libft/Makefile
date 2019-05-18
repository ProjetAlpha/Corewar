# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kgrosjea <kev.grosjean@gmail.com>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/02 13:36:56 by kgrosjea     #+#   ##    ##    #+#        #
#    Updated: 2019/03/28 21:11:09 by thbrouss    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

CC			= gcc
NAME		= libft.a

FLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I ./libft.h

SRCDIR		= ./
BINDIR		= ./

SRC			=	ft_putchar.c			\
				ft_putstr.c				\
				ft_tolower.c			\
				ft_isalnum.c			\
		        ft_isalpha.c			\
    		    ft_isascii.c			\
				ft_isdigit.c			\
				ft_isprint.c			\
				ft_isnumber.c			\
				ft_toupper.c			\
				ft_atoi.c				\
				ft_strcpy.c				\
				ft_strncpy.c			\
				ft_strcat.c				\
				ft_strncat.c			\
				ft_strlcat.c			\
				ft_strcmp.c				\
				ft_strncmp.c			\
				ft_strstr.c				\
				ft_strnstr.c			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strlen.c				\
				ft_strdup.c				\
				ft_memset.c				\
				ft_bzero.c				\
				ft_memcpy.c				\
				ft_memccpy.c			\
				ft_memmove.c			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_memalloc.c			\
				ft_memdel.c				\
				ft_strnew.c				\
				ft_strdel.c				\
				ft_strclr.c				\
				ft_strctn.c				\
				ft_striter.c			\
				ft_striteri.c			\
				ft_strmap.c				\
				ft_strmapi.c			\
				ft_strequ.c				\
				ft_strnequ.c			\
				ft_strsub.c 			\
				ft_strjoin.c			\
				ft_strtrim.c			\
				ft_strsplit.c			\
				ft_itoa.c				\
				ft_putendl.c			\
				ft_putnbr.c				\
				ft_putchar_fd.c			\
				ft_putstr_fd.c			\
				ft_putendl_fd.c			\
				ft_putnbr_fd.c			\
				ft_lstnew.c				\
				ft_lstdelone.c			\
				ft_lstdel.c				\
				ft_lstadd.c				\
				ft_lstiter.c			\
				ft_lstmap.c				\
				ft_pow.c				\
				ft_sqrt.c				\
				ft_isupper.c			\
				ft_islower.c			\
				ft_isspace.c			\
				ft_factorial.c			\
				ft_char_belongs_to.c	\
				get_next_line.c			\
				ft_max.c				\
				ft_min.c				\
				ft_nblen.c				\
				ft_lltoa_base.c			\
				ft_ulltoa_base.c		\
				ft_strcapitalize.c		\
				ft_strjoin_f.c		\
				ft_ldtoa.c				\
				ft_manage_colors.c		\
				ft_free_lst.c				\
				ft_strrev.c				\
				ft_write_len.c		\
				ft_write_inc.c  \
				ft_printf.c			\
				parse_input.c \
				handle_padding.c \
				printf_utils.c \
				printf_utils2.c \
				conv_all.c \
				conv_basic.c \
				conv_hex.c \
				conv_o.c \
				conv_strings.c \
				conv_un.c \
				conv_void.c \
				ft_init_lst.c \
				is_helper.c

BIN			= $(SRC:.c=.o)

SRCS		= $(addprefix $(SRCDIR), $(SRC))
BINS		= $(addprefix $(BINDIR), $(BIN))

COMPILE		= $(CC) $(FLAGS) $(INCLUDES)

.PHONY: all clean fclean re

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

$(NAME): $(BINS)

	@ar rc $(NAME) $^
	@echo "\n\n${B}[LIBRARY \"$(NAME)\" COMPILED]\n"
	@ranlib $(NAME)
	@echo "${B}[LIBRARY \"$(NAME)\" INDEXED]\n"

$(BINDIR)%.o: $(SRCDIR)%.c libft.h

	@$(COMPILE) -o $@ -c $< && echo "${G} \c"

clean:

	@echo "\n${R}[CLEANING $(NAME) BINARIES]\n"
	@rm -f $(BINS)

fclean: clean

	@echo "${R}[REMOVING \"$(NAME)\"]\n"
	@rm -f $(NAME)

debug:

	@echo "\n${B}[COMPILING WITH DEBUG FLAGS]" && make re FLAGS=' -Wall -Wextra -Werror -g'

re: fclean all
