/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isalnum.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 13:58:47 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 13:59:58 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c, char type)
{
	if (type == 'l')
		return (ft_isdigit(c) || ft_islower(c));
	if (type == 'u')
		return (ft_isdigit(c) || ft_isupper(c));
	return (ft_isalpha(c) || ft_isdigit(c));
}
