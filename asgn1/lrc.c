// Merilyn Kuo
// CSE 13S
// Spring 2021

#include "philos.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#define FUNDS     3  // Amount of money each player starts with.
#define MAX_ROLLS 3  // Maximum number of dice a player can do in their turn.

// The following two functions is code provided in the assignment 1 PDF.

//static inline uint8_t left(uint8_t pos, uint8_t players) {

	// Returns the position of the player to the left.
	// pos:     The position of the current player.
	// players: The number of players in the game.

//	return ((pos + players - 1) % players);
//}

//static inline uint8_t right(uint8_t pos, uint8_t players) {

	// Returns the position of the player to the right.
	// pos:    The postition of the current player.
	// playes: The number f players in the game.

//	return ((pos + 1) % players);
//}

int main(void) {

	uint32_t bank[] = { FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS };
	int32_t seed, players;

	// The following code for taking user inputs was based off of vampires.c posted on Piazza.

	printf("Random seed: ");
	if ((scanf("%d", &seed) < 1) || seed < 1) {
	    fprintf(stderr, "Pseudorandom seed must be non-negative (%d).\n", seed);
	    return 1;
	}
	srandom(seed); // Set starting point for random number generator

	printf("How many players? ");
	if ((scanf("%d", &players) < 1) || players < 1 || players > 14) {
	    fprintf(stderr, "Number of players must be from 1 to 14.\n");
	    return 1;
	}

	uint32_t active = players;  // Number of players that have funds in their bank

	for (int32_t p = 0; p < players; p += 1) {

	    if (active == 1){
		break;  // Exit loop if only 1 active player
	    }

	    if (bank[p] == 0) {
		continue;  // Continue to next player if current player has no money
	    }

	    uint32_t dice = bank[p];  // Number of rolls player gets is based on their funds
	    if (dice > 3) {
		dice = MAX_ROLLS;  // Max number of rolls player can have is three
	    }

	    for (uint32_t r = dice; r > 0; r -= 1) {
		int roll = random() % 6;
		printf("%d", roll);
	    }

	}
}
