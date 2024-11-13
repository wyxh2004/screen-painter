#include "sc_point_iterator.h"
#include "sc_common.h"

int line_p_iter_next(struct line_point_iter *self, struct point *result);
int rect_p_iter_next(struct rect_point_iter *self, struct point *result);
int circle_p_iter_next(struct circle_point_iter *self, struct point *buffer);

static struct point_iter_i line_p_interface = {
	.next = (point_iter_next_fn)line_p_iter_next,
};

int line_p_iter_init(struct line_point_iter *self, struct point start, struct point end) {
	self->iterator = &line_p_interface;
	self->cursor = start;
	self->destination = end;
	self->delta.x = end.x - start.x;
	self->delta.y = end.y - start.y;
	self->step.x = UNIT_VAL(self->delta.x);
	self->step.y = UNIT_VAL(self->delta.y);
	self->acc.x = 0;
	self->acc.y = 0;
	self->distance = MAX(self->delta.x, self->delta.y);
	self->count = 0;

	return 0;
}

int line_p_iter_next(struct line_point_iter *self, struct point *result) {
	*result = self->cursor;
	self->acc.x += self->delta.x;
	if (self->acc.x >= self->distance) {
		self->acc.x -= self->distance;
		self->cursor.x += self->step.x;
	}
	if (self->acc.y >= self->distance) {
		self->acc.y -= self->distance;
		self->cursor.y += self->step.y;
	}
	if (self->count++ < self->distance)
		return 0;
	else
		return 1;
}

static struct point_iter_i rect_p_interface = {
	.next = (point_iter_next_fn)rect_p_iter_next,
};

int rect_p_iter_init(struct rect_point_iter *self, struct point start, struct point end) {
	self->iterator = &rect_p_interface;
	point_init(&self->start, MIN(start.x, end.x), MIN(start.y, end.y));
	point_init(&self->end, MAX(start.x, end.x), MAX(start.y, end.y));
	self->cursor = start;

	return 0;
}

int rect_p_iter_next(struct rect_point_iter *self, struct point *result) {
	*result = self->cursor;
	self->cursor.x++;
	if (self->cursor.x > self->end.x + 1) {
		if (self->cursor.y < self->end.y)
			return 1;
		self->cursor.x = 0;
		self->cursor.y++;
	}

	return 0;
}

static struct point_iter_i circle_p_interface = {
	.next = (point_iter_next_fn)circle_p_iter_next,
};

int circle_p_iter_init(struct circle_point_iter *self, struct point center, int radius) {
	self->iterator = &circle_p_interface;
	self->center = center;
	self->radius = radius;
	self->px = radius;
	self->py = 0;
	return 0;
}

int circle_p_iter_next(struct circle_point_iter *self, struct point *buffer) {
	if (self->py > self->px)
		return 1;
	buffer[0].x = self->center.x - self->px;
	buffer[0].y = self->center.y - self->py;
	buffer[1].x = self->center.x - self->px;
	buffer[1].y = self->center.y + self->py;
	buffer[2].x = self->center.x + self->px;
	buffer[2].y = self->center.y - self->py;
	buffer[3].x = self->center.x + self->px;
	buffer[3].y = self->center.y + self->py;

	buffer[4].x = self->center.x - self->py;
	buffer[4].y = self->center.y - self->px;
	buffer[5].x = self->center.x - self->py;
	buffer[5].y = self->center.y + self->px;
	buffer[6].x = self->center.x + self->py;
	buffer[6].y = self->center.y - self->px;
	buffer[7].x = self->center.x + self->py;
	buffer[7].y = self->center.y + self->px;

	self->py++;

	if ((SQUARE(self->py) + SQUARE(self->px)) > SQUARE(self->radius))
		self->px--;

	return 0;
}