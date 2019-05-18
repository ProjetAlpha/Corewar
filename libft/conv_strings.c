/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_strings.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 12:05:53 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:57:52 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		get_padding(char *str, t_info *info)
{
	int		len;
	char	*tmp;

	info->t_len = 0;
	len = (str == NULL) ? 6 : ft_strlen(str);
	if (info->extra[ZERO] == ZERO &&
			info->width > 0 && info->extra[MINUS] != MINUS)
	{
		if (info->prec >= 0 && info->is_prec == 1 && info->prec < len)
			ft_wr_len(tmp = set_zero(info->width -
						(len - (len - info->prec))), info);
		else
			ft_wr_len(tmp = set_zero(info->width - len), info);
		ft_strdel(&tmp);
		return ;
	}
	if (info->prec >= 0 && info->is_prec == 1 && info->prec < len)
		info->t_len = info->width - (len - (len - info->prec));
	else
		info->t_len = info->width - len;
	if (info->t_len <= 0)
		return ;
	ft_wr_len(tmp = fill_str(info->t_len, ' '), info);
	ft_strdel(&tmp);
}

void			conv_strings(char *str, t_info *info, int len)
{
	char s_prec[len - (len - info->prec) + 1];

	info->t_len = 0;
	if (info->width > 0 && info->extra[MINUS] != MINUS)
		get_padding(str, info);
	if (info->prec >= 0 && info->is_prec > 0 && info->prec < len && str != NULL)
		ft_wr_len(ft_strncpy(s_prec, str, len - (len - info->prec)), info);
	else if (str != NULL)
		ft_wr_inc(str, ft_strlen(str), info);
	else if (str == NULL)
	{
		if (info->prec >= 0 && info->is_prec > 0 && info->prec < len)
			ft_wr_len(ft_strncpy(s_prec, "(null)",
						len - (len - info->prec)), info);
		else
			ft_wr_inc("(null)", 6, info);
	}
	if (info->width > 0 && info->extra[MINUS] == MINUS)
		get_padding(str, info);
}

void			write_null(int c, t_info *info, int type)
{
	if (type == 0 && c == 0 && info->extra[MINUS] == MINUS)
		ft_wr_inc("\0", 1, info);
	else if (type == 1 && c == 0 && info->extra[MINUS] != MINUS)
		ft_wr_inc("\0", 1, info);
}

void			handle_zero(int c, char *str, t_info *info)
{
	char *tmp;

	write_null(c, info, 0);
	ft_wr_len(tmp = set_zero(info->width - 1), info);
	ft_strdel(&tmp);
	ft_wr_len(str, info);
	info->t_len++;
	write_null(c, info, 1);
	return ;
}

void			conv_char(int c, t_info *info)
{
	char	str[2];
	char	*tmp;

	info->prec = 0;
	str[0] = c;
	str[1] = '\0';
	info->is_prec = 0;
	info->t_len = 0;
	if ((info->flag == 0 || info->width > 0) && info->extra[ZERO] == ZERO)
		return (handle_zero(c, str, info));
	write_null(c, info, 0);
	if (info->width > 0 && info->extra[MINUS] != MINUS)
	{
		ft_wr_len((tmp = fill_str(info->width - 1, ' ')), info);
		ft_strdel(&tmp);
	}
	ft_wr_len(str, info);
	if (info->width > 0 && info->extra[MINUS] == MINUS)
	{
		ft_wr_len((tmp = fill_str(info->width - 1, ' ')), info);
		ft_strdel(&tmp);
	}
	write_null(c, info, 1);
}
