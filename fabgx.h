#ifndef FABGX_H
#define FABGX_H

#include <stdint.h>
#include <stdlib.h>

typedef struct{
	uint8_t r, g, b, a;
}fabgx_color;

fabgx_color fabgx_mix_colors(const fabgx_color color1,
	const fabgx_color color2){

	const float a1f = color1.a / 255.f;
	const float a2f = color2.a / 255.f;
	const float amf = a1f * (1 - a2f);

	return (fabgx_color){
		.r = color1.r * amf + color2.r * a2f,
		.g = color1.g * amf + color2.g * a2f,
		.b = color1.b * amf + color2.b * a2f,
		.a = (amf + a2f) * 255
	};
}

typedef struct{
	unsigned int x, y;
}fabgx_vec2;

typedef struct{
	fabgx_color* pixels;
	fabgx_vec2 size;
}fabgx_surface;

void fabgx_fill(fabgx_surface* surface, const fabgx_color color){
	const unsigned int lenght = surface->size.x * surface->size.y;

	for(unsigned int i = 0; i < lenght; i++){
		surface->pixels[i] = fabgx_mix_colors(surface->pixels[i], color);
	}
}

void fabgx_pixel(fabgx_surface* surface, const fabgx_vec2 pos,
	const fabgx_color color){

	const unsigned int i = pos.y * surface->size.x + pos.x;
	surface->pixels[i] = fabgx_mix_colors(surface->pixels[i], color);
}

void fabgx_rect(fabgx_surface* surface, const fabgx_vec2 pos,
	const fabgx_vec2 size, const fabgx_color color){

	const fabgx_vec2 end_pos = {pos.x + size.x, pos.y + size.y};

	for(unsigned int y = pos.y; y < end_pos.y; y++){
		for(unsigned int x = pos.y; x < end_pos.x; x++){
			fabgx_pixel(surface, (fabgx_vec2){x, y}, color);
		}
	}
}

void fabgx_line(fabgx_surface* surface, fabgx_vec2 start_pos,
	const fabgx_vec2 end_pos, const fabgx_color color){

	// https://en.wikipedia.org/wiki/Bresenham's_line_algorithm
	const int dx = abs(end_pos.x - start_pos.x);
	const int dy = -abs(end_pos.y - start_pos.y);
	const int sx = start_pos.x < end_pos.x ? 1 : -1;
	const int sy = start_pos.y < end_pos.y ? 1 : -1;

	int e2, error = dx + dy;

	while(1){
		fabgx_pixel(surface, start_pos, color);
		if(start_pos.x == end_pos.x && start_pos.y == end_pos.y) break;
		e2 = error * 2;
		if(e2 >= dy){
			if(start_pos.x == end_pos.x) break;
			error += dy;
			start_pos.x += sx;
		}
		if(e2 <= dx){
			if(start_pos.y == end_pos.y) break;
			error += dx;
			start_pos.y += sy;
		}
	}
}

#endif // FABGX_H
