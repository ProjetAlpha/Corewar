/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_digit.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 16:40:21 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:57:33 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	conv_uint(unsigned long input, t_info *info)
{
	info->u_arg = input;
	conv_ulength(info);
	if (info->flag == X || info->flag == LX)
		conv_hexa(info);
	if (info->flag == O || info->flag == LO)
		conv_o(info);
	if (info->flag == U || info->flag == LU || info->flag == LD)
		conv_un(info);
}

void	conv_int(long long int input, t_info *info)
{
	info->i_arg = input;
	conv_length(info);
	conv_basic(info);
}

char	*conv_flags(t_info *info, va_list args)
{
	char	*str;
	int		len;

	len = 0;
	if (info->flag == D || info->flag == LD || info->flag == I)
		conv_int(va_arg(args, long long int), info);
	else if (info->flag == LX || info->flag == LU || info->flag == U
			|| info->flag == X || info->flag == O || info->flag == LO
			|| info->length == Z || info->length == LL || info->length == J)
		conv_uint(va_arg(args, unsigned long int), info);
	else if (info->flag == LS || info->flag == S)
	{
		str = va_arg(args, char *);
		len = (str == NULL) ? 6 : ft_strlen(str);
		conv_strings(str, info, len);
	}
	else if (info->flag == C || info->flag == LC)
		conv_char(va_arg(args, int), info);
	else if (info->flag == P)
		conv_void((unsigned long int)va_arg(args, void *), info);
	else if (info->flag == F || info->flag == LF)
		return (NULL);
	return (NULL);
}
