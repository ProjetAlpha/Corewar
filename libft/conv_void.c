/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_void.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 17:04:30 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:58:05 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		get_padding(char *str, t_info *info)
{
	int		ret;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	info->t_len = 0;
	ret = 0;
	ret += 2;
	if (len == 0 && info->is_prec == 0)
		len++;
	if (info->prec > 0 && info->is_prec != 0 && info->prec > len)
		info->t_len = info->width - ((info->prec - len) + len + ret);
	else if (info->width > len)
	{
		if (info->extra[ZERO] == ZERO && info->prec == 0 && info->is_prec == 0)
			return ;
		info->t_len = info->width - (len + ret);
	}
	if (info->t_len <= 0)
		return ;
	ft_wr_len(tmp = fill_str(info->t_len, ' '), info);
	ft_strdel(&tmp);
}

static void		set_prec(t_info *info, char *str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	if (info->prec > len)
	{
		if (info->prec >= 0 && info->is_prec > 0)
		{
			ft_wr_len(tmp = set_zero(info->prec - len), info);
			ft_strdel(&tmp);
		}
	}
	else if (is_zero(info) && info->width > len)
	{
		ft_wr_len(tmp = set_zero(info->width - (len + 2)), info);
		ft_strdel(&tmp);
	}
}

void			conv_void(unsigned long int n, t_info *info)
{
	char	*str;
	int		len;

	info->u_arg = n;
	str = conv_ubase(info, 16, get_nbr_len(info, 16, 1));
	len = ft_strlen(str);
	if (info->width > 0 && info->extra[MINUS] == 0 && info->width > len)
		get_padding(str, info);
	ft_wr_inc("0x", 2, info);
	set_prec(info, str);
	if (len == 0 && info->is_prec == 0)
		ft_wr_inc("0", 1, info);
	else
		ft_wr_inc(str, ft_strlen(str), info);
	if (info->width > 0 && info->extra[MINUS] > 0)
		get_padding(str, info);
	ft_strdel(&str);
}
