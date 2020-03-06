#include "wolf3d.h"


int			render(t_param *param)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = x * 2 / (double)WINDOW_WIDTH - 1;
		param->look.dir_x = param->look.cam_dir_x
			+ param->look.plane_x * camera_x;
		param->look.dir_y = param->look.cam_dir_y
			+ param->look.plane_y * camera_x;

		
		//which box of the map we're in
		param->look.real_map_x = (int)param->look.pos_x;
		param->look.real_map_y = (int)param->look.pos_y;


		
	
		//length of ray from one x or y-side to next x or y-side
		param->look.d_dist_x = fabs(1 / param->look.dir_x);
		param->look.d_dist_y = fabs(1 / param->look.dir_y);

		// Alternative code for deltaDist in case division through zero is not supported
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		// param->look.d_dist_x = (param->look.dir_y == 0) ? 0 :
		// 	((param->look.dir_x == 0) ? 1 : fabs(1 / param->look.dir_x));
      	// param->look.d_dist_y = (param->look.dir_x == 0) ? 0 :
		//   ((param->look.dir_y == 0) ? 1 : fabs(1 / param->look.dir_y));
	
	

		




		//calculate step and initial sideDist
		if (param->look.dir_x < 0)
		{
			param->look.step_x = -1;
			param->look.dist_to_side_x = (param->look.pos_x -
				param->look.real_map_x) * param->look.d_dist_x;
		}
		else
		{
			param->look.step_x = 1;
			param->look.dist_to_side_x = (param->look.real_map_x + 1.0
			- param->look.pos_x) * param->look.d_dist_x;
		}
		////////////////////////////////////////////////
		if (param->look.dir_y < 0)
		{
			param->look.step_y = -1;
			param->look.dist_to_side_y = (param->look.pos_y -
				param->look.real_map_y) * param->look.d_dist_y;
			
		
		}
		else
		{
			param->look.step_y = 1;
			param->look.dist_to_side_y = (param->look.real_map_y
				+ 1.0 - param->look.pos_y) * param->look.d_dist_y;
		}
		//////////////////////////////////////
		
		param->look.hit = 0;


		//perform DDA
		//print_map(param);
		while (param->look.hit == 0)
		{
			
			//jump to next map square in x-direction OR in y-direction
			if (param->look.dist_to_side_x < param->look.dist_to_side_y)
			{
				param->look.dist_to_side_x += param->look.d_dist_x;
				param->look.real_map_x += param->look.step_x;
				param->look.hit_side = X_SIDE;
			}
			else
			{
				param->look.dist_to_side_y += param->look.d_dist_y;
				param->look.real_map_y += param->look.step_y;
				param->look.hit_side = Y_SIDE;
			}
			//Check if ray has hit a wall
			if (param->map[param->look.real_map_y][param->look.real_map_x] > 0)
				param->look.hit = 1;
		}

		//Calculate distance projected on camera direction
			//(Euclidean distance will give fisheye effect!)
      	if (param->look.hit_side == X_SIDE) 
	  		param->look.perp_dist_to_wall = (param->look.real_map_x - param->look.pos_x
			+ (1 - param->look.step_x) / 2) / param->look.dir_x;
     	else
	  		param->look.perp_dist_to_wall = (param->look.real_map_y - param->look.pos_y
			+ (1 - param->look.step_y) / 2) / param->look.dir_y;







			//Calculate height of line to draw on screen
		param->look.line_h = (int)(WINDOW_HEIGHT / param->look.perp_dist_to_wall);

			//calculate lowest and highest pixel to fill in current stripe
		param->look.draw_start = WINDOW_HEIGHT / 2 - param->look.line_h / 2;
		if (param->look.draw_start < 0)
			param->look.draw_start = 0;
		param->look.draw_end = WINDOW_HEIGHT / 2 + param->look.line_h / 2 ;
		if (param->look.draw_end >= WINDOW_HEIGHT)
			param->look.draw_end = WINDOW_HEIGHT - 1;


		if (param->map[param->look.real_map_y][param->look.real_map_x] == 1)
			param->look.colour = 0xFF0000; 
		else if (param->map[param->look.real_map_y][param->look.real_map_x] == 2)
			param->look.colour = 0x00FF00; 
		else if (param->map[param->look.real_map_y][param->look.real_map_x] == 3)
			param->look.colour = 0x0000FF; 
		else if (param->map[param->look.real_map_y][param->look.real_map_x] == 4)
			param->look.colour = 0xFFFFFF; 
		else
			param->look.colour = 0x000000; 

		if (param->look.hit_side == Y_SIDE)
			param->look.colour /= 2;


		//draw line!!!!!!!!!!!!!!!!!
		int y_y;

		y_y = param->look.draw_start;
		while (y_y < param->look.draw_end)
		{
			mlx_pixel_put(param->mlx_par.mlx_ptr, param->mlx_par.win_ptr, x, y_y, param->look.colour);
			y_y++;
		}
		x++;
	}






	 //timing for input and FPS counter
    param->time_old = param->time;
    param->time = (double)clock();
	
	 //frameTime is the time this frame has taken, in seconds
    param->frame_time = (param->time - param->time_old) / CLOCKS_PER_SEC;
    //printf("%f\n", 1.0 / param->frame_time); //FPS counter
	mlx_clear_window(param->mlx_par.mlx_ptr, param->mlx_par.win_ptr);

   
	 param->ms =  param->frame_time * 5.0;
   
	
	 param->rot_speed =  param->frame_time * 3.0; 






	return (0);
}


int			main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2)
		return (wrong_num_of_args());
	initialize(&param);
	if (read_map(&param, argv[1]) == 0)
		return (-1);


















	/*if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return (-1);
	} 

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
		// Открыть окно и создать в нем контекст OpenGL
	GLFWwindow* window;
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT,
		"Wolf3D", NULL, NULL);
	if (window == NULL)
	{
		fprintf( stderr, "Невозможно открыть окно GLFW.\n" );
		glfwTerminate();
		return (-1);
	}



	glfwMakeContextCurrent(window);


		// Инициализируем GLEW
	glewExperimental = GL_TRUE; // Флаг необходим в Core-режиме OpenGL
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Невозможно инициализировать GLEW.\n");
		return (-1);
	}

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	//glEnable(GL_DEPTH_TEST); // enable depth-testing
	//glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	GLuint VertexArrayID = 0;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	
	//Массив 3 векторов, которые являются вершинами треугольника
	static const GLfloat g_vertex_buffer_data[] = {
	-100.0f, 0.0f, 0.0f,
	100.0f, 0.0f, 0.0f
	};
	// Это будет идентификатором нашего буфера вершин
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);




	while ( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
       glfwWindowShouldClose(window) == 0 )
    {


		//render(&param);




		// Указываем, что первым буфером атрибутов будут вершины
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(
		0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
		3,                  // Размер
		GL_FLOAT,           // Тип
		GL_FALSE,           // Указывает, что значения не нормализованы
		0,                  // Шаг
		(void*)0            // Смещение массива в буфере
		);

		// Вывести треугольник!
		glDrawArrays(GL_LINE, 0, 2); // Начиная с вершины 0, всего 3 вершины -> один треугольник
		glDisableVertexAttribArray(0);











		glClear( GL_COLOR_BUFFER_BIT );
        glfwSwapBuffers(window);
        glfwPollEvents();
   	}
 
	glfwDestroyWindow(window);

	glfwTerminate();

	*/
	param.mlx_par.mlx_ptr = mlx_init();
	param.mlx_par.win_ptr = mlx_new_window(param.mlx_par.mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT, "Eto moe okno");
	mlx_loop_hook(param.mlx_par.mlx_ptr, &render, &param);
	mlx_hook(param.mlx_par.win_ptr, 2, 0, &key_press_down, (void*)&param);
	mlx_loop(param.mlx_par.mlx_ptr);
	return (0);
}
