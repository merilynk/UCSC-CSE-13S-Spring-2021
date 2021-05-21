// Merilyn Kuo
// CSE 13S Spring 2021
// io.c

#include "io.h"
#include "code.h"

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0;
    int b;
    while (total < nbytes && (b = read(infile, buf + total, nbytes - total) > 0)) {
	total += b;
    }
    if (b < 0) {
	return b;
    }
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int b;
    while (total < nbytes && (b = write(outfile, buf + total, nbytes - total) > 0)) {
	total += b;
    }
    if (b < 0) {
	return b;
    }
    return total;
}

static uint8_t buffer[BLOCK];
static uint64_t i = 0;
static uint32_t loaded = 0;

bool read_bit(int infile, uint8_t *bit) {
    if (loaded == 0) {
	loaded = read_bytes(infile, buffer, BLOCK);
	i = 0;
    }
    if (i < loaded * 8) {
	*bit = (buffer[i / 8] >> (i % 8)) & 1;
	i += 1;
    }
    if (i == loaded * 8) {
	loaded = read_bytes(infile, buffer, BLOCK);
	i = 0;
	if (loaded <= 0) {
	    return false;
	}
    }
    return true;
}

static uint8_t w_buffer[BLOCK];
static int buffer_index = 0;

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i += 1) {
	if (c->bits[i] == 1) {
	    w_buffer[i / 8] |= (1 << (i % 8));
	}
	else {
	    w_buffer[i / 8] &= ~(1 << (i % 8));
	}
	buffer_index += 1;
	if (buffer_index == 8 * BLOCK) {
	    write_bytes(outfile, w_buffer, BLOCK);
	    buffer_index = 0;
	}
    }
    return;
}

void flush_codes(int outfile) {
    if (buffer_index > 0) {
	if (buffer_index % 8 != 0) {
	    w_buffer[buffer_index / 8] &= (0xFF >> (8 - buffer_index % 8));  // zero out rest of bits
	    buffer_index = buffer_index / 8 + 1;
	}
	else {
	    buffer_index /= 8;
	}
	write_bytes(outfile, w_buffer, buffer_index);
    }
return;
}

