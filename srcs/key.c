/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:19:59 by suylee            #+#    #+#             */
/*   Updated: 2021/05/17 12:06:23 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_moverot(t_all *all)
{
	double	olddirx;

	if (all->key.key_l)
	{
		olddirx = all->cam.dir.x;
		all->cam.dir.x = all->cam.dir.x * cos(-all->cam.rotspeed)
			- all->cam.dir.y * sin(-all->cam.rotspeed);
		all->cam.dir.y = olddirx * sin(-all->cam.rotspeed) +
			all->cam.dir.y * cos(-all->cam.rotspeed);
		all->cam.plane.x = -0.66 * all->cam.dir.y;
		all->cam.plane.y = 0.66 * all->cam.dir.x;
	}
	if (all->key.key_r)
	{
		olddirx = all->cam.dir.x;
		all->cam.dir.x = all->cam.dir.x * cos(all->cam.rotspeed)
			- all->cam.dir.y * sin(all->cam.rotspeed);
		all->cam.dir.y = olddirx * sin(all->cam.rotspeed)
			+ all->cam.dir.y * cos(all->cam.rotspeed);
		all->cam.plane.x = -0.66 * all->cam.dir.y;
		all->cam.plane.y = 0.66 * all->cam.dir.x;
	}
}

void	ft_moveside(t_all *all)
{
	double posetmpx;
	double posetmpy;

	posetmpx = all->cam.pos.x;
	posetmpy = all->cam.pos.y;
	if (all->key.key_a)
	{
		all->cam.pos.x -= all->cam.plane.x * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y -= all->cam.plane.y * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
	if (all->key.key_d)
	{
		all->cam.pos.x += all->cam.plane.x * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y += all->cam.plane.y * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
}

void	ft_moveup(t_all *all)
{
	double posetmpx;
	double posetmpy;

	posetmpx = all->cam.pos.x;
	posetmpy = all->cam.pos.y;
	if (all->key.key_w)
	{
		all->cam.pos.x += all->cam.dir.x * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y += all->cam.dir.y * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
	if (all->key.key_s)
	{
		all->cam.pos.x -= all->cam.dir.x * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y -= all->cam.dir.y * all->cam.movespeed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
}

int		key_press(int key, t_all *all)
{
	if (key == K_ESC)
		ft_exit(all);
	if (key == K_W)
		all->key.key_w = 1;
	else if (key == K_S)
		all->key.key_s = 1;
	if (key == K_A)
		all->key.key_a = 1;
	else if (key == K_D)
		all->key.key_d = 1;
	if (key == K_R)
		all->key.key_r = 1;
	else if (key == K_L)
		all->key.key_l = 1;
	return (0);
}

int		key_release(int key, t_all *all)
{
	if (key == K_ESC)
		ft_exit(all);
	if (key == K_W)
		all->key.key_w = 0;
	else if (key == K_S)
		all->key.key_s = 0;
	if (key == K_A)
		all->key.key_a = 0;
	else if (key == K_D)
		all->key.key_d = 0;
	if (key == K_R)
		all->key.key_r = 0;
	else if (key == K_L)
		all->key.key_l = 0;
	return (0);
}
