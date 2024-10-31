#ifndef __SC_COMMON_H
#define __SC_COMMON_H

struct point {
	int x, y;
};

struct color_painter {
	unsigned long foreground;
	unsigned long background;
};

static inline int point_init(struct point *self, int x, int y) {
	self->x = x;
	self->y = y;
	return 0;
};

static inline int color_painter_init(struct color_painter *self, unsigned long fg, unsigned long bg) {
	self->foreground = fg;
	self->background = bg;
	return 0;
}

int delay(int ms);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define UNIT_VAL(a) ((a) < 0 ? -1 : 1)
#define SQUARE(a) ((a) * (a))

#endif
