/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_padding.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/23 16:45:56 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:56:40 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		is_valid(char c)
{
	if (is_extra_c(c) || is_flag(c) ||
			ft_isdigit(c) || is_len_modif(c) || c == '.')
		return (1);
	return (0);
}

int		is_zero(t_info *info)
{
	if (info->extra[ZERO] == ZERO && info->extra[MINUS] != MINUS &&
			info->prec == 0 && info->is_prec == 0)
		return (1);
	return (0);
}

char	*set_zero(int n)
{
	char	*dest;
	int		i;

	i = 0;
	if (n <= 0)
		return (NULL);
	if (!(dest = malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (n-- != 0)
		dest[i++] = '0';
	dest[i] = '\0';
	return (dest);
}
