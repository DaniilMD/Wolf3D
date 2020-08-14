#include "wolf3d.h"

int			foo(char *p, int *cnt_comma, int *cnt_dot, int *i)
{
	if (p[*i] == '.')
	{
		if (*i == 0 || (p[*i - 1] > '9' ||
			p[*i - 1] < '0') || p[*i + 1] == '\0')
			return (0);
		if (*cnt_comma != 0 && *cnt_comma != 1)
			return (0);
		*cnt_dot += 1;
	}
	return (1);
}

int			norm_val_spr_par(char *p, int *cnt_comma, int *cnt_dot, int *i)
{
	while (p[*i] != '\0')
	{
		if ((p[*i] < '0' || p[*i] > '9') && p[*i] != ',' && p[*i] != '.')
			return (0);
		if (p[*i] == ',')
		{
			if (*i == 0 || (p[*i - 1] > '9' || p[*i - 1] < '0')
							|| p[*i + 1] == '\0')
				return (0);
			if (*cnt_dot != 1 && *cnt_dot != 2)
				return (0);
			*cnt_comma += 1;
		}
		if (!foo(p, cnt_comma, cnt_dot, i))
			return (0);
		if (*cnt_comma > 2 || *cnt_dot > 2)
			return (0);
		*i += 1;
	}
	return (1);
}

int			validate_sprite_par(char *spr_p)
{
	int i;
	int cnt_comma;
	int cnt_dot;

	i = 0;
	cnt_comma = 0;
	cnt_dot = 0;
	if (!norm_val_spr_par(spr_p, &cnt_comma, &cnt_dot, &i))
		return (0);
	if (cnt_comma < 2)
		return (0);
	if (cnt_dot < 2)
		return (0);
	return (1);
}

int			norm_valid_file(char c, char prev, int *dog_cnt)
{
	if (c == '@')
	{
		if (prev != '\n')
			return (0);
		*dog_cnt += 1;
	}
	return (1);
}

int			walls(int a)
{
	if (a == 0 || (a >= 'a' && a <= 'h') || a == 20)
		return (1);
	return (0);
}
