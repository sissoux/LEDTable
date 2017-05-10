#include "Pixel.h"



Pixel::Pixel()
{
}

Pixel::Pixel(const Pixel &source)
{
	h = source.h;
	s = source.s;
	v = source.v;
	r = source.r;
	g = source.g;
	b = source.b;
}

Pixel::Pixel(uint8_t h, uint8_t s, uint8_t v)
{
	this->h = h;
	this->s = s;
	this->v = v;
	this->hsv2rgb();
}

Pixel::~Pixel()
{
}


/*CHSV Pixel::rgb2hsv(CRGB in)
{
	CHSV         out;
	double      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max > in.b ? max : in.b;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, v is undefined
		out.s = 0.0;
		//		out.h = null;                            // its now undefined
		return out;
	}
	if (in.r >= max)                           // > is bogus, just keeps compilor happy
		out.h = (in.g - in.b) / delta;        // between yellow & magenta
	else
		if (in.g >= max)
			out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
		else
			out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}*/

void Pixel::hsv2rgb()//const struct CHSV & hsv, struct CRGB & rgb)
{
	// Convert hue, saturation and brightness ( HSV/HSB ) to RGB
	// "Dimming" is used on saturation and brightness to make
	// the output more visually linear.

	// Apply dimming curves

	uint8_t value = APPLY_DIMMING(this->val);
	uint8_t saturation = this->sat;

	// The brightness floor is minimum number that all of
	// R, G, and B will be set to.
	uint8_t invsat = APPLY_DIMMING(255 - saturation);
	uint8_t brightness_floor = (value * invsat) / 256;

	// The color amplitude is the maximum amount of R, G, and B
	// that will be added on top of the brightness_floor to
	// create the specific hue desired.
	uint8_t color_amplitude = value - brightness_floor;

	// Figure out which section of the hue wheel we're in,
	// and how far offset we are withing that section
	uint8_t section = this->hue / HSV_SECTION_3; // 0..2
	uint8_t offset = this->hue % HSV_SECTION_3;  // 0..63

	uint8_t rampup = offset; // 0..63
	uint8_t rampdown = (HSV_SECTION_3 - 1) - offset; // 63..0

													 // We now scale rampup and rampdown to a 0-255 range -- at least
													 // in theory, but here's where architecture-specific decsions
													 // come in to play:
													 // To scale them up to 0-255, we'd want to multiply by 4.
													 // But in the very next step, we multiply the ramps by other
													 // values and then divide the resulting product by 256.
													 // So which is faster?
													 //   ((ramp * 4) * othervalue) / 256
													 // or
													 //   ((ramp    ) * othervalue) /  64
													 // It depends on your processor architecture.
													 // On 8-bit AVR, the "/ 256" is just a one-cycle register move,
													 // but the "/ 64" might be a multicycle shift process. So on AVR
													 // it's faster do multiply the ramp values by four, and then
													 // divide by 256.
													 // On ARM, the "/ 256" and "/ 64" are one cycle each, so it's
													 // faster to NOT multiply the ramp values by four, and just to
													 // divide the resulting product by 64 (instead of 256).
													 // Moral of the story: trust your profiler, not your insticts.

													 // Since there's an AVR assembly version elsewhere, we'll
													 // assume what we're on an architecture where any number of
													 // bit shifts has roughly the same cost, and we'll remove the
													 // redundant math at the source level:

													 //  // scale up to 255 range
													 //  //rampup *= 4; // 0..252
													 //  //rampdown *= 4; // 0..252

													 // compute color-amplitude-scaled-down versions of rampup and rampdown
	uint8_t rampup_amp_adj = (rampup   * color_amplitude) / (256 / 4);
	uint8_t rampdown_amp_adj = (rampdown * color_amplitude) / (256 / 4);

	// add brightness_floor offset to everything
	uint8_t rampup_adj_with_floor = rampup_amp_adj + brightness_floor;
	uint8_t rampdown_adj_with_floor = rampdown_amp_adj + brightness_floor;


	if (section) {
		if (section == 1) {
			// section 1: 0x40..0x7F
			this->r = brightness_floor;
			this->g = rampdown_adj_with_floor;
			this->b = rampup_adj_with_floor;
		}
		else {
			// section 2; 0x80..0xBF
			this->r = rampup_adj_with_floor;
			this->g = brightness_floor;
			this->b = rampdown_adj_with_floor;
		}
	}
	else {
		// section 0: 0x00..0x3F
		this->r = rampdown_adj_with_floor;
		this->g = rampup_adj_with_floor;
		this->b = brightness_floor;
	}
}

bool Pixel::operator ==(Pixel* input)
{
	return (this->h == input->h &&this->s == input->s &&this->v == input->v);	
}

bool Pixel::operator !=(Pixel* input)
{
	return (this->h != input->h || this->s != input->s || this->v != input->v);
}