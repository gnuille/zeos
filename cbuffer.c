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

int cbuffer_size(struct cbuffer *b) {
    return b -> count;
}

int cbuffer_full(struct cbuffer *b) {
    return b -> count == CBUFFER_SIZE;
}

char cbuffer_front(struct cbuffer *b) {
    return *(b -> head);
}

int cbuffer_read(struct cbuffer *b, char* buff, int size){
    char *act;
    int i;
    for (
            i = 0, act = b -> head;
            act != &(b -> buffer[CBUFFER_SIZE]) && act != (b -> tail) && i < size && i < CBUFFER_SIZE;
            act++, i++
        ) buff[i] = *act;
    for (
            act = b -> buffer;
            act != (b -> tail) && i < size && i < CBUFFER_SIZE;
            act++, i++
        ) buff[i] = *act;
    b -> head = act;
    b -> count -= i;
    return i;
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

