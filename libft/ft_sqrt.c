/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sqrt.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 10:04:53 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/29 11:26:24 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int n, int return_closest_sup)
{
	int sqrt;

	sqrt = 0;
	while ((sqrt * sqrt) < n && sqrt <= 46340)
		sqrt++;
	if ((sqrt * sqrt) == n || return_closest_sup)
		return (sqrt);
	return (0);
}
