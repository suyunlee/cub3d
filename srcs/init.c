/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:17:48 by suylee            #+#    #+#             */
/*   Updated: 2021/05/17 12:37:46 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initmlx(t_all *all)
{
	if (!(all->mlx.imgptr = mlx_new_image(all->mlx.ptr,
		all->info.res.x, all->info.res.y)))
	{
		printf("Error\nmlx_new_image");
		ft_exit(all);
	}
	if (!(all->mlx.get_data = (int *)mlx_get_data_addr(all->mlx.imgptr,
		&all->mlx.bpp, &all->mlx.size_l, &all->mlx.endian)))
	{
		printf("Error\nmlx_get_data_addr");
		ft_exit(all);
	}
}

void	initwin(t_all *all, char **argv)
{
	if ((all->cam.isit != 1))
	{
		printf("Error\nplayer num\n");
		ft_exit(all);
	}
	if (!(all->mlx.ptr = mlx_init()))
	{
		printf("Error\nmlx_init\n");
		ft_exit(all);
	}
	ft_sprites(all);
	ft_textures(all);
	if (argv[2] && !ft_strncmp(argv[2], "--save", 10))
		ft_bmpinit(all);
	else if (argv[2])
	{
		printf("Error\nyou're second argument isn't --save");
		ft_exit(all);
	}
	if (!(all->mlx.winptr = mlx_new_window(all->mlx.ptr,
			all->info.res.x, all->info.res.y, "cub3D")))
	{
		printf("Error\nmlx_init");
		ft_exit(all);
	}
}

void	ft_refresh(t_all *all)
{
	initmlx(all);
	if (!(all->spr.distwall = ft_calloc(sizeof(double*), all->info.res.x)))
	{
		printf("Error\nmalloc all->spr.distwall\n");
		ft_exit(all);
	}
	ft_reycasting(all);
	init_sprites(all);
	mlx_put_image_to_window(all->mlx.ptr,
		all->mlx.winptr, all->mlx.imgptr, 0, 0);
	mlx_destroy_image(all->mlx.ptr, all->mlx.imgptr);
}

void	maxscreen(t_all *all)
{
	int	screensize;

	screensize = mlx_get_screen_size(all->mlx.ptr,
			&all->info.sx, &all->info.sy);
	if (all->info.res.x > all->info.sx)
		all->info.res.x = all->info.sx;
	else if (all->info.res.x < 100)
		all->info.res.x = 100;
	if (all->info.res.y > all->info.sy)
		all->info.res.y = all->info.sy;
	else if (all->info.res.y < 100)
		all->info.res.y = 100;
}

void	initall(t_all *all, char **argv)
{
	ft_memset(all, 0, sizeof(t_all));
	all->cam.movespeed = 0.05;
	all->cam.rotspeed = 0.05;
	ft_parsing(argv, all);
	if (!(all->info.test[(int)'N'] == 1 && all->info.test[(int)'U']
			== 1 && all->info.test[(int)'W'] == 1 && all->info.test[(int)'E']
			== 1 && all->info.test[(int)'S'] == 1 && all->info.test[(int)'F']
			== 1 && all->info.test[(int)'C'] == 1 && all->info.test[(int)'R']
			== 1))
	{
		printf("Error\nnot enough map list\n");
		ft_exit(all);
	}
	verify_map(all);
	maxscreen(all);
	initwin(all, argv);
	ft_refresh(all);
}
