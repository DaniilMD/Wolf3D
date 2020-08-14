#include "wolf3d.h"

void	mult_rgb(int *r, int *g, int *b)
{
	*r *= 0.5;
	*g *= 0.5;
	*b *= 0.5;
}

int		apply_fog(int curr_col, double dist, int mult_on_half)
{
	double			fog_coef;
	int				r;
	int				g;
	int				b;

	r = curr_col / 65536;
	g = (curr_col % 65536) / 256;
	b = ((curr_col % 65536) % 256);
	if (mult_on_half == 1)
		mult_rgb(&r, &g, &b);
	if (dist <= SIGHT_DIST)
	{
		fog_coef = dist * (1.0 / SIGHT_DIST);
		r = (1 - fog_coef) * r + fog_coef * FOG_R;
		g = (1 - fog_coef) * g + fog_coef * FOG_G;
		b = (1 - fog_coef) * b + fog_coef * FOG_B;
	}
	else
	{
		r = FOG_R;
		g = FOG_G;
		b = FOG_B;
	}
	return ((r * 65536) + (g * 256) + b);
}
