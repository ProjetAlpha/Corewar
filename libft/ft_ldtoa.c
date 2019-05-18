/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ldtoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 11:45:35 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:39:10 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_round(long double nbr, size_t i, t_format *format)
{
	long double tmp;

	tmp = nbr;
	while (i <= (format->point ? format->precision : 6))
	{
		if (i == (format->point ? format->precision : 6) &&
			(unsigned long long)(tmp * 10) % 10 >= 5)
			return ((((int)nbr) == 9) ? 0 : (int)nbr + 1);
		else if ((unsigned long long)(tmp * 10) % 10 == 9)
			tmp *= 10;
		else
			return ((int)nbr);
		i++;
	}
	return ((((int)nbr) == 9) ? 0 : (int)nbr + 1);
}

static char	*set_rest(long double nbr, t_format *format)
{
	char	*rest;
	size_t	i;

	i = 0;
	rest = ft_strnew(0);
	while (i < (format->point ? format->precision : 6))
	{
		nbr -= (unsigned long long)nbr;
		nbr *= 10;
		i++;
		rest = ft_strjoin_f(rest, ft_itoa(ft_round(nbr, i, format)));
	}
	return (rest);
}

char		*ft_ldtoa(long double nbr, t_format *format)
{
	char	*str;
	char	*rest;

	str = NULL;
	rest = ft_strnew(0);
	nbr = nbr < 0 ? -nbr : nbr;
	if (format->point && !format->precision)
		ft_ulltoa_base(&str, ((unsigned long long)(nbr * 10) % 10 >= 5) ?
			(unsigned long long)nbr + 1 : (unsigned long long)nbr, 10);
	else
	{
		rest = ft_strjoin_f(rest, set_rest(nbr, format));
		if (rest[0] == '0' && (unsigned long long)(nbr * 10) % 10 >= 5)
			ft_ulltoa_base(&str, (unsigned long long)nbr + 1, 10);
		else
			ft_ulltoa_base(&str, (unsigned long long)nbr, 10);
		str = ft_strjoin_f(str, ft_strdup("."));
		str = ft_strjoin_f(str, rest);
	}
	return (str);
}
