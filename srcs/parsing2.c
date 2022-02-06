/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:26:45 by suylee            #+#    #+#             */
/*   Updated: 2021/05/14 12:56:24 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_res(t_all *all, char *line)
{
	int i;

	i = 0;
	ft_ifspace(line, &i);
	all->info.res.x = ft_atoi(&line[++i]);
	i++;
	while (ft_isdigit(line[i]))
		i++;
	all->info.res.y = ft_atoi(&line[i++]);
	if (all->info.res.x <= 0 || all->info.res.y <= 0)
	{
		printf("Error\nres\n");
		ft_exit(all);
	}
	while (ft_isdigit(line[i]))
		i++;
	ft_ifspace(line, &i);
	if (line[i])
	{
		printf("Error\nincorrect res\n");
		ft_exit(all);
	}
}

char	*ft_dirtex(t_all *all, char *line)
{
	int		i;
	char	**s;
	char	*atex;

	if (!(s = ft_split(line, ' ')))
	{
		printf("Error\nmalloc split in ft_dirtex\n");
		ft_exit(all);
	}
	if (!(atex = ft_strdup(s[1])))
	{
		printf("Error\nmalloc str in ft_dirtex\n");
		ft_exit(all);
	}
	if (s[2])
	{
		printf("Error\ntexture info isn't correct\n");
		ft_exit(all);
	}
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s[i]);
	free(s);
	return (atex);
}

void	ft_colnumj(char *line, int *i, int *j)
{
	if (ft_isdigit(line[*i]))
		(*j)++;
	if (ft_atoi(&line[*i]) < 0 || ft_atoi(&line[*i]) > 255)
		(*j)--;
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*j)++;
}

void	ft_colcheck(t_all *all, char *line, int i)
{
	int j;

	j = 0;
	ft_colnumj(line, &i, &j);
	i++;
	ft_colnumj(line, &i, &j);
	i++;
	ft_colnumj(line, &i, &j);
	if (line[i] == ',')
		j--;
	ft_ifspace(line, &i);
	if (line[i] != '\0')
		j--;
	if (j != 5)
	{
		printf("Error\nFCcolor\n");
		ft_exit(all);
	}
}

int		ft_col(char *line, t_all *all)
{
	int				i;
	unsigned int	color;

	i = 0;
	ft_ifspace(line, &i);
	i++;
	ft_ifspace(line, &i);
	ft_colcheck(all, line, i);
	color = ft_atoi(&line[i]) * 256 * 256;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]) * 256;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]);
	return (color);
}
