/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:04:41 by suylee            #+#    #+#             */
/*   Updated: 2021/05/17 12:31:10 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>

# define K_W	13
# define K_A	0
# define K_S	1
# define K_D	2
# define K_ESC	53
# define K_R	124
# define K_L	123

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 4658
# endif

typedef struct		s_coor
{
	int				x;
	int				y;
}					t_coor;

typedef struct		s_dcoor
{
	double			x;
	double			y;
}					t_dcoor;

typedef struct		s_mlx
{
	void			*ptr;
	void			*winptr;
	void			*imgptr;
	int				bpp;
	int				size_l;
	int				endian;
	int				*get_data;
	int				w;
	int				h;
	int				color;
}					t_mlx;

typedef struct		s_cam
{
	t_dcoor			pos;
	t_dcoor			dir;
	t_dcoor			plane;
	int				isit;
	double			movespeed;
	double			rotspeed;
}					t_cam;

typedef struct		s_algo
{
	t_dcoor			raypos;
	t_dcoor			sided;
	t_dcoor			delta;
	t_coor			step;
	t_dcoor			raydir;
	t_coor			map;
	int				side;
	double			camx;
	double			pdist;
	double			lineh;
	double			drawstart;
	double			drawend;
	t_dcoor			trans;
	int				spscreen;
	t_coor			start;
	t_coor			end;
	int				texsp_x;
}					t_algo;

typedef struct		s_key
{
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_r;
	int				key_l;
}					t_key;

typedef struct		s_info
{
	char			*n;
	char			*s;
	char			*e;
	char			*w;
	char			*i;
	unsigned int	c;
	unsigned int	f;
	t_coor			res;
	t_coor			maplen;
	char			*bufmap;
	int				test[256];
	int				sx;
	int				sy;
}					t_info;

typedef struct		s_texture
{
	void			*ptr;
	int				*data;
	int				bpp;
	int				line_size;
	int				endian;
	int				h;
	int				w;
	int				color;
}					t_texture;

typedef struct		s_sprites
{
	t_dcoor			coor;
	double			dist;
	int				ordre;
	t_mlx			img;
}					t_sprites;

typedef struct		s_spr
{
	int				nbsp;
	t_dcoor			camsp;
	t_dcoor			trans;
	t_coor			start;
	t_coor			end;
	int				spscreen;
	int				sph;
	int				spw;
	t_coor			texsp;
	double			*distwall;
}					t_spr;

typedef struct		s_bmp
{
	int				size;
	unsigned char	header[14];
	unsigned char	info[40];
	unsigned char	pad[3];
	int				color;
	int				fd;
}					t_bmp;

typedef struct		s_all
{
	t_algo			algo;
	t_info			info;
	t_mlx			mlx;
	t_cam			cam;
	t_key			key;
	t_spr			spr;
	t_texture		texturen;
	t_texture		textures;
	t_texture		texturee;
	t_texture		texturew;
	t_sprites		*sprites;
}					t_all;

int					main(int argc, char **argv);
void				ft_cub(char *argv);
int					ft_block(t_all *all);
int					game_exit(t_all *all);

void				initmlx(t_all *all);
void				initwin(t_all *all, char **argv);
void				ft_refresh(t_all *all);
int					mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
void				maxscreen(t_all *all);
void				initall(t_all *all, char **argv);

void				ft_error(t_all *all);
void				ft_bufmap(t_all *all, char *line);
void				ft_firstcheck(t_all *all, char c, char d);
void				ft_parsing_line(t_all *all, char *line, int i);
void				ft_parsing(char **argv, t_all *all);

void				ft_res(t_all *all, char *line);
char				*ft_dirtex(t_all *all, char *line);
void				ft_colnumj(char *line, int *i, int *j);
void				ft_colcheck(t_all *all, char *line, int i);
int					ft_col(char *line, t_all *all);

void				ft_algo(t_all *all);
void				ft_initalgo(t_all *all);
void				ft_initray(t_all *all, int x);
void				ft_reycasting(t_all *all);

t_texture			ft_mettretexture(t_all *all);
void				ft_drawall(t_all *all, int x);

void				set_header(unsigned char *header, int param);
void				imgbmp(t_all *all, t_bmp *bmp);
void				ft_header(t_all *all, t_bmp *bmp);
void				ft_bmp(t_all *all);
void				ft_bmpinit(t_all *all);

void				ft_checkones(t_all *all);
void				posdepart(t_all *all, int x, int y, char dir);
void				ft_checkline(char *line, int j, t_all *all);
void				verify_map(t_all *all);

void				ft_textures(t_all *all);
t_texture			ft_puttexture(char *texture_addr, t_all *all);
t_mlx				ft_texturespr(char *texture_addr, t_all *all);

void				ft_sprites(t_all *all);
void				sp_draw(t_all *all, int x, int i);
void				init_sprites(t_all *all);

float				ft_fpower(float nb, int power);
void				ft_sort(t_all *all);
void				ft_sort_sp(t_all *all);
void				sp_position(t_all *all, int i);
void				sp_dimension(t_all *all);

void				ft_moverot(t_all *all);
void				ft_moveside(t_all *all);
void				ft_moveup(t_all *all);
int					key_press(int key, t_all *all);
int					key_release(int key, t_all *all);
int					ft_keys(t_all *all);

void				ft_exit(t_all *all);
void				ft_ifspace(char *line, int *i);
void				ft_strdel(char **as);
char				*ft_suprspace(char *str);
char				*ft_strjoinfr(char const *s1, char const *s2, int f);

int					ft_getnewline(char *backup);
int					gnl_fill(char **backup, char **line);
int					gnl_result(char **backup, char **line, int size, int fd);
int					get_next_line(int fd, char **line);

#endif
