#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"


static const int d_pins[16]={14, 13, 12, 11, 10, 9, 46, 3, 8, 18, 17, 16, 15, 7, 6, 5};
static const int a_pins[8]={21, 47, 48, 45, 35, 36, 37, 38};
static const int ctl_pins[6]={-1, 39, 40, 41, 42, 2};

static void pins_setup(const int *pins, int ct) {
	gpio_config_t cfg={
		.mode=GPIO_MODE_INPUT,
		.pull_down_en=GPIO_PULLDOWN_ENABLE,
	};
	for (int i=0; i<ct; i++) {
		if (pins[i]>=0) {
			cfg.pin_bit_mask|=(1ULL<<pins[i]);
		}
	}
	gpio_config(&cfg);
}

static void pins_dir_set(const int *pins, int ct, gpio_mode_t mode) {
	for (int i=0; i<ct; i++) {
		if (pins[i]>=0) {
			gpio_set_direction(pins[i], mode);
		}
	}
}

static void pins_dir_in(const int *pins, int ct) {
	pins_dir_set(pins, ct, GPIO_MODE_INPUT);
}

static void pins_dir_out(const int *pins, int ct) {
	pins_dir_set(pins, ct, GPIO_MODE_OUTPUT);
}

static void pins_set_out(const int *pins, int ct, int v) {
	for (int i=0; i<ct; i++) {
		if (pins[i]>=0) { 
			gpio_set_level(pins[i], v&(1<<i));
		}
	}
}

static int pins_get_in(const int *pins, int ct) {
	int r=0;
	for (int i=0; i<ct; i++) {
		r|=gpio_get_level(pins[i])?(1<<i):0;
	}
	return r;
}

static int data_pins_are_output=0;

void audbrd_bus_write(uint8_t address, uint16_t data) {
	if (!data_pins_are_output) {
		pins_dir_out(d_pins, 16);
		data_pins_are_output=1;
	}
	pins_set_out(a_pins, 8, address);
	pins_set_out(d_pins, 16, data);
	pins_set_out(ctl_pins, 6, 0x30);
	pins_set_out(ctl_pins, 6, 0x3F);
}

uint16_t audbrd_bus_read(uint8_t address) {
	if (data_pins_are_output) {
		pins_dir_in(d_pins, 16);
		data_pins_are_output=0;
	}
	pins_set_out(a_pins, 8, address);
	pins_set_out(ctl_pins, 6, 0x35);
	uint16_t r=pins_get_in(d_pins, 16);
	pins_set_out(ctl_pins, 6, 0x3F);
	return r;
}


void audbrd_bus_setup() {
	//We use the LEDC to generate an 8MHz signal as the clock for the board.
	ledc_timer_config_t ledc_timer = {
		.speed_mode		  = LEDC_LOW_SPEED_MODE,
		.duty_resolution  = LEDC_TIMER_1_BIT,
		.timer_num		  = LEDC_TIMER_0,
		.freq_hz		  = 8000000,
		.clk_cfg		  = LEDC_AUTO_CLK
	};
	ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
	ledc_channel_config_t ledc_channel = {
		.speed_mode		= LEDC_LOW_SPEED_MODE,
		.channel		= LEDC_CHANNEL_0,
		.timer_sel		= LEDC_TIMER_0,
		.intr_type		= LEDC_INTR_DISABLE,
		.gpio_num		= 0,
		.duty			= 1,
		.hpoint			= 0
	};
	ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

	int meas_pin=1;
	pins_setup(a_pins, 8);
	pins_setup(d_pins, 16);
	pins_setup(ctl_pins, 6);

	pins_dir_out(a_pins, 8);
	pins_dir_in(d_pins, 16);
	pins_dir_out(ctl_pins, 6);

	pins_set_out(ctl_pins, 6, 0x3F);
}
