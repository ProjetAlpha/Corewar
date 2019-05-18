/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 13:03:50 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 14:19:44 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*fs;
	unsigned int	i;

	if (s && f)
	{
		i = ft_strlen(s);
		if (!(fs = ft_strnew(i)))
			return (NULL);
		while (*s)
			*fs++ = f(*s++);
		return (fs - i);
	}
	return (NULL);
}
