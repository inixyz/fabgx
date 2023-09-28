#ifndef FABGX_H
#define FABGX_H

#include <stdint.h>

typedef struct{
	unsigned int x, y;
}fabgx_vec2;

typedef struct{
	uint32_t* pixels;
	fabgx_vec2 size;
}fabgx_surface;

uint32_t fabgx_rgba(const uint8_t r, const uint8_t g, const uint8_t b,
	const uint8_t a){

	return r << 24 | g << 16 | b << 8 | a;
}

void fabgx_unpack_rgba(const uint32_t color, uint8_t* r, uint8_t* g, uint8_t* b,
	uint8_t* a){

	if(r) *r = color >> 24;
	if(g) *g = color >> 16 & 0xFF;
	if(b) *b = color >> 8 & 0xFF;
	if(a) *a = color & 0xFF;
}

uint32_t fabgx_mix_colors(const uint32_t color1, const uint32_t color2){
	uint8_t r1, g1, b1, a1;
	fabgx_unpack_rgba(color1, &r1, &g1, &b1, &a1);

	uint8_t r2, g2, b2, a2;
	fabgx_unpack_rgba(color2, &r2, &g2, &b2, &a2);

	const float a1f = a1 / 255.0f;
	const float a2f = a2 / 255.0f;
	const float amf = a1f * (1 - a2f);

	uint8_t r, g, b, a;
	r = r1 * amf + r2 * a2f;
	g = g1 * amf + g2 * a2f;
	b = b1 * amf + b2 * a2f;
	a = (amf + a2f) * 255;

	return fabgx_rgba(r, g, b, a);
}

void fabgx_blend_index(fabgx_surface* surface, const unsigned int i,
	const uint32_t color){

	surface->pixels[i] = fabgx_mix_colors(surface->pixels[i], color);
}

void fabgx_pixel(fabgx_surface* surface, const fabgx_vec2 pos,
	const uint32_t color){

	fabgx_blend_index(surface, pos.y * surface->size.x + pos.x, color);
}

void fabgx_fill(fabgx_surface* surface, const uint32_t color){
	const unsigned int lenght = surface->size.x * surface->size.y;

	for(unsigned int i = 0; i < lenght; i++){
		fabgx_blend_index(surface, i, color);
	}
}

void fabgx_rect(fabgx_surface* surface, const fabgx_vec2 pos,
	const fabgx_vec2 size, const uint32_t color){

	const fabgx_vec2 end_pos = {pos.x + size.x, pos.y + size.y};

	for(unsigned int y = pos.y; y < end_pos.y; y++){
		for(unsigned int x = pos.y; x < end_pos.x; x++){
			fabgx_pixel(surface, (fabgx_vec2){x, y}, color);
		}
	}
}

#endif // FABGX_H
