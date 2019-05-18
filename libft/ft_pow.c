/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pow.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 09:53:29 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 10:02:35 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int n, unsigned int power)
{
	int res;

	res = n;
	if (power == 0)
		return (1);
	if (power == 1)
		return (n);
	return (n * ft_pow(n, power - 1));
}
