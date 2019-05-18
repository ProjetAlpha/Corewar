/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printf.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/29 18:40:57 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 19:28:06 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

typedef struct		s_info
{
	int				width;
	int				prec;
	int				is_prec;
	long long		i_arg;
	unsigned long	u_arg;
	long long		t_len;
	long long		tmp;
	int				length;
	int				flag;
	int				skip;
	int				stop;
	int				extra[8];
	int				pos[2];
	size_t			c_len;
	int				neg;
	struct s_info	*next;
}					t_info;

void				conv_length(t_info *info);
void				conv_ulength(t_info *info);
int					check_extra(char **curr_str, char *str, t_info *info);
void				set_len_modif(char *str, t_info *info);
int					get_escape_len(char *str, int begin, int len, int c);
char				*ft_escape(char *str, int c, int start, int len);
int					is_extra_c(char c);
int					is_len_modif(char c);
int					is_empty(int *extra);
int					is_extra(int *extra, int id);
int					is_flag(char c);
int					is_valid(char c);
int					is_zero(t_info *info);
char				*conv_base(t_info *info, int base, int len);
char				*conv_ubase(t_info *info, int base, int len);
int					get_nbr_len(t_info *info, int base, int type);
char				*fill_str(int len, int c);
void				set_flags(char c, t_info *info);
char				*get_zero(t_info *info);
char				*set_zero(int n);
void				print_struct(t_info *info);
void				check_end(char *str, char **curr_str, t_info *info);
char				*conv_flags(t_info *info, va_list args);
void				conv_strings(char *str, t_info *info, int len);
void				conv_char(int c, t_info *info);
void				conv_void(unsigned long int n, t_info *info);
void				conv_basic(t_info *info);
void				conv_un(t_info *info);
void				conv_o(t_info *info);
void				conv_hexa(t_info *info);
char				*conv_float(double n, t_info *info);
void				ft_wr_inc(char *str, size_t len, t_info *info);
void				ft_wr_len(char *str, t_info *info);
void				ft_free_lst(t_info *info);
t_info				*ft_init_lst(void);
int					parse_str(char *str, t_info *info, va_list args);
int					ft_printf(const char *str, ...)
					 __attribute__((format(printf,1,2)));

# define FLAGS "sSpdDioOuUxXcCfF"
# define ABS(n) (n < 0 ? -n : n)

enum	e_padtype{P_ZERO = 1, P_SPACE = 2};

enum	e_pos{START = 0, END = 1};

enum	e_length{H = 1, HH = 2, L = 3, LL = 4, J = 5, Z = 6};

enum	e_extra{H_TAG = 1, ZERO = 2, MINUS = 3,
	PLUS = 4, SPACE = 6, PERCENT = 7};

typedef enum	e_flags
{
	S = 1, LS = 2, P = 3, D = 4, LD = 5,
	I = 6, O = 7, LO = 8, U = 9, LU = 10,
	X = 11, LX = 12, C = 13, LC = 14, F = 15, LF = 16
}				t_values;

#endif
