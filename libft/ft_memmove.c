/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 14:05:31 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 13:15:41 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if (src > dst)
	{
		i = 0;
		while (++i <= len)
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
	}
	if (dst > src)
	{
		i = len + 1;
		while (--i > 0)
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
	}
	return (dst);
}
