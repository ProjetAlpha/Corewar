/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 19:48:44 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 18:46:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int i;
	int a;
	int return_length;

	a = 0;
	i = 0;
	while (dst[i] != '\0')
		i++;
	while (src[a] != '\0')
		a++;
	return_length = (int)size < i ? a + (int)size : i + a;
	a = -1;
	while (src[++a] != '\0' && a + i < (int)size - 1)
		dst[i + a] = src[a];
	dst[i + a] = '\0';
	return (return_length);
}
