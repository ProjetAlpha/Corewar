/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:27:35 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 11:51:21 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

int get_null_byte(unsigned long int byte)
{
    if (!(byte & 0xff))
        return (1);
    if (!((byte >> 8) & 0xff))
        return (2);
    if (!((byte >> 16) & 0xff))
        return (3);
    if (!((byte >> 24) & 0xff))
        return (4);
	if (!((byte >> 32) & 0xff))
		return (5);
	if (!((byte >> 40) & 0xff))
		return (5);
	if (!((byte >> 48) & 0xff))
		return (6);
	if (!((byte >> 56) & 0xff))
		return (7);
    return (0);
}

size_t 		ft_strlen2(const char *s)
{
	unsigned long int *conv_str;
    int null_byte;

	conv_str = (unsigned long int*)s;
	while (conv_str)
	{
		if ((null_byte = get_null_byte(*conv_str)) != 0)
			return ((const char *)conv_str - s + (null_byte - 1));
		conv_str++;
	}
	return (0);
}
