/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:55:04 by mechane           #+#    #+#             */
/*   Updated: 2022/10/28 15:46:33 by mechane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

size_t	strlen_nw(const char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_read(char *stash, int fd, char *buff)
{
	char	*temp;
	int		ret;

	ret = 1 ;
	while (ret > 0 && !ft_strchr(buff, '\n'))
	{	
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == 0)
			break ;
		buff[ret] = '\0';
		temp = ft_strjoin(stash, buff);
		free(stash);
		stash = temp;
	}
	free (buff);
	return (stash);
}

char	*get_stash(char *stash, int fd)
{
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
	{
		free(buff);
		return (NULL);
	}
	buff[0] = 0;
	stash = ft_read(stash, fd, buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[10241];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	stash[fd] = get_stash(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	if (!*stash[fd])
	{	
		free(stash[fd]);
		return (stash[fd] = 0);
	}
	line = ft_substr(stash[fd], 0, strlen_nw(stash[fd]) + 1);
	temp = ft_substr(stash[fd], strlen_nw(stash[fd]) + 1,
			ft_strlen(stash[fd] + strlen_nw(stash[fd]) + 1));
	free(stash[fd]);
	stash[fd] = temp ;
	return (line);
}
