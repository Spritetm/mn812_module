/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "font-5x7.h"

extern const uint8_t audsch_bit_start[] asm("_binary_audsch_bit_start");
extern const uint8_t audsch_bit_end[] asm("_binary_audsch_bit_end");

static const int d_pins[16]={14, 13, 12, 11, 10, 9, 46, 3, 8, 18, 17, 16, 15, 7, 6, 5};
static const int a_pins[8]={21, 47, 48, 45, 35, 36, 37, 38};
static const int ctl_pins[6]={-1, 39, 40, 41, 42, 2};

void pins_dir_in(const int *pins, int ct) {
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

void pins_dir_out(const int *pins, int ct) {
	gpio_config_t cfg={
		.mode=GPIO_MODE_OUTPUT,
	};
	for (int i=0; i<ct; i++) {
		if (pins[i]>=0) {
			cfg.pin_bit_mask|=(1ULL<<pins[i]);
		}
	}
	gpio_config(&cfg);
}

void pins_set_out(const int *pins, int ct, int v) {
	for (int i=0; i<ct; i++) {
		if (pins[i]>=0) { 
			gpio_set_level(pins[i], v&(1<<i));
		}
	}
}

int pins_get_in(const int *pins, int ct) {
	int r=0;
	for (int i=0; i<ct; i++) {
		r|=gpio_get_level(pins[i])?(1<<i):0;
	}
	return r;
}




//note: needs to be sent MSB-first, data valid on raising edge of clk
void fpga_config() {
	const uint8_t *p=audsch_bit_start;
	pins_dir_out(d_pins, 16);
	//skip to sync
	while (!(p[0]==0xff && p[1]==0x20)) p++;

	//reset fpga
	pins_set_out(a_pins, 8, 0xF2);
	pins_set_out(d_pins, 16, 0);
	pins_set_out(ctl_pins, 6, 0x30);
	pins_set_out(ctl_pins, 6, 0x3F);

	while (p!=audsch_bit_end) {
		for (int bit=0x80; bit!=0; bit=bit>>1) {
//		for (int bit=1; bit!=0x100; bit=bit<<1) {
			pins_set_out(a_pins, 8, 0xF0);
			pins_set_out(d_pins, 16, ((*p)&bit)?0x01:0x00);
			pins_set_out(ctl_pins, 6, 0x30);
			pins_set_out(ctl_pins, 6, 0x3F);
			pins_set_out(a_pins, 8, 0xF1);
			pins_set_out(ctl_pins, 6, 0x30);
			pins_set_out(ctl_pins, 6, 0x3F);
		}
		p++;
	}
	for (int i=0; i<32; i++) {
		pins_set_out(a_pins, 8, 0xF0);
		pins_set_out(ctl_pins, 6, 0x30);
		pins_set_out(ctl_pins, 6, 0x3F);
		pins_set_out(a_pins, 8, 0xF1);
		pins_set_out(ctl_pins, 6, 0x30);
		pins_set_out(ctl_pins, 6, 0x3F);
	}
}


void chardisp_set_char(int pos, unsigned char *v) {
	pins_set_out(a_pins, 8, 0x8);
	pins_set_out(d_pins, 16, pos);
	pins_set_out(ctl_pins, 6, 0x30);
	pins_set_out(ctl_pins, 6, 0x3F);
	
	for (int i=0; i<5; i++) {
		pins_set_out(a_pins, 8, i);
		pins_set_out(d_pins, 16, v[i]);
		pins_set_out(ctl_pins, 6, 0x30);
		pins_set_out(ctl_pins, 6, 0x3F);
	}

}



void app_main(void) {

	// Prepare and then apply the LEDC PWM timer configuration
	ledc_timer_config_t ledc_timer = {
		.speed_mode		  = LEDC_LOW_SPEED_MODE,
		.duty_resolution  = LEDC_TIMER_1_BIT,
		.timer_num		  = LEDC_TIMER_0,
		.freq_hz		  = 8000000,
		.clk_cfg		  = LEDC_AUTO_CLK
	};
	ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

	// Prepare and then apply the LEDC PWM channel configuration
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
	pins_dir_out(a_pins, 8);
	pins_dir_out(ctl_pins, 6);

	fpga_config();

	for (int i=0; i<64; i++) {
		chardisp_set_char(i, &font_data[(i+33)*5]);
	}

	pins_dir_in(d_pins, 16);

#if 0
	for (int a=0; a<256; a++) {
		pins_set_out(a_pins, 8, a);
		for (int c=0; c<64; c++) {
			pins_set_out(ctl_pins, 6, c);
			int r=pins_get_in(d_pins, 16);
			if (r!=0) printf("A=%02X ctl=%x (%d%d%d%d%d%d) d=%04X\n", a, c,
				(c&0x20)?1:0,(c&0x10)?1:0,(c&0x8)?1:0,(c&0x4)?1:0,(c&0x2)?1:0,(c&0x1)?1:0 , r);
			pins_set_out(ctl_pins, 6, 0x3F);
		}
	}
#endif

#if 0
	pins_dir_in(&meas_pin, 1);

	pins_dir_out(d_pins, 16);
	int ex=1;
	for (int a=0; a<256; a++) {
		pins_set_out(a_pins, 8, a);
		for (int c=0; c<64; c++) {
			pins_set_out(d_pins, 16, ex?0xffff:0x0FFF);
			pins_set_out(ctl_pins, 6, c);
			pins_set_out(ctl_pins, 6, 0x3F);
			int r=gpio_get_level(meas_pin);
			if (r==ex) {
				printf("A=%02X ctl=%d%d%d%d%d%d l=%d\n", a, 
					(c&0x20)?1:0,(c&0x10)?1:0,(c&0x8)?1:0,(c&0x4)?1:0,(c&0x2)?1:0,(c&0x1)?1:0, r);
				ex=ex?0:1;
			}
/*
			pins_set_out(ctl_pins, 6, 0x3F);
			pins_set_out(ctl_pins, 6, 0x1F);
			pins_set_out(ctl_pins, 6, 0x3F);
			pins_set_out(ctl_pins, 6, 0x1F);
			pins_set_out(ctl_pins, 6, 0x3F);
			pins_set_out(ctl_pins, 6, 0x1F);
			pins_set_out(ctl_pins, 6, 0x3F);
			pins_set_out(ctl_pins, 6, 0x1F);
			pins_set_out(ctl_pins, 6, 0x3F);
			pins_set_out(ctl_pins, 6, 0x1F);
*/
		}
	}
	
/*
	while(1) {
		pins_set_out(ctl_pins, 6, 0x3F);
		pins_set_out(ctl_pins, 6, 0x2F);
		vTaskDelay(1);
	}
*/

#endif
	pins_dir_out(d_pins, 16);
	int a=0;
	int d=0x5555;
	int write=1;
	while(1) {
		int v;
		do {
			vTaskDelay(1);
//			pins_set_out(ctl_pins, 6, 0x3F);
//			pins_set_out(ctl_pins, 6, 0x3E);
			v=getchar();
			if (v==']') a++;
			if (v=='[') a--;
			if (v>='0' && v<='9') d=(d<<4)|(v-'0');
			if (v>='a' && v<='f') d=(d<<4)|(v-'a'+10);
			if (v=='r') {
				write=0;
				pins_dir_in(d_pins, 16);
			}
			if (v=='w') {
				write=1;
				pins_dir_out(d_pins, 16);
			}
			d=d&0xffff;
			a=a&0xff;
		} while (v<=0);
		pins_set_out(a_pins, 8, a);
		if (v=='x') {
			for (int i=0; i<65535; i++) {
				pins_set_out(a_pins, 8, rand()&0xff);
				pins_set_out(d_pins, 16, rand()&0xffff);
//				pins_set_out(ctl_pins, 6, 0x30);
//				pins_set_out(ctl_pins, 6, 0x3F);
				pins_set_out(ctl_pins, 6, rand());
			}
			printf("A %x D %x meas %d\n", a, d, gpio_get_level(meas_pin));
		} else if (v=='k') {
			do {
				v=getchar();
				pins_set_out(a_pins, 8, a);
				pins_set_out(ctl_pins, 6, 0x35);
				int r=pins_get_in(d_pins, 16);
				pins_set_out(ctl_pins, 6, 0x3F);
				printf("A %x D %x\n", a, r);
			} while (v<=0);
		} else if (write) {
			pins_set_out(d_pins, 16, d);
			vTaskDelay(1);
			pins_set_out(ctl_pins, 6, 0x30);
			vTaskDelay(1);
			pins_set_out(ctl_pins, 6, 0x3F);
			printf("A %x D %x meas %d\n", a, d, gpio_get_level(meas_pin));
		} else {
			pins_set_out(a_pins, 8, a);
			pins_set_out(ctl_pins, 6, 0x35);
			int r=pins_get_in(d_pins, 16);
			pins_set_out(ctl_pins, 6, 0x3F);
			printf("A %x D %x meas %d\n", a, r, gpio_get_level(meas_pin));
		}
	}

	pins_dir_in(d_pins, 16);
}
