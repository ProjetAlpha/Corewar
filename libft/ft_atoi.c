/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:25:40 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/20 14:37:13 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	i;
	size_t			res;
	int				sign;

	i = 0;
	sign = 1;
	res = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+')
			sign = *(str++) == '-' ? -sign : sign;
		while (ft_isdigit(*str))
			res = 10 * res + (*(str++) - '0');
		return ((int)(sign * res));
	}
	return (0);
}
