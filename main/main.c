#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "audbrd_bus.h"
#include "audbrd_chardisp.h"


void app_main(void) {
	audbrd_bus_setup();
	audbrd_chardisp_init();
	for (int i=0; i<64; i++) audbrd_chardisp_set_char(i, 33+i);
}
