#pragma once

struct Color {
	Color(float r = 1, float g = 1, float b = 1, float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	inline Color(const Color& other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
	}
	
	inline Color operator=(Color& other) {
		other.r = r;
		other.g = g;
		other.b = b;
		other.a = a;
		return other;
	}
	
	float r, g, b, a;
};
