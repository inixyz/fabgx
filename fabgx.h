#ifndef FABGX_H
#define FABGX_H

#include <stdint.h>

//------------------------------------------------------------------------------

typedef struct{
	uint8_t r, g, b, a;
}fabgx_color;

typedef struct{
	unsigned int x, y;
}fabgx_vec2u;

typedef struct{
	fabgx_color* pixels;
	fabgx_vec2u size;
}fabgx_surface;

//------------------------------------------------------------------------------

int fabgx_absint(const int val){
	return val < 0 ? -val : val;
}

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

void fabgx_fill(fabgx_surface* surface, const fabgx_color color){
	const unsigned int lenght = surface->size.x * surface->size.y;

	for(unsigned int i = 0; i < lenght; i++){
		surface->pixels[i] = fabgx_mix_colors(surface->pixels[i], color);
	}
}

//------------------------------------------------------------------------------

void fabgx_pixel(fabgx_surface* surface, const fabgx_vec2u pos,
	const fabgx_color color){

	const unsigned int i = pos.y * surface->size.x + pos.x;
	surface->pixels[i] = fabgx_mix_colors(surface->pixels[i], color);
}

//------------------------------------------------------------------------------

void fabgx_rect(fabgx_surface* surface, const fabgx_vec2u pos,
	const fabgx_vec2u size, const fabgx_color color){

	const fabgx_vec2u end_pos = {pos.x + size.x, pos.y + size.y};

	for(unsigned int y = pos.y; y < end_pos.y; y++){
		for(unsigned int x = pos.y; x < end_pos.x; x++){
			fabgx_pixel(surface, (fabgx_vec2u){x, y}, color);
		}
	}
}

//------------------------------------------------------------------------------

void fabgx_line(fabgx_surface* surface, fabgx_vec2u start_pos,
	const fabgx_vec2u end_pos, const fabgx_color color){

	// https://en.wikipedia.org/wiki/Bresenham's_line_algorithm
	const int dx = fabgx_absint(end_pos.x - start_pos.x);
	const int dy = -fabgx_absint(end_pos.y - start_pos.y);
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

//------------------------------------------------------------------------------

void fabgx_ellipse(fabgx_surface* surface, const fabgx_vec2u center,
	const fabgx_vec2u size, const fabgx_color color){

	const unsigned int ww = size.x * size.x;
	const unsigned int hh = size.y * size.y;
	const unsigned int wwhh = ww * hh;

	int x0 = size.x, x1;
	int dx = 0;

	for(int x = -(int)size.x; x <= (int)size.x; x++){
		fabgx_pixel(surface, (fabgx_vec2u){center.x + x, center.y}, color);
	}

	for(int y = 1; y <= size.y; y++){
	    for(x1 = x0 - (dx - 1); x1 > 0; x1--){
			if(x1 * x1 * hh + y * y * ww <= wwhh) break;
	    }

	    dx = x0 - x1;
	    x0 = x1;

	    for(int x = -x0; x <= x0; x++){
	    	fabgx_pixel(surface, (fabgx_vec2u){center.x + x, center.y - y},
	    		color);
	    	fabgx_pixel(surface, (fabgx_vec2u){center.x + x, center.y + y},
	    		color);
	    }
	}
}

#endif // FABGX_H
