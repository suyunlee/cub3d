/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:21:17 by suylee            #+#    #+#             */
/*   Updated: 2021/05/17 12:35:39 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_iscub(char *argv)
{
	int len;

	len = ft_strlen(argv);
	if (len - 4 < 0)
		len = 0;
	else
		len = len - 4;
	if ((ft_strncmp(argv + len, ".cub", 4)))
	{
		printf("Error\nInvalide map file : file extention isn't .cub");
		exit(0);
	}
}

int		ft_block(t_all *all)
{
	if (all->info.bufmap[(int)all->cam.pos.x
		+ ((int)all->cam.pos.y * all->info.maplen.x)] == '1' ||
		all->info.bufmap[(int)all->cam.pos.x
		+ ((int)all->cam.pos.y * all->info.maplen.x)] == '2')
		return (1);
	return (0);
}

int		ft_keys(t_all *all)
{
	double	tmp;

	tmp = all->cam.pos.x + all->cam.pos.y +
		all->cam.dir.x + all->cam.dir.y + all->cam.plane.x;
	if (all->key.key_w == 1 || all->key.key_s == 1)
		ft_moveup(all);
	if (all->key.key_a == 1 || all->key.key_d == 1)
		ft_moveside(all);
	if (all->key.key_r == 1 || all->key.key_l == 1)
		ft_moverot(all);
	if (tmp != (all->cam.pos.x + all->cam.pos.y
		+ all->cam.dir.x + all->cam.dir.y + all->cam.plane.x))
		ft_refresh(all);
	return (0);
}

int		game_exit(t_all *all)
{
	ft_exit(all);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 3)
	{
		printf("Error\nargc\n");
		ft_exit(&all);
	}
	ft_iscub(argv[1]);
	initall(&all, argv);
	mlx_hook(all.mlx.winptr, 2, (1L << 0), &key_press, &all);
	mlx_hook(all.mlx.winptr, 3, (1L << 1), &key_release, &all);
	mlx_hook(all.mlx.winptr, 17, 0, &game_exit, &all);
	mlx_loop_hook(all.mlx.ptr, &ft_keys, &all);
	mlx_loop(all.mlx.ptr);
	return (0);
}
