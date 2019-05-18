/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 16:10:02 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:55:35 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	check_digit(char **curr_str, char *str, t_info *info)
{
	check_end(str, curr_str, info);
	while (*str && ft_isdigit(*str) && info->stop == 0)
	{
		info->width = info->width * 10 + (*str - '0');
		(*curr_str)++;
		str++;
	}
	check_end(str, curr_str, info);
}

void	check_prec(char **curr_str, char *str, t_info *info)
{
	check_end(str, curr_str, info);
	if (*str && *str == '.' && info->stop == 0)
	{
		info->is_prec = 1;
		str++;
		(*curr_str)++;
		while (*str && ft_isdigit(*str) && info->stop == 0)
		{
			info->prec = info->prec * 10 + (*str - '0');
			(*curr_str)++;
			str++;
		}
	}
	check_end(str, curr_str, info);
}

void	set_all_flags(char **curr_str, char *str, t_info *info)
{
	if (info->stop == 0)
		set_len_modif(str, info);
	if ((info->length == HH || info->length == LL) && info->stop == 0)
	{
		(*curr_str) += 2;
		str += 2;
	}
	else if (info->length > 0 && info->stop == 0)
	{
		(*curr_str)++;
		str++;
	}
	if (info->stop == 0)
		set_flags(*str, info);
	if (info->flag != 0 && info->stop == 0)
	{
		set_flags(*str, info);
		(*curr_str)++;
		str++;
	}
}

void	write_conv(char **curr_str, t_info *info, va_list args)
{
	check_extra(curr_str, *curr_str, info);
	check_digit(curr_str, *curr_str, info);
	check_prec(curr_str, *curr_str, info);
	set_all_flags(curr_str, *curr_str, info);
	if (curr_str != 0)
		conv_flags(info, args);
}

int		parse_str(char *str, t_info *info, va_list args)
{
	int		c_len;
	t_info	*begin;

	begin = info;
	c_len = 0;
	while (*str)
	{
		while (*str && *str != '%')
		{
			c_len++;
			write(1, str++, 1);
		}
		if (*str == '%')
		{
			info->stop = 0;
			str++;
			write_conv(&str, info, args);
			if (info->c_len > 0)
				c_len += info->c_len;
			info->next = ft_init_lst();
			info = info->next;
		}
	}
	ft_free_lst(begin);
	return (c_len);
}
