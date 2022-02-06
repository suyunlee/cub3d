/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:32:03 by suylee            #+#    #+#             */
/*   Updated: 2021/05/11 15:33:56 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture		ft_puttexture(char *texture_addr, t_all *all)
{
	t_texture	texture;

	if (!(texture.ptr = mlx_xpm_file_to_image(all->mlx.ptr,
		texture_addr, &texture.w, &texture.h)))
	{
		printf("Error\nThe texture path isn't correct");
		ft_exit(all);
	}
	if (!(texture.data = (int *)mlx_get_data_addr(texture.ptr,
		&texture.bpp, &texture.line_size, &texture.endian)))
	{
		printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
	return (texture);
}

t_mlx			ft_texturespr(char *texture_addr, t_all *all)
{
	t_mlx	texture;

	if (!(texture.ptr = mlx_xpm_file_to_image(all->mlx.ptr,
		texture_addr, &texture.w, &texture.h)))
	{
		printf("Error\nThe sprite texture path isn't correct");
		ft_exit(all);
	}
	if (!(texture.get_data = (int *)mlx_get_data_addr(texture.ptr,
		&texture.bpp, &texture.size_l, &texture.endian)))
	{
		printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
	return (texture);
}

void			ft_textures(t_all *all)
{
	int		i;
	char	*text;

	i = -1;
	all->texturen = ft_puttexture(all->info.n, all);
	all->textures = ft_puttexture(all->info.s, all);
	all->texturee = ft_puttexture(all->info.e, all);
	all->texturew = ft_puttexture(all->info.w, all);
	while (++i < all->spr.nbsp)
	{
		text = all->info.i;
		all->sprites[i].img = ft_texturespr(text, all);
	}
}
