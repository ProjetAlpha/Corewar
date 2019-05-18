/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 20:18:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/12 14:00:57 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_int_l(long n)
{
	unsigned int	l;

	l = 0;
	while (n > 0)
	{
		l++;
		n /= 10;
	}
	return (l);
}

static char			*ft_stringzero(void)
{
	char *strzero;

	if (!(strzero = ft_strnew(1)))
		return (NULL);
	*strzero = '0';
	return (strzero);
}

char				*ft_itoa(int n)
{
	char			*s;
	unsigned int	l;
	long			tmp;

	l = 0;
	tmp = (long)n;
	if (tmp == 0)
		return (ft_stringzero());
	if (tmp < 0)
	{
		l++;
		tmp = -tmp;
	}
	l += get_int_l(tmp);
	if (!(s = ft_strnew(l)))
		return (NULL);
	while (l-- && tmp > 0)
	{
		*(s + l) = (char)(tmp % 10) + '0';
		tmp = tmp / 10;
	}
	if (n < 0)
		*s = '-';
	return (s);
}
