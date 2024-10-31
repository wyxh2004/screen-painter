#ifndef __SC_PAINTER_H
#define __SC_PAINTER_H

#include "sc_common.h"

typedef int (*drawing_draw_point_fn_t)(void *screen, struct point p, unsigned long color);
typedef int (*drawing_fill_fn_t)(void *screen, struct point p1, struct point p2, unsigned long color);
typedef int (*drawing_clear_fn_t)(void *screen, unsigned long color);
typedef int (*drawing_size_fn_t)(void *screen, struct point p);
typedef int (*drawing_flush_fn_t)(void *screen);

struct drawing_i {
  drawing_draw_point_fn_t draw_point;
  drawing_fill_fn_t fill;
  drawing_clear_fn_t clear;
  drawing_size_fn_t size;
  drawing_flush_fn_t flush;
};

struct sc_painter {
  struct drawing_i **drawing_board;
};

int sc_painter_init(struct sc_painter *self, struct drawing_i **drawing_board);
int sc_painter_draw_point(struct sc_painter *self, struct point p, unsigned long color);
int sc_painter_size(struct sc_painter *self, struct point *p);
int sc_painter_clear(struct sc_painter *self, unsigned long color);
int sc_painter_flush(struct sc_painter *self);

int sc_painter_draw_line(struct sc_painter *self, struct point p1, struct point p2, unsigned long color);
int sc_painter_draw_rect(struct sc_painter *self, struct point p1, struct point p2, unsigned long color);
int sc_painter_draw_circle(struct sc_painter *self, struct point p, int radius, unsigned long color);
int sc_painter_draw_bezier(struct sc_painter *self, struct point start, struct point end, struct point control, unsigned long color);

#endif