#pragma once

//Callback function for rotary and button events.
#define AUDBRD_EVT_BTN 1
#define AUDBRD_EVT_ROTARY 2
typedef void (*audbrd_evt_cb_t)(int type, int which, int val);

#define AUDBRD_BRIGHT_ROTLEDS 0
#define AUDBRD_BRIGHT_BTNLEDS_RED 1
#define AUDBRD_BRIGHT_BTNLEDS_GREEN 2

//Set one character display (4 characters) to the zero-terminated string in c.
void audbrd_chardisp_set(int pos, char *c);

//brightness 0-255, with 255 being the brightest. `which` is one of AUDBRD_BRIGHT_X
void audbrd_brightness_set(int which, int brightness);

//Get and set a button LED. RG values: 0=off, 1=red, 2=green, 3=orange
int audbrd_btn_led_get(int index);
void audbrd_btn_led_set(int index, int rg);

//Initialize board hardware and specify event callback
void audbrd_init(audbrd_evt_cb_t cb);
