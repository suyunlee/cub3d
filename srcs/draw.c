/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:14:05 by suylee            #+#    #+#             */
/*   Updated: 2021/05/14 15:33:32 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture	ft_mettretexture(t_all *all)
{
	if (all->algo.raydir.x > 0)
	{
		if (all->algo.side)
		{
			if (all->algo.raydir.y < 0)
				return (all->textures);
			return (all->texturen);
		}
		return (all->texturew);
	}
	else
	{
		if (all->algo.side)
		{
			if (all->algo.raydir.y < 0)
				return (all->textures);
			return (all->texturen);
		}
		return (all->texturee);
	}
}

void		ft_drawall(t_all *all, int x)
{
	double		wallx;
	int			texx;
	int			texy;
	t_texture	img;

	img = ft_mettretexture(all);
	if (all->algo.side == 1)
		wallx = all->algo.raypos.x + all->algo.pdist * all->algo.raydir.x;
	else
		wallx = all->algo.raypos.y + all->algo.pdist * all->algo.raydir.y;
	wallx -= floor(wallx);
	texx = wallx * (double)img.w;
	while (all->algo.drawstart < all->algo.drawend)
	{
		texy = (all->algo.drawstart - all->info.res.y / 2 +
				all->algo.lineh / 2) * img.h / all->algo.lineh;
		all->mlx.get_data[x + (int)all->algo.drawstart
			* (all->mlx.size_l / 4)] = img.data[texx + texy * img.w];
		all->algo.drawstart++;
	}
}
