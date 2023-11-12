//Highlevel module interface code
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "audbrd_bus.h"
#include "audbrd_chardisp.h"
#include "audbrd.h"
#include "font-5x7.h"

static uint16_t btn_led_state[8]={0};
static uint16_t scancode_old=0;
typedef struct {
	int min;
	int max;
	int val;
} rotary_t;
static rotary_t rotary[16];

static SemaphoreHandle_t mutex;

void audbrd_chardisp_set(int pos, char *c) {
	xSemaphoreTake(mutex, portMAX_DELAY);
	for (int i=0; i<4; i++) {
		if (*c) {
			audbrd_chardisp_set_bitmap(pos*4+i, &font_data[(*c)*5]);
			c++;
		} else {
			audbrd_chardisp_set_bitmap(pos*4+i, &font_data[(' ')*5]);
		}
	}
	xSemaphoreGive(mutex);
}

void audbrd_brightness_set(int which, int brightness) {
	xSemaphoreTake(mutex, portMAX_DELAY);
	int b=255-brightness;
	if (which==AUDBRD_BRIGHT_ROTLEDS) {
		audbrd_bus_write(AUDBRD_REG_DIM_ROTARYLED1, 0x00);
		audbrd_bus_write(AUDBRD_REG_DIM_ROTARYLED2, b);
	}
	if (which==AUDBRD_BRIGHT_BTNLEDS_RED) audbrd_bus_write(AUDBRD_REG_DIM_BTNLED_RED, b);
	if (which==AUDBRD_BRIGHT_BTNLEDS_GREEN) audbrd_bus_write(AUDBRD_REG_DIM_BTNLED_GREEN, b);
	xSemaphoreGive(mutex);
}



static void send_rotaryled_state(int i) {
	int v=((rotary[i].val-rotary[i].min)*15)/(rotary[i].max-rotary[i].min);
	uint16_t b=0xffff>>(15-v);
	audbrd_bus_write(AUDBRD_REG_ROTARY_LED(i), b);
}

static void send_btnled_state(int i) {
	audbrd_bus_write(AUDBRD_REG_BTN_LED(i), btn_led_state[i]);
}

int audbrd_btn_led_get(int index) {
	int reg=index/8;
	int off=index&7;
	int r=0;
	xSemaphoreTake(mutex, portMAX_DELAY);
	if (btn_led_state[reg]&(1<<off)) r|=1;;
	if (btn_led_state[reg]&(0x100<<off)) r|=2;
	xSemaphoreGive(mutex);
	return r;
}

void audbrd_btn_led_set(int index, int rg) {
	int reg=index/8;
	int off=index&7;
	xSemaphoreTake(mutex, portMAX_DELAY);
	btn_led_state[reg]&=~(0x0101<<off);
	if (rg&1) btn_led_state[reg]|=(1<<off);
	if (rg&2) btn_led_state[reg]|=(0x100<<off);
	send_btnled_state(reg);
	xSemaphoreGive(mutex);
}

static void audbrd_task(void *param) {
	audbrd_evt_cb_t cb=(audbrd_evt_cb_t)param;
	xSemaphoreTake(mutex, portMAX_DELAY);
	//un-reset btn controller
	audbrd_bus_write(AUDBRD_REG_BTN_CTL, 0x8000);
	for (int i=0; i<16; i++) send_rotaryled_state(i);
	for (int i=0; i<8; i++) send_btnled_state(i);
	for (int i=0; i<64; i++) audbrd_chardisp_set_bitmap(i, &font_data[(' ')*5]);
	audbrd_bus_write(AUDBRD_REG_DIM_ROTARYLED1, 0);
	audbrd_bus_write(AUDBRD_REG_DIM_ROTARYLED2, 0);
	audbrd_bus_write(AUDBRD_REG_DIM_BTNLED_RED, 0);
	audbrd_bus_write(AUDBRD_REG_DIM_BTNLED_GREEN, 0);
	xSemaphoreGive(mutex);
	while(1) {
		xSemaphoreTake(mutex, portMAX_DELAY);
		while(1) {
			uint16_t scancode=audbrd_bus_read(AUDBRD_REG_BTN_CTL);
			if (scancode==scancode_old) break;
			xSemaphoreGive(mutex);
			cb(AUDBRD_EVT_BTN, scancode&0x7F, (scancode&0x80)?0:1);
			xSemaphoreTake(mutex, portMAX_DELAY);
			scancode_old=scancode;
		}
		for (int r=0; r<16; r++) {
			int16_t rotval=audbrd_bus_read(AUDBRD_REG_ROTARY_CNT(r));
			if (rotval!=0) {
				rotary[r].val+=rotval;
				if (rotary[r].val>=rotary[r].max) rotary[r].val=rotary[r].max;
				if (rotary[r].val<=rotary[r].min) rotary[r].val=rotary[r].min;
				send_rotaryled_state(r);
				xSemaphoreGive(mutex);
				cb(AUDBRD_EVT_ROTARY, r, rotary[r].val);
				xSemaphoreTake(mutex, portMAX_DELAY);
			}
		}
		xSemaphoreGive(mutex);
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}

void audbrd_init(audbrd_evt_cb_t cb) {
	audbrd_bus_setup();
	audbrd_chardisp_init();
	for (int i=0; i<16; i++) {
		rotary[i].min=0;
		rotary[i].max=100;
		rotary[i].val=0;
	}
	mutex=xSemaphoreCreateMutex();
	xTaskCreate(audbrd_task, "audbrd", 8192, cb, 5, NULL);
}
