/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_o.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 20:18:55 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:56:36 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void		get_padding(unsigned long n, t_info *info, int len)
{
	int		ret;
	char	*tmp;

	ret = 0;
	info->t_len = 0;
	if ((info->prec == 0 && info->is_prec == 1) &&
			n == 0 && info->extra[H_TAG] != H_TAG)
		len--;
	if (info->prec > 0 && info->is_prec != 0 && info->prec > len)
		info->t_len = info->width - ((info->prec - len) + len + ret);
	else if (info->width > len)
	{
		if (is_zero(info))
			return ;
		info->t_len = info->width - (len + ret);
	}
	if (info->t_len <= 0)
		return ;
	ft_wr_len(tmp = fill_str(info->t_len, ' '), info);
	ft_strdel(&tmp);
}

static void		set_prec(t_info *info, int len)
{
	int		diff;
	char	*tmp;

	diff = 0;
	if (info->prec > len)
	{
		if (info->prec >= 0 && info->is_prec > 0)
		{
			ft_wr_len(tmp = set_zero(info->prec - (len + diff)), info);
			ft_strdel(&tmp);
		}
	}
	else if (info->prec == 0 && info->is_prec == 0 && info->width > len
			&& info->extra[ZERO] == ZERO && info->extra[MINUS] != MINUS)
	{
		ft_wr_len(tmp = set_zero(info->width - (len + diff)), info);
		ft_strdel(&tmp);
	}
}

void			conv_o(t_info *info)
{
	int		i_len;
	char	*tmp;

	i_len = get_nbr_len(info, 8, 1);
	if (info->u_arg == 0)
		i_len++;
	if (info->extra[H_TAG] && info->u_arg != 0)
		i_len++;
	if (info->width > 0 && info->extra[MINUS] != MINUS && info->width >= i_len)
		get_padding(info->u_arg, info, i_len);
	if ((info->extra[H_TAG] == H_TAG && info->u_arg != 0) ||
			(info->extra[H_TAG] && info->prec == 0 && info->is_prec == 1))
		ft_wr_inc("0", 1, info);
	set_prec(info, i_len);
	if (info->u_arg == 0 && !(info->is_prec > 0 && info->prec == 0))
		ft_wr_inc("0", 1, info);
	if (info->u_arg != 0)
	{
		ft_wr_len(tmp = conv_ubase(info, 8, i_len), info);
		free(tmp);
	}
	if (info->width > 0 && info->extra[MINUS] == MINUS)
		get_padding(info->u_arg, info, i_len);
}
