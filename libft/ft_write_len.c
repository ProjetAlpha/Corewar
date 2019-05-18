/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wr_len.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 16:29:46 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:47:10 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_wr_len(char *str, t_info *info)
{
	int len;

	len = 0;
	if (str != NULL && info != NULL)
	{
		len = ft_strlen(str);
		if (len > 0)
		{
			write(1, str, len);
			info->c_len += len;
		}
	}
}
