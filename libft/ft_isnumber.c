/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isnumber.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kev.grosjean@gmail.com>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 13:08:24 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 13:09:07 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isnumber(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (FALSE);
		line++;
	}
	return (TRUE);
}
