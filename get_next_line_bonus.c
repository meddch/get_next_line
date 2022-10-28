/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mechane <mechane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:55:04 by mechane           #+#    #+#             */
/*   Updated: 2022/10/28 15:13:45 by mechane          ###   ########.fr       */
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

	temp = NULL;
	ret = 1 ;
	while (ret > 0 && !ft_strchr(buff, '\n'))
	{	
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == 0)
			break ;
		buff[ret] = '\0';
		temp = ft_strjoin(stash[fd], buff);
		free(stash[fd]);
		stash[fd] = temp;
	}
	free (buff);
	return (stash[fd]);
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
	stash[fd] = ft_read(stash[fd], fd, buff);
	return (stash[fd]);
}

char	*get_next_line(int fd)
{
	static char	*stash[10240];
	char		*line;
	char		*temp;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
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
