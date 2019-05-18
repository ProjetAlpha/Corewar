/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_helper.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 14:53:31 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:56:53 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		is_extra_c(char c)
{
	return (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ');
}

int		is_len_modif(char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z');
}

int		is_empty(int *extra)
{
	int i;

	i = 0;
	while (i <= 7)
	{
		if (extra[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int		is_extra(int *extra, int id)
{
	int i;

	i = 0;
	while (extra[i])
	{
		if (extra[i] == id)
			return (1);
		i++;
	}
	return (0);
}

int		is_flag(char c)
{
	int i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == c)
			return (1);
		i++;
	}
	return (0);
}
