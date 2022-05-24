/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:59:18 by wmonacho          #+#    #+#             */
/*   Updated: 2022/05/24 12:00:12 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_malloc_dfault(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->dfault = (t_default **)malloc(sizeof(t_default *) * (fdf->y_max));
	if (fdf->dfault == NULL)
		return (ft_free_all(fdf));
	while (i < fdf->y_max)
		fdf->dfault[i++] = (t_default *)malloc(sizeof(t_default)
				* (fdf->x_max));
	if (fdf->dfault[i] == NULL)
		return (ft_free_all(fdf));
}

void	ft_malloc_mapsbis(t_fdf *fdf)
{
	int	i;

	fdf->map = (t_point **)malloc(sizeof(t_point *) * (fdf->y_max));
	if (fdf->map == NULL)
		exit (0);
	i = 0;
	while (i < fdf->y_max)
		fdf->map[i++] = (t_point *)malloc(sizeof(t_point) * (fdf->x_max));
	if (fdf->map == NULL)
		ft_free_map(fdf);
}

void	ft_malloc_maps(t_fdf *fdf, char *line, int fd)
{
	int		i;
	char	**tab;
	char	*trim;

	i = 0;
	line = get_next_line(fd);
	trim = ft_strtrim(line, "\n");
	tab = ft_split(trim, ' ');
	free(trim);
	while (tab[i] != NULL)
		i++;
	fdf->x_max = i;
	fdf->y_max = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		fdf->y_max++;
	}
	free(line);
	i = 0;
	while (tab[i] != '\0')
		free(tab[i++]);
	free(tab);
	ft_malloc_mapsbis(fdf);
}