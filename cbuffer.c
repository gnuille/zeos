#include <cbuffer.h>

void init_cbuffer(struct cbuffer *b) {
	b -> count = 0;
	b -> head = b -> tail = b -> buffer;
}

int cbuffer_push(struct cbuffer *b, char value) {
	if (b -> count == CBUFFER_SIZE) {
		return 0;
	}

	b -> count++;
	*(b -> tail) = value;

	b -> tail++;
	if (b -> tail == &(b -> buffer[CBUFFER_SIZE]))
		b -> tail = b -> buffer;
	return 1;
}

int cbuffer_empty(struct cbuffer *b) {
	return b -> count == 0;
}

int cbuffer_full(struct cbuffer *b) {
	return b -> count == CBUFFER_SIZE;
}

char cbuffer_front(struct cbuffer *b) {
	return *(b -> head);
}

char cbuffer_pop(struct cbuffer *b) {
	char value = *(b -> head);
	if (b -> head != b -> tail) {
		b -> count--;
		b -> head++;
		if (b -> head == &(b -> buffer[CBUFFER_SIZE]))
			b -> head = b -> buffer;
	}
	return value;
}

