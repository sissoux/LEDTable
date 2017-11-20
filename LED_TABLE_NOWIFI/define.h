#include "Arduino.h"

#ifndef define_h
#define define_h

#define ROW_COUNT 20
#define COLUMN_COUNT 10

#define N_ROW ROW_COUNT
#define N_COLUMN COLUMN_COUNT

#define FANCY_START

#define NUM_LEDS 200
#define DATA_PIN 13
#define CLOCK_PIN 14
#define LED_TYPE APA102

#define REFRESH_RATE 20    // in ms
#define INPUT_REFRESH_RATE 20
#define BLINK_RATE 500
#define TIME_REFRESH_RATE 500 //ms
#define DISPLAY_REFRESH_RATE 20 //ms (50fps)
#define ONE_SECOND 1000 // to Reset each second
#define NTP_TIMEOUT 5000 // 
#define RETRIES_AT_BOOT 5
#define WIFI_CONNECT_TIMEOUT 60000
#define DEFAULT_RESYNC_PERIOD 3600000UL //Resync with NTP each hour
#define CONTROLLER_REFRESH_RATE 5
#define START_ANIMATION_DURATION 10000 / DISPLAY_REFRESH_RATE

#define R_SENSOR_THRESHOLD 600
#define L_SENSOR_THRESHOLD 600
#define DEBOUNCE_DELAY 200
#define R_FLAG_MASK 0b00000001
#define L_FLAG_MASK 0b00000010

#define NUMBER_OF_STATIC_COLORS 1

#define TIME_HEADER  "T"   // Header tag for serial time sync message

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#endif
