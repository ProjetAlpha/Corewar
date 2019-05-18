/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nblen.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 12:22:28 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 11:18:19 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nblen(long long int nb)
{
	size_t len;

	len = 1;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while ((nb / 10) > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
