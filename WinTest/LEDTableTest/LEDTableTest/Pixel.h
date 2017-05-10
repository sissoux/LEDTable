#pragma once
#include <stdint.h>
#include "CHSV.h"
#include "CRGB.h"

#define APPLY_DIMMING(X) (X)
#define HSV_SECTION_6 (0x20)
#define HSV_SECTION_3 (0x40)


class Pixel
{
public:
	//uint16_t ID = 1<<16;
	union {
		struct {
			union {
				uint8_t hue;
				uint8_t h;
			};
			union {
				uint8_t saturation;
				uint8_t sat;
				uint8_t s;
			};
			union {
				uint8_t value;
				uint8_t val;
				uint8_t v;
			};
		};
		uint8_t raw[3];
	};

	union {
		struct {
			union {
				uint8_t r;
				uint8_t red;
			};
			union {
				uint8_t g;
				uint8_t green;
			};
			union {
				uint8_t b;
				uint8_t blue;
			};
		};
		uint8_t raw[3];
	};


	bool operator!=(Pixel*);
	bool operator==(Pixel*);


	Pixel();
	Pixel(const Pixel &);
	Pixel(uint8_t h, uint8_t s, uint8_t v);
	~Pixel();

	//CHSV rgb2hsv(CRGB in);
	void hsv2rgb();
};


