/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calibration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:48:28 by wmonacho          #+#    #+#             */
/*   Updated: 2022/05/17 16:03:39 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_calibration(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->y_max)
	{
		j = -1;
		while (++j < fdf->x_max)
		{
			fdf->dfault[i][j].x = fdf->dfault[i][j].x * fdf->dist;
			fdf->dfault[i][j].y = fdf->dfault[i][j].y * fdf->dist;
			fdf->dfault[i][j].x += fdf->posx;
			fdf->dfault[i][j].y += fdf->posy;
		}
	}
}

void	ft_calibrate_z(t_fdf *fdf)
{
	float	compare;
	int		i;
	int		j;

	i = -1;
	compare = ft_calculate_diffinv(fdf->x_max, fdf->y_max);
	while (++i < fdf->y_max)
	{
		j = -1;
		while (++j < fdf->x_max)
		{
			if (fdf->map[i][j].z != 0 && fdf->z_max >= compare / 2)
			{
				if (fdf->z_max >= compare * 2)
					fdf->map[i][j].z = fdf->map[i][j].z
						/ ((fdf->z_max / compare) * 4);
				if (fdf->z_max < compare * 2)
					fdf->map[i][j].z = fdf->map[i][j].z
						/ ((compare / fdf->z_max) * 4);
			}
		}
	}
	i = 0;
	fdf->dfault = (t_default **)malloc(sizeof(t_default *) * (fdf->y_max));
	while (i < fdf->y_max)
		fdf->dfault[i++] = (t_default *)malloc(sizeof(t_default)
				* (fdf->x_max));
}

float	ft_calculate_diffinv(float ratio_x, float ratio_y)
{
	if (ratio_x >= ratio_y)
	{
		return (ratio_x);
	}
	if (ratio_x <= ratio_y)
	{
		return (ratio_y);
	}
	return (1);
}

float	ft_calculate_diff(float ratio_x, float ratio_y)
{
	if (ratio_x >= ratio_y)
	{
		return (ratio_y);
	}
	if (ratio_x <= ratio_y)
	{
		return (ratio_x);
	}
	return (1);
}

float	ft_max(float max1, float max2)
{
	if (max1 > max2)
		return (max1);
	if (max1 < max2)
		return (max2);
	return (max1);
}
