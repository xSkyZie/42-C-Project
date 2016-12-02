/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_line_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:58:43 by malexand          #+#    #+#             */
/*   Updated: 2016/12/02 15:05:11 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libmlx.h"

/*
**	Tracer de Bresenham
*/

static	t_bres	init(t_point *p1, t_point *p2)
{
	t_bres		bres;

	bres.x0 = p1->px;
	bres.y0 = p1->py;
	bres.x1 = p2->px;
	bres.y1 = p2->py;
	bres.dx = ((p2->px - bres.x0) < 0) ? -(p2->px - bres.x0) : p2->px - bres.x0;
	bres.sx = bres.x0 < p2->px ? 1 : -1;
	bres.dy = ((p2->py - p1->py) < 0) ? -(p2->py - p1->py) : p2->py - p1->py;
	bres.sy = p1->py < p2->py ? 1 : -1;
	bres.err = ((bres.dx > bres.dy) ? bres.dx : -bres.dy) / 2;
	bres.e2 = 0;
	return (bres);
}

void			mlx_put_line(t_mlx *mlx, t_point *p1, t_point *p2)
{
	t_bres		bres;

	bres = init(p1, p2);
	bres.color = 0xFFFFFF;
	while (1)
	{
		if (bres.x0 < mlx->width && bres.y0 < mlx->heigth)
			mlx_pixel_put_img(bres.color, mlx->img, bres.x0, bres.y0);
		if (bres.x0 == bres.x1 && bres.y0 == bres.y1)
			break ;
		bres.e2 = bres.err;
		if (bres.e2 > -bres.dx)
		{
			bres.err -= bres.dy;
			bres.x0 += bres.sx;
		}
		if (bres.e2 < bres.dy)
		{
			bres.err += bres.dx;
			bres.y0 += bres.sy;
		}
	}
}