/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:00:32 by suylee            #+#    #+#             */
/*   Updated: 2021/05/11 18:02:22 by suylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_exit(t_all *all)
{
	if (all->mlx.ptr && all->mlx.winptr)
	{
		mlx_clear_window(all->mlx.ptr, all->mlx.winptr);
		mlx_destroy_window(all->mlx.ptr, all->mlx.winptr);
	}
	if (all->sprites)
		free(all->sprites);
	if (all->info.bufmap)
		free(all->info.bufmap);
	exit(0);
}

void	ft_ifspace(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
			|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

char	*ft_suprspace(char *str)
{
	int		i;
	char	*tmp;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != ' ')
			i++;
		j++;
	}
	if (!(tmp = ft_calloc(i, sizeof(char))))
		return (NULL);
	j = 0;
	k = -1;
	while (str[++k] && j <= k)
	{
		if (str[k] != ' ')
			tmp[j++] = str[k];
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*ft_strjoinfr(char const *s1, char const *s2, int f)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[++j] != '\0')
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if ((f == 1 || f == 3) && s1)
		free((char*)s1);
	if ((f == 2 || f == 3) && s2)
		free((char*)s2);
	return (str);
}
