#ifndef FABGX_BACKEND_PPM_H
#define FABGX_BACKEND_PPM_H

#include <stdio.h>

unsigned int fabgx_save_to_ppm(const fabgx_surface* surface,
	const char* file_path){

	FILE* file = fopen(file_path, "wb");
	if(!file) return 0;

	fprintf(file, "P6\n%u %u 255\n", surface->size.x, surface->size.y);

	const unsigned int lenght = surface->size.x * surface->size.y;

	uint8_t r, g, b;
	for(unsigned int i = 0; i < lenght; i++){
		fabgx_unpack_rgba(surface->pixels[i], &r, &g, &b, NULL);

		fwrite(&r, 1, 1, file);
		fwrite(&g, 1, 1, file);
		fwrite(&b, 1, 1, file);

		if(ferror(file)) return 0;
	}

	return 1;
}

#endif // FABGX_BACKEND_PPM_H
