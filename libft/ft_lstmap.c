/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 13:24:12 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 12:17:19 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlist;
	t_list *new;
	t_list *current;

	if (!lst || !f)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		new = f(lst);
		if (!newlist)
			newlist = new;
		else
			current->next = new;
		current = new;
		lst = lst->next;
	}
	return (newlist);
}
