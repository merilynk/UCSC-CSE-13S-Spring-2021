// Queue
// Merilyn Kuo
// CSE 13S Spring 2021

// Code from Assignment 3 PDF
struct Queue {
    uint32_t head;  // Index of start of queue
    uint32_t tail;  // Index of end of queue
    uint32_t size;  // Number of elements in queue
    uint32_t capacity;  // max size of queue
    int64_t *items;  // Holds the items
}

// Code based on stack constructor from Assignment 3 PDF
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
	q->head = 0;
	q->tail = 0;
	q->capacity = capacity;
	q->items = (int *) calloc(capacity, sizeof(int));
	if (!q->items) {
	    free(q);
	    q = NULL;
	}
    }
    return q;
}

void queue_delete(Queue **q) {
    if ((*q) && (*q)->items) {
	free((*q)->items);
	free(*q);
	*q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    return (*q)->tail == 0;
}

bool queue_full(Queue *q) {
    return (*q)->size == (*q)->capacity;
}

uint32_t queue_size(Queue *q) {
    return (*q)->size;
}

// Code for enqueue and dequeue was referenced from Sahiti's section.

bool enqueue(Queue *q, int64_t x) {
    if ((*q)->size == (*q)->capacity) {
	return false
    }
    (*q)->item[(*q)->tail] = x;
    (*q)->tail += 1;
    (*q)->size += 1;
    return true;
}

bool dequeue(Queue *q, int65 *x) {
    if((*q)->tail == 0) {
	return false;
    }
    (*q)->size -= 1;
    *x = (*q)->items[(*q)->head];
    (*q)->head += 1;
    return true;
}

void queue_print(Queue *q) {
    printf("%q\n", *q);
}
