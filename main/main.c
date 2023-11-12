//Simple demo program
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "audbrd.h"

void ev_cb(int type, int which, int val) {
	printf("Ev %d which %d val %d\n", type, which, val);
	if (type==AUDBRD_EVT_BTN && val) {
		int rg=audbrd_btn_led_get(which);
		rg=(rg+1)&3;
		audbrd_btn_led_set(which, rg);
	}
	if (type==AUDBRD_EVT_ROTARY) {
		char buf[32];
		sprintf(buf, "%d%%", val);
		audbrd_chardisp_set(which, buf);
	}
}

void app_main(void) {
	audbrd_init(ev_cb);
}
