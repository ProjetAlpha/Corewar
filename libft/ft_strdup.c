/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:32:47 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 18:29:42 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	l;
	char	*scopy;

	if (*s1)
	{
		l = ft_strlen(s1);
		if (!(scopy = ft_strnew(l)))
			return (NULL);
		return (ft_strcpy(scopy, s1));
	}
	return (NULL);
}
