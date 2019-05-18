/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_un.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 20:02:19 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:57:02 by thbrouss    ###    #+. /#+    ###.fr     */
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
	if (info->extra[SPACE] == SPACE && info->extra[PLUS] != PLUS && n > 0)
		ret++;
	if (info->extra[PLUS] == PLUS && n > 0)
		ret++;
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

static	void	set_prec(unsigned long int n, t_info *info, int len)
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
		if (info->extra[SPACE] == SPACE && info->extra[PLUS] != PLUS && n > 0)
			diff++;
		if (info->extra[PLUS] == PLUS && n > 0)
			diff++;
		ft_wr_len(tmp = set_zero(info->width - (len + diff)), info);
		ft_strdel(&tmp);
	}
}

void			conv_un(t_info *info)
{
	int		i_len;
	char	*tmp;

	i_len = get_nbr_len(info, 10, 1);
	if (info->u_arg == 0)
		i_len++;
	if (info->extra[SPACE] == SPACE && info->extra[PLUS] != PLUS &&
			!(info->flag == U || info->flag == LU))
		ft_wr_inc(" ", 1, info);
	if (info->width > 0 && info->extra[MINUS] != MINUS && info->width >= i_len)
		get_padding(info->u_arg, info, i_len);
	if (info->extra[PLUS] == PLUS && info->u_arg > 0
			&& !(info->flag == U || info->flag == LU))
		ft_wr_inc("+", 1, info);
	set_prec(info->u_arg, info, i_len);
	if (info->u_arg == 0 && !(info->is_prec > 0 && info->prec == 0))
		ft_wr_inc("0", 1, info);
	if (info->u_arg != 0)
	{
		ft_wr_len(tmp = conv_ubase(info, 10, i_len), info);
		free(tmp);
	}
	if (info->width > 0 && info->extra[MINUS] == MINUS)
		get_padding(info->u_arg, info, i_len);
}
