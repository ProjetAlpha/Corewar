/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_hex.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 20:38:59 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:57:20 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static	void	get_padding(unsigned long int n, t_info *info, int len)
{
	int		ret;
	char	*tmp;

	ret = 0;
	info->t_len = 0;
	if ((info->prec == 0 && info->is_prec == 1) && n == 0)
		len--;
	if (info->extra[H_TAG] == H_TAG && info->u_arg != 0 && info->prec != 0)
		ret += 2;
	if (info->prec > 0 && info->is_prec != 0 && info->prec > len)
		info->t_len = info->width - ((info->prec - len) + len + ret);
	else if (info->width > len)
	{
		if (is_zero(info))
			return ;
		info->t_len = info->width - (len);
	}
	if (info->t_len == 0)
		return ;
	ft_wr_len(tmp = fill_str(info->t_len, ' '), info);
	ft_strdel(&tmp);
}

static	void	set_prec(unsigned long int n, t_info *info, int len)
{
	int		diff;
	char	*tmp;

	diff = 0;
	if (info->extra[H_TAG] == H_TAG && n != 0 && info->prec >= 0
			&& info->is_prec > 0)
		len -= 2;
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

void			conv_hexa(t_info *info)
{
	int		i_len;
	char	*tmp;

	i_len = get_nbr_len(info, 16, 1);
	if (info->u_arg == 0)
		i_len++;
	if (info->extra[H_TAG] == H_TAG && info->u_arg != 0)
		i_len += 2;
	if (info->width > 0 && info->extra[MINUS] != MINUS && info->width >= i_len)
		get_padding(info->u_arg, info, i_len);
	if (info->extra[H_TAG] && info->u_arg != 0 && info->flag == X)
		ft_wr_inc("0x", 2, info);
	if (info->extra[H_TAG] && info->u_arg != 0 && info->flag == LX)
		ft_wr_inc("0X", 2, info);
	set_prec(info->u_arg, info, i_len);
	if (info->u_arg == 0 && !(info->is_prec > 0 && info->prec == 0))
		ft_wr_inc("0", 1, info);
	if (info->u_arg != 0)
	{
		ft_wr_len(tmp = conv_ubase(info, 16, i_len), info);
		free(tmp);
	}
	if (info->width > 0 && info->extra[MINUS] == MINUS)
		get_padding(info->u_arg, info, i_len);
}
