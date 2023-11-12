

#define AUDBRD_EVT_BTN 1
#define AUDBRD_EVT_ROTARY 2

typedef void (*audbrd_evt_cb_t)(int type, int which, int val);

void audbrd_chardisp_set(int pos, unsigned char *c);


void audbrd_init(audbrd_evt_cb_t cb);
