/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_char_belongs_to.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 13:11:37 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 13:13:18 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_char_belongs_to(const char *values, char c)
{
	if (ft_strctn(values, c))
		return (TRUE);
	return (FALSE);
}
