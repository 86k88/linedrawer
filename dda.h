#ifndef DDA_H
#define DDA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*dda_callback_t)(int32_t x, int32_t y, void *context);

typedef struct {
    int32_t x0, y0, x1, y1;
    int32_t dx, dy;
    int32_t sx, sy;
    int32_t acc_err;
    bool is_running;
    dda_callback_t put_pixel;
    void *context;
} dda_t;

void dda_init(dda_t *dda, dda_callback_t pixel_cb, void *context);
void dda_begin(dda_t *dda, int32_t x0, int32_t y0, int32_t x1, int32_t y1);
bool dda_step(dda_t *dda);

#ifdef __cplusplus
}
#endif

#endif
