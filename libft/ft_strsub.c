/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 14:50:42 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 18:59:09 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *fs;

	if (s)
	{
		if (!(fs = ft_strnew(len)))
			return (NULL);
		return (ft_strncpy(fs, s + start, len));
	}
	return (NULL);
}
