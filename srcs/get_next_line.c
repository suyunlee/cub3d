/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:22:21 by suylee            #+#    #+#             */
/*   Updated: 2021/05/11 15:49:31 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_getnewline(char *backup)
{
	int	i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	gnl_fill(char **backup, char **line)
{
	int		cut;
	int		len;
	char	*tmp;

	cut = ft_getnewline(*backup);
	(*backup)[cut] = '\0';
	*line = ft_strdup(*backup);
	len = ft_strlen(*backup + cut + 1);
	if (len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	tmp = ft_strdup(*backup + cut + 1);
	free(*backup);
	*backup = tmp;
	return (1);
}

int	gnl_result(char **backup, char **line, int size, int fd)
{
	if (size < 0)
		return (-1);
	if (backup[fd] && ft_getnewline(backup[fd]) >= 0)
		return (gnl_fill(&backup[fd], line));
	if (backup[fd])
	{
		*line = backup[fd];
		backup[fd] = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*backup[OPEN_MAX];
	int			size;

	if (fd == -1 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size] = '\0';
		if (backup[fd] == NULL)
			backup[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(backup[fd], buf);
			free(backup[fd]);
			backup[fd] = tmp;
		}
		if (ft_getnewline(backup[fd]) >= 0)
			break ;
	}
	return (gnl_result(backup, line, size, fd));
}
