/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:51:10 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 21:01:52 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include "../includes/printf.h"
# define BUFF_SIZE 1000
# define TRUE 1
# define FALSE 0
# define FORMAT ".#0+- hlL"
# define TYPES "spdiouxXcefg"
# define LENGTH "hlL"
# define NULLSTR "(null)"
# define COLORS "dDrRgGyYbBmMcC"
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define UINT_MAX 4294967295
# define LONG_MAX 9223372036854775807U
# define LONG_MIN -9223372036854775808U
# define ULONG_MAX 18446744073709551615U

typedef int		t_bool;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_restfd
{
	int				fd;
	char			*rest;
	struct s_restfd	*next;
}				t_restfd;

typedef struct	s_flags
{
	t_bool	hashtag;
	t_bool	minus;
	t_bool	plus;
	t_bool	zero;
	t_bool	space;
	t_bool	coma;
}				t_flags;

typedef struct	s_format
{
	struct s_flags	*flags;
	size_t			width;
	t_bool			point;
	size_t			precision;
	char			*length;
	char			type;
}				t_format;

typedef struct	s_expr
{
	char			*expr;
	size_t			length;
	struct s_format	*format;
	struct s_expr	*next;
}				t_expr;

int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
t_bool			ft_char_belongs_to(const char *values, char c);
int				ft_factorial(int n);
int				ft_isalnum(int c, char type);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isspace(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
t_bool			ft_isnumber(char *line);
char			*ft_itoa(int n);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
int				ft_pow(int n, unsigned int power);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
int				ft_sqrt(int n, int return_closest_supp);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
t_bool			ft_strctn(const char *str, char c);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				get_next_line(const int fd, char **line);
int				ft_max(int nb1, int nb2);
int				ft_min(int nb1, int nb2);
size_t			ft_nblen(long long int nb);
char			*ft_strrev(char *str);
t_bool			ft_lltoa_base(char **str, long int num, int base);
t_bool			ft_ulltoa_base(char **str, unsigned long int n, int base);
char			*ft_strcapitalize(char *str);
t_expr			*create_new_t_expr(void);
t_format		*create_new_t_format(void);
t_flags			*create_new_t_flags(void);
char			*get_flags(const char *sub_expr);
char			*get_width(const char *sub_expr);
char			*get_precision(const char *sub_expr);
char			*get_length(const char *sub_expr);
int				set_width(t_format *format, char *width);
int				set_point(t_format *format, const char *sub_expr);
int				set_precision(t_format *format, char *precision);
int				set_length(t_format *format, char *length);
char			*convert_string(t_format *format, size_t *len, va_list args);
char			*convert_decimal(t_format *format, size_t *len, va_list args);
char			*convert_octal(t_format *format, size_t *len, va_list args);
char			*convert_hexa(t_format *format, size_t *len, va_list args);
char			*convert_unsigned(t_format *format, size_t *len, va_list args);
char			*convert_character(t_format *format, size_t *len, va_list args);
char			*convert_pointer(t_format *format, size_t *len, va_list args);
char			*format_character(t_format *format, size_t *len, char arg);
char			*ft_ldtoa(long double nbr, t_format *format);
char			*convert_float(t_format *format, size_t *len, va_list args);
t_bool			parse_expression(const char *expr, t_expr **first);
char			*manage_colors(t_expr *curr);
void			ft_jump_line(int fd, char **line);
char			*ft_strjoin_f(char *s1, char *s2);

#endif
