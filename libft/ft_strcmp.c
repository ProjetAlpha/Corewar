/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 12:28:04 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 17:05:38 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/*int get_null_byte(int byte)
{
    if (!(byte & 0xff))
        return (1);
    if (!((byte >> 8) & 0xff))
        return (2);
    if (!((byte >> 16) & 0xff))
        return (3);
    if (!((byte >> 24) & 0xff))
        return (4);
    return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	int *s1_conv = (int *)s1;
    int *s2_conv = (int *)s2;
	int null_byte = 0;
	while (*s1_conv == *s2_conv)
	{
	    if ((null_byte = get_null_byte(*s1_conv)) != 0)
           break;
	    s1_conv++;
	    s2_conv++;
	}
	return (s2_conv - s1_conv < 0 ? -1 : s1_conv - s2_conv);
}
}*/
