#include <cbuffer.h>

void init_cbuffer(struct cbuffer *b) {
	b -> count = 0;
	b -> head = b -> tail = b -> buffer;
}

int cqueue_push(struct cbuffer *b, char value) {
	if (b -> tail == b -> head) {
		return 0;
	}

	b -> count++;
	*(b -> tail) = value;

	b -> tail++;
	if (b -> tail == &(b -> buffer[CBUFFER_SIZE]))
		b -> tail = b -> buffer;
	return 1;
}

int cqueue_empty(struct cbuffer *b) {
	return b -> count == 0;
}

int cqueue_full(struct cbuffer *b) {
	return b -> count == CBUFFER_SIZE;
}

char cqueue_front(struct cbuffer *b) {
	return *(b -> head);
}

char cqueue_pop(struct cbuffer *b) {
	char value = *(b -> head);
	if (b -> head != b -> tail) {
		b -> count--;
		b -> head++;
		if (b -> head == &(b -> buffer[CBUFFER_SIZE]))
			b -> head = b -> buffer;
	}
	return *(b -> head);
}
