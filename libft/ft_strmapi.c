/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 14:06:01 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 14:32:17 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fs;

	i = 0;
	if (s && f)
	{
		if (!(fs = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (*s)
			*fs++ = f(i++, *s++);
		return (fs - i);
	}
	return (NULL);
}
