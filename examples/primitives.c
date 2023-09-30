#include "fabgx.h"
#include "fabgx_backend_ppm.h"

int main(){
	const unsigned int width = 400, height = 400;
	fabgx_color pixels[width * height];
	fabgx_surface surface = {pixels, {width, height}};

	fabgx_fill(&surface, (fabgx_color){50, 50, 50, 255});

	fabgx_rect(&surface, (fabgx_vec2){150, 150}, (fabgx_vec2){200, 200},
		(fabgx_color){0, 255, 0, 255});

	fabgx_save_to_ppm(&surface, "examples/primitives.ppm");
}
