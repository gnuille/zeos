
#define CBUFFER_SIZE 443

struct cbuffer{
	char *head;			// pointer to the begin of the buffer
	char *tail;			// pointer to the end of the buffer

	int count;			// number of unread values

	char buffer[CBUFFER_SIZE];	// vector of chars which stores the buffer
};

/**
 * Pre: The struct cbuffer that b is pointing is uninicialized.
 * Post:The struct cbuffer pointed by b is inizialized with 0 values stored.
 */
void init_cbuffer(struct cbuffer *b);

int cqueue_push(struct cbuffer *b, char value);

int cqueue_empty(struct cbuffer *b);

int cqueue_full(struct cbuffer *b);

char cqueue_front(struct cbuffer *b);

char cqueue_pop(struct cbuffer *b);
