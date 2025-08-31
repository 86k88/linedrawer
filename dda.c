#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef void (*dda_callback_t)(int32_t x, int32_t y, void *context);

typedef struct
{

    int32_t x0, y0, x1, y1;
    int32_t dx, dy, sx, sy, acc_err;
    bool is_running;


    dda_callback_t put_pixel;
    void *context;
} dda_t;


void dda_init(dda_t *dda, dda_callback_t pixel_cb, void *context)
{
    dda->put_pixel = pixel_cb;
    dda->context = context;
    dda->is_running = false;

}

void dda_begin(dda_t *dda, int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    dda->x0 = x0;
    dda->y0 = y0;
    dda->x1 = x1;
    dda->y1 = y1;

    dda->dx = labs(x1 - x0);
    dda->dy = labs(y1 - y0);
    dda->sx = (x0 < x1) ? 1 : -1;
    dda->sy = (y0 < y1) ? 1 : -1;
    dda->acc_err = dda->dx - dda->dy;

    dda->is_running = true;
}

/* returns false when done or when dda_begin() is not called before running dda_step(), true if still running */
bool dda_step(dda_t *dda)
{
    if (!dda->is_running) return false;

    // Plot current pixel
    dda->put_pixel(dda->x0, dda->y0, dda->context);

    // Check end condition
    if (dda->x0 == dda->x1 && dda->y0 == dda->y1) {
        dda->is_running = false;
        return false;
    }

    int e2 = 2 * dda->acc_err;
    if (e2 > -dda->dy) {
        dda->acc_err -= dda->dy;
        dda->x0 += dda->sx;
    }
    if (e2 < dda->dx) {
        dda->acc_err += dda->dx;
        dda->y0 += dda->sy;
    }

    return true;

}
