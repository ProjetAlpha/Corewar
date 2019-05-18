/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 16:17:59 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 10:20:15 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*fs;
	size_t	l;
	size_t	i;

	if (s)
	{
		l = 0;
		while (*s && ft_isspace(*s))
			s++;
		while (*s && *(s + l))
			l++;
		while (*s && *(s + (l - 1)) && ft_isspace(*(s + (l - 1))))
			l--;
		if (!(fs = ft_strnew(l)))
			return (NULL);
		i = 0;
		while (i < l)
		{
			*(fs + i) = *(s + i);
			i++;
		}
		return (fs);
	}
	return (NULL);
}
