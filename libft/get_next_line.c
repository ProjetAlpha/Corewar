/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 17:58:22 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 20:25:48 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		cut_l(char **dest, char **line, int begin, int fd)
{
	int		end;
	char	*tmp;

	end = ft_strlen(dest[fd]);
	if (begin == end)
	{
		*line = ft_strdup(dest[fd]);
		tmp = dest[fd];
		dest[fd] = ft_strsub(tmp, begin, end);
		free(tmp);
	}
	else
	{
		*line = ft_strsub(dest[fd], 0, begin);
		tmp = dest[fd];
		dest[fd] = ft_strsub(tmp, begin + 1, end);
		free(tmp);
	}
	return (1);
}

int		save_line(char **line, int fd, char **dest)
{
	int begin;

	begin = 0;
	while (dest[fd][begin] && dest[fd][begin] != '\n')
		begin++;
	return (cut_l(dest, line, begin, fd));
}

int		get_next_line(const int fd, char **line)
{
	int			bytes;
	static char	*dest[1024] = {0};
	char		*tmp;
	char		buff[BUFF_SIZE + 1];

	tmp = NULL;
	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL || read(fd, buff, 0) == -1)
		return (-1);
	if (!dest[fd])
		dest[fd] = ft_strnew(0);
	if (ft_strchr(dest[fd], '\n') != NULL)
		return (save_line(line, fd, dest));
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		tmp = dest[fd];
		dest[fd] = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(dest[fd], '\n'))
			return (save_line(line, fd, dest));
	}
	if (ft_strlen(dest[fd]) > 0 && bytes == 0)
		return (save_line(line, fd, dest));
	return (0);
}
