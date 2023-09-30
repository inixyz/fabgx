#ifndef FABGX_BACKEND_PPM_H
#define FABGX_BACKEND_PPM_H

#include <stdio.h>

unsigned int fabgx_save_to_ppm(const fabgx_surface* surface,
	const char* file_path){

	FILE* file = fopen(file_path, "wb");
	if(!file) return 0;

	// header
	fprintf(file, "P6\n%u %u 255\n", surface->size.x, surface->size.y);

	//body
	const unsigned int lenght = surface->size.x * surface->size.y;
	for(unsigned int i = 0; i < lenght; i++){
		fwrite(surface->pixels + i, 1, 3, file);
	}

	fclose(file);
	return 1;
}

#endif // FABGX_BACKEND_PPM_H
