/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifymap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:34:41 by suylee            #+#    #+#             */
/*   Updated: 2021/05/17 10:58:47 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_checkones(t_all *all)
{
	int	x;
	int	y;

	x = -1;
	while (++x < all->info.maplen.x)
	{
		if (all->info.bufmap[x] != '1' || all->info.bufmap[x +
			(all->info.maplen.x * all->info.maplen.y)
			- all->info.maplen.x] != '1')
		{
			printf("Error map\nOnly '1' on the edges of your map");
			ft_exit(all);
		}
	}
	y = -1;
	while (++y < all->info.maplen.y)
	{
		if (all->info.bufmap[(y * all->info.maplen.x)] != '1'
			|| all->info.bufmap[(all->info.maplen.x +
			y * all->info.maplen.x) - 1] != '1')
		{
			printf("Error map\nOnly '1' on the edges of your map");
			ft_exit(all);
		}
	}
}

void	posdepart(t_all *all, int x, int y, char dir)
{
	all->cam.pos.x = x + 0.5;
	all->cam.pos.y = y + 0.5;
	if (dir == 'E')
		all->cam.dir = (t_dcoor){1, 0};
	else if (dir == 'S')
		all->cam.dir = (t_dcoor){0, 1};
	else if (dir == 'W')
		all->cam.dir = (t_dcoor){-1, 0};
	else
		all->cam.dir = (t_dcoor){0, -1};
	all->cam.plane.x = -0.66 * all->cam.dir.y;
	all->cam.plane.y = 0.66 * all->cam.dir.x;
	all->cam.isit++;
}

void	ft_checkline(char *line, int y, t_all *all)
{
	int	x;
	int	k;

	x = -1;
	while (++x < all->info.maplen.x)
	{
		k = x + (y * all->info.maplen.x);
		if (line[k] == 'N' || line[k] == 'S' ||
				line[k] == 'W' || line[k] == 'E')
			posdepart(all, x, y, line[k]);
		else if (line[k] == '2')
			all->spr.nbsp++;
		else if (line[k] != '1' && line[k] != '0')
		{
			printf("Error\nmap error : %d\n", line[k]);
			ft_exit(all);
		}
	}
}

void	verify_map(t_all *all)
{
	int	y;

	y = -1;
	while (++y < all->info.maplen.y)
		ft_checkline(all->info.bufmap, y, all);
	ft_checkones(all);
	if (!(all->sprites =
		(t_sprites*)ft_calloc(sizeof(t_sprites), all->spr.nbsp)))
	{
		printf("Error\nmalloc all->sprites\n");
		ft_exit(all);
	}
}
