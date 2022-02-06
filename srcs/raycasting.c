/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:28:25 by suylee            #+#    #+#             */
/*   Updated: 2021/05/11 17:53:37 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_algo(t_all *all)
{
	while (1)
	{
		if (all->algo.sided.x < all->algo.sided.y)
		{
			all->algo.sided.x += all->algo.delta.x;
			all->algo.map.x += all->algo.step.x;
			all->algo.side = 0;
		}
		else
		{
			all->algo.sided.y += all->algo.delta.y;
			all->algo.map.y += all->algo.step.y;
			all->algo.side = 1;
		}
		if (all->info.bufmap[all->algo.map.x +
				(all->algo.map.y * all->info.maplen.x)] == '1')
			break ;
	}
	if (all->algo.side == 0)
		all->algo.pdist = (all->algo.map.x - all->algo.raypos.x
				+ (1 - all->algo.step.x) / 2) / all->algo.raydir.x;
	else
		all->algo.pdist = (all->algo.map.y - all->algo.raypos.y
				+ (1 - all->algo.step.y) / 2) / all->algo.raydir.y;
	all->algo.lineh = (all->info.res.y / all->algo.pdist);
}

void	ft_initalgo(t_all *all)
{
	if (all->algo.raydir.x < 0)
	{
		all->algo.step.x = -1;
		all->algo.sided.x = (all->algo.raypos.x
			- all->algo.map.x) * all->algo.delta.x;
	}
	else
	{
		all->algo.step.x = 1;
		all->algo.sided.x = (all->algo.map.x + 1.0
			- all->algo.raypos.x) * all->algo.delta.x;
	}
	if (all->algo.raydir.y < 0)
	{
		all->algo.step.y = -1;
		all->algo.sided.y = (all->algo.raypos.y
			- all->algo.map.y) * all->algo.delta.y;
	}
	else
	{
		all->algo.step.y = 1;
		all->algo.sided.y = (all->algo.map.y + 1.0
			- all->algo.raypos.y) * all->algo.delta.y;
	}
}

void	ft_initray(t_all *all, int x)
{
	all->algo.camx = 2 * x / (double)all->info.res.x - 1;
	all->algo.raypos = (t_dcoor){all->cam.pos.x, all->cam.pos.y};
	all->algo.raydir.x = all->cam.dir.x + all->cam.plane.x * all->algo.camx;
	all->algo.raydir.y = all->cam.dir.y + all->cam.plane.y * all->algo.camx;
	all->algo.map = (t_coor){(all->algo.raypos.x), (all->algo.raypos.y)};
	all->algo.delta.x = fabs(1 / all->algo.raydir.x);
	all->algo.delta.y = fabs(1 / all->algo.raydir.y);
	ft_initalgo(all);
	ft_algo(all);
	all->algo.drawstart = (-all->algo.lineh / 2 + all->info.res.y / 2);
	all->algo.drawend = (all->algo.lineh / 2 + all->info.res.y / 2);
	if (all->algo.drawstart < 0)
		all->algo.drawstart = 0;
	if (all->algo.drawend >= all->info.res.y)
		all->algo.drawend = all->info.res.y - 1;
}

void	ft_reycasting(t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x < all->info.res.x)
	{
		ft_initray(all, x);
		ft_drawall(all, x);
		y = all->algo.drawend;
		while (y < all->info.res.y)
		{
			all->mlx.get_data[x + y *
				(all->mlx.size_l / 4)] = all->info.f;
			all->mlx.get_data[x + (all->info.res.y - y - 1)
				* (all->mlx.size_l / 4)] = all->info.c;
			y++;
		}
		all->spr.distwall[x] = all->algo.pdist;
		x++;
	}
}
