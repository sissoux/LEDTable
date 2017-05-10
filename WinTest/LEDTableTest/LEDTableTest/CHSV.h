#pragma once
#include <stdint.h>

/// Representation of an HSV pixel (hue, saturation, value (aka brightness)).
struct CHSV {
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

	/// default values are UNITIALIZED
	CHSV()
	{
	}

	/// allow construction from H, S, V
	CHSV(uint8_t ih, uint8_t is, uint8_t iv)
		: h(ih), s(is), v(iv)
	{
	}

	/// allow copy construction
	CHSV(const CHSV& rhs)
	{
		h = rhs.h;
		s = rhs.s;
		v = rhs.v;
	}

	CHSV& operator= (const CHSV& rhs)
	{
		h = rhs.h;
		s = rhs.s;
		v = rhs.v;
		return *this;
	}

	CHSV& setHSV(uint8_t ih, uint8_t is, uint8_t iv)
	{
		h = ih;
		s = is;
		v = iv;
		return *this;
	}
};

/// Pre-defined hue values for HSV objects
typedef enum {
	HUE_RED = 0,
	HUE_ORANGE = 32,
	HUE_YELLOW = 64,
	HUE_GREEN = 96,
	HUE_AQUA = 128,
	HUE_BLUE = 160,
	HUE_PURPLE = 192,
	HUE_PINK = 224
} HSVHue;


