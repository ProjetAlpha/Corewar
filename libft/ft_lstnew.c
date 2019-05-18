/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kev.grosjean@gmail.com>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 23:49:39 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 13:19:06 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;

	link = NULL;
	if (!(link = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(link->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(link->content, content, content_size);
		link->content_size = content_size;
	}
	else
	{
		link->content = NULL;
		link->content_size = 0;
	}
	link->next = NULL;
	return (link);
}
