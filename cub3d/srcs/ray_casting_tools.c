#include "mlx_utils.h"
#include <stdio.h>

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}

void	ft_update(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	program->frame++;
	if (program->frame % program->render->delay == 0)
	{
		fill_window(program, 0x650000FF);
		ray_casting(program);
	}
}

void	ray_casting(t_program *data)
{
	float	ray_angle = data->player->angle - data->player->half_fov;
	for(int ray_count = 0; ray_count < data->screen->width; ray_count++) {
		
		// Ray data
		t_vector2	ray = ft_floattovec2(data->player->x, data->player->y);
		printf("data: %f %f\n", data->player->x, data->player->y);

		// Wall finder
		char wall = 48;
		while (wall == 48) {
			ray.x += cosf(degrees_to_radians(ray_angle)) / data->rc->precision;
			ray.y += sinf(degrees_to_radians(ray_angle)) / data->rc->precision;
			wall = data->map->map[(int)floorf(ray.y)][(int)floorf(ray.x)];
		}

		// Pythagoras theorem
		float distance = sqrtf(powf(data->player->x - ray.x, 2) + powf(data->player->y - ray.y, 2));	// * cosf(degrees_to_radians(ray_angle - 0)); où 0 = rotation du joueur
		printf("distance %f pow1 %f pow2 %f\n", sqrtf(powf(data->player->x - ray.x, 2) + powf(data->player->y - ray.y, 2)), powf(data->player->x - ray.x, 2), powf(data->player->y - ray.y, 2));
		printf("after pow %f - %f, %f - %f\n\n", data->player->x, ray.x, data->player->y, ray.y);
		// Wall height
		float wall_height = floorf((float)data->screen->half_height / distance);
		printf("floor %f half height %d dist %f\n", floorf((float)data->screen->half_height / distance), data->screen->half_height, distance);

		// Draw
		printf("printf1: %d %d\n%f %d\n\n",ray_count, data->screen->half_height, wall_height, data->screen->height);
		t_vector2	vec = ft_floattovec2(ray_count, 0);
		t_vector2	vec2 = ft_floattovec2(ray_count, (float)(data->screen->half_height - wall_height));
		t_vector2	vec3 = ft_floattovec2(ray_count, (float)(data->screen->half_height + wall_height));
		t_vector2	vec4 = ft_floattovec2(ray_count, (float)(data->screen->height));
		draw_line(data->img.img, vec, vec2, 0x00FFFFFF);
		ft_printf("ciao");
		draw_line(data->img.img, vec2, vec3, 0xFF0000FF);
		ft_printf("ciao2");
		draw_line(data->img.img, vec3, vec4, 0x00FF00FF);
		ft_printf("ciao3");

		// Increment
		ray_angle += data->rc->increment_angle;
	}
}

/*
void	ray_casting(t_program *data)
{
	t_vector2	vec;
	t_vector2	vec2;
	t_vector2	vec3;
	t_vector2	vec4;

	vec = ft_floattovec2(480, 0);
	vec2 = ft_floattovec2(480, 0);
	vec3 = ft_floattovec2(480, 240);
	vec4 = ft_floattovec2(480, 63);
	draw_line(data->img.img, vec, vec2, 0x00FFFFFF);
	draw_line(data->img.img, vec2, vec3, 0xFF0000FF);
	draw_line(data->img.img, vec3, vec4, 0x00FF00FF);
}
*/