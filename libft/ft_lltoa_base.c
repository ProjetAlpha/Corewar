/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lltoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 11:45:53 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 12:40:40 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_str_len(long int n, int base)
{
	unsigned int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

static char		*ft_stringzero(void)
{
	char *strzero;

	if (!(strzero = ft_strnew(1)))
		return (NULL);
	*strzero = '0';
	return (strzero);
}

t_bool			ft_lltoa_base(char **str, long int n, int base)
{
	t_bool	neg;
	int		index;

	neg = FALSE;
	index = 0;
	if (n == 0)
	{
		*str = ft_stringzero();
		return (FALSE);
	}
	if (n < 0 && base == 10)
	{
		neg = TRUE;
		n = -n;
	}
	index = calc_str_len(n, base);
	if (!(*str = ft_strnew(index)))
		return (FALSE);
	while (index-- && n > 0)
	{
		*(*str + index) = n % base > 9 ? (n % base - 10) + 'A' : n % base + '0';
		n /= base;
	}
	return (neg);
}
