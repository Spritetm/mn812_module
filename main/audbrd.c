#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "audbrd_bus.h"
#include "audbrd_chardisp.h"
#include "audbrd.h"
#include "font-5x7.h"

static uint16_t btn_led_state[8]={0xffff, 0};
static uint16_t scancode_old=0;
typedef struct {
	int min;
	int max;
	int val;
} rotary_t;
static rotary_t rotary[16];

static SemaphoreHandle_t mutex;

void audbrd_chardisp_set(int pos, unsigned char *c) {
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


static void send_rotaryled_state(int i) {
	int v=((rotary[i].val-rotary[i].min)*15)/(rotary[i].max-rotary[i].min);
	uint16_t b=0xffff>>(15-v);
	audbrd_bus_write(AUDBRD_REG_ROTARY_LED(i), b);
}

static void send_btnled_state(int i) {
	audbrd_bus_write(AUDBRD_REG_BTN_LED(i), btn_led_state[i]);
}

static void audbrd_task(void *param) {
	audbrd_evt_cb_t cb=(audbrd_evt_cb_t)param;
	xSemaphoreTake(mutex, portMAX_DELAY);
	//un-reset btn controller
	audbrd_bus_write(AUDBRD_REG_BTN_CTL, 0x8000);
	for (int i=0; i<16; i++) send_rotaryled_state(i);
	for (int i=0; i<8; i++) send_btnled_state(i);
	for (int i=0; i<64; i++) audbrd_chardisp_set_bitmap(i, &font_data[(' ')*5]);
	xSemaphoreGive(mutex);
	while(1) {
		xSemaphoreTake(mutex, portMAX_DELAY);
		while(1) {
			uint16_t scancode=audbrd_bus_read(AUDBRD_REG_BTN_CTL);
			if (scancode==scancode_old) break;
			cb(AUDBRD_EVT_BTN, scancode&0x7F, (scancode&0x80)?0:1);
			scancode_old=scancode;
		}
		for (int r=0; r<15; r++) {
			int16_t rotval=audbrd_bus_read(AUDBRD_REG_ROTARY_CNT(r));
			if (rotval!=0) {
				rotary[r].val+=rotval;
				if (rotary[r].val>=rotary[r].max) rotary[r].val=rotary[r].max;
				if (rotary[r].val<=rotary[r].min) rotary[r].val=rotary[r].min;
				send_rotaryled_state(r);
				cb(AUDBRD_EVT_ROTARY, r, rotary[r].val);
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
