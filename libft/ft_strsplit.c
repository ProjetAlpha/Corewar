/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 18:08:59 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 10:48:54 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countw(char const *s, char c)
{
	unsigned int wc;

	wc = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		if (*s && *s != c)
		{
			wc++;
			while (*s && *s != c)
				s++;
		}
	}
	return (wc);
}

static int	ft_wlen(char const *s, char c)
{
	unsigned int wl;

	wl = 0;
	while (*s && *s++ != c)
		wl++;
	return (wl);
}

char		**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	i;

	if (s)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (ft_countw(s, c) + 1))))
			return (NULL);
		i = 0;
		while (*s)
		{
			if (*s == c)
				s++;
			if (*s && *s != c)
			{
				if (!(tab[i++] = ft_strsub(s, 0, ft_wlen(s, c))))
					return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
