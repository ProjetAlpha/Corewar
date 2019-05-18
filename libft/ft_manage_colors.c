/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_colors.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/22 16:38:19 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 16:31:26 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*color_str(char color)
{
	if (color == 'r')
		return (ft_strdup("\033[0;31m"));
	if (color == 'g')
		return (ft_strdup("\033[0;32m"));
	if (color == 'y')
		return (ft_strdup("\033[0;33m"));
	if (color == 'b')
		return (ft_strdup("\033[0;34m"));
	if (color == 'm')
		return (ft_strdup("\033[0;35m"));
	if (color == 'c')
		return (ft_strdup("\033[0;36m"));
	if (color == 'R')
		return (ft_strdup("\033[1;31m"));
	if (color == 'G')
		return (ft_strdup("\033[1;32m"));
	if (color == 'Y')
		return (ft_strdup("\033[1;33m"));
	if (color == 'B')
		return (ft_strdup("\033[1;34m"));
	if (color == 'M')
		return (ft_strdup("\033[1;35m"));
	if (color == 'C')
		return (ft_strdup("\033[1;36m"));
	return (ft_strdup("\033[0m"));
}

char		*manage_colors(t_expr *curr)
{
	size_t	len;
	size_t	start;
	char	*new_expr;

	len = 0;
	start = 0;
	new_expr = ft_strnew(0);
	while (len <= curr->length - 2)
	{
		if (curr->expr[len] == '{' && curr->expr[len + 2] == '}' &&
			ft_strctn(COLORS, curr->expr[len + 1]))
		{
			new_expr = ft_strjoin_f(new_expr,
									ft_strsub(curr->expr, start, len - start));
			start = len + 3;
			new_expr = ft_strjoin_f(new_expr, color_str(curr->expr[len + 1]));
			curr->length += ft_strctn("Dd", curr->expr[len + 1]) ? 1 : 4;
		}
		len++;
	}
	new_expr = ft_strjoin_f(new_expr,
							ft_strsub(curr->expr, start, len - start));
	free(curr->expr);
	return (new_expr);
}
