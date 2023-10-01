#include "fabgx.h"
#include "fabgx_backend_ppm.h"

int main(){
	const unsigned int width = 400, height = 400;
	fabgx_color pixels[width * height];
	fabgx_surface surface = {pixels, {width, height}};

	fabgx_fill(&surface, (fabgx_color){50, 50, 50, 255});

	fabgx_line(&surface, (fabgx_vec2u){200, 200}, (fabgx_vec2u){50, 150},
		(fabgx_color){255, 0, 0, 255});


	fabgx_ellipse(&surface, (fabgx_vec2u){200, 200}, (fabgx_vec2u){180, 80},
		(fabgx_color){230, 50, 230, 255});

	fabgx_save_to_ppm(&surface, "examples/primitives.ppm");
}
