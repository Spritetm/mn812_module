#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "audbrd.h"

void ev_cb(int type, int which, int val) {
	printf("Ev %d which %d val %d\n", type, which, val);
}

void app_main(void) {
	audbrd_init(ev_cb);
}
