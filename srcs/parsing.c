/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:22:48 by suylee            #+#    #+#             */
/*   Updated: 2021/05/14 16:39:57 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(t_all *all)
{
	printf("Error\nmalloc ft_bufmap\n");
	ft_exit(all);
}

void	ft_bufmap(t_all *all, char *line)
{
	char	*newline;

	if ((newline = ft_strtrim(line, " ")))
	{
		newline = ft_suprspace(newline);
		if (all->info.maplen.y == 0)
		{
			all->info.maplen.x = ft_strlen(newline);
			all->info.bufmap = ft_strdup(newline);
		}
		else
		{
			if (all->info.maplen.x != (int)ft_strlen(newline))
			{
				printf("Error\nlen line\n");
				ft_exit(all);
			}
			all->info.bufmap = ft_strjoinfr(all->info.bufmap, newline, 1);
		}
	}
	if (!newline || !all->info.bufmap)
		ft_error(all);
	ft_strdel(&newline);
	all->info.maplen.y += 1;
}

void	ft_firstcheck(t_all *all, char c, char d)
{
	if (c == 'S' && d == 'O')
		c = 'U';
	if (all->info.test[(int)c] == 0)
		all->info.test[(int)c] += 1;
	else if (c && c != '1')
	{
		printf("Error\n map double RNSWESFC\n");
		ft_exit(all);
	}
	if (c == '1')
	{
		if (!(all->info.test[(int)'N'] == 1 && all->info.test[(int)'U']
			== 1 && all->info.test[(int)'W'] == 1 && all->info.test[(int)'E']
			== 1 && all->info.test[(int)'S'] == 1 && all->info.test[(int)('F')]
			== 1 && all->info.test[(int)'C'] == 1 && all->info.test[(int)'R']))
		{
			printf("Error\nmap parameter\n");
			ft_exit(all);
		}
	}
	if (c != '1' && c != '0' && (all->info.test[(int)'1'] == 1))
	{
		printf("Error\nmap : incorrect line\n");
		ft_exit(all);
	}
}

void	ft_parsing_line(t_all *all, char *line, int i)
{
	ft_ifspace(line, &i);
	ft_firstcheck(all, line[i], line[i + 1]);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(all, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->info.n = ft_dirtex(all, line);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->info.s = ft_dirtex(all, line);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		all->info.w = ft_dirtex(all, line);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		all->info.e = ft_dirtex(all, line);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		all->info.i = ft_dirtex(all, line);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		all->info.f = ft_col(line, all);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		all->info.c = ft_col(line, all);
	else if (line[i] == '1' || line[i] == '0')
		ft_bufmap(all, line);
	else if (line[i] && line != (void *)0)
	{
		printf("Error\nincorrect map parameter\n");
		ft_exit(all);
	}
}

void	ft_parsing(char **argv, t_all *all)
{
	int		ret;
	char	*line;
	int		fd;
	int		i;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error\nFD");
		ft_exit(all);
	}
	line = NULL;
	ret = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		i = 0;
		ft_parsing_line(all, line, i);
		ft_strdel(&line);
	}
	if (ret == -1)
	{
		printf("Error\ngnl\n");
		ft_exit(all);
	}
	ft_strdel(&line);
	close(fd);
}
