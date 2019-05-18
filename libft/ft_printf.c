/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 17:04:39 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 21:09:44 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf(const char *str, ...)
{
	t_info		*info;
	va_list		va;

	info = ft_init_lst();
	va_start(va, str);
	return (parse_str((char*)str, info, va));
}
