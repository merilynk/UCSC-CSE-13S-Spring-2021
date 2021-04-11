// Merilyn Kuo
// CSE 13S
// Spring 2021

#include "philos.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNDS     3 // Amount of money each player starts with.
#define MAX_ROLLS 3 // Maximum number of dice a player can do in their turn.
#define PHILOS    14 // Largest number of players that can be in the game is the length of philos[]

// The following two functions is code provided in the assignment 1 PDF.

// Returns the position of the player to the left.
// pos:     The position of the current player.
// players: The number of players in the game.

static inline uint8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

// Returns the position of the player to the right.
// pos:    The postition of the current player.
// playes: The number f players in the game.

static inline uint8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

int main(void) {

    uint32_t bank[]
        = { FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS, FUNDS };
    int32_t seed, players;
    uint32_t roll, left_player, right_player, pot = 0;

    // Next two lines is code provided in the Assignment 1 PDF.

    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

    // The following code for taking user inputs was based off of vampires.c posted on Piazza.

    printf("Random seed: ");
    if ((scanf("%d", &seed) < 1) || seed < 1) {
        fprintf(stderr, "Pseudorandom seed must be non-negative (%d).\n", seed);
        return 1;
    }
    srandom(seed); // Set starting point for random number generator

    printf("How many players? ");
    if ((scanf("%d", &players) < 1) || players < 1 || players > PHILOS) {
        fprintf(stderr, "Number of players must be from 1 to 14.\n");
        return 1;
    }

    uint32_t active = players; // Number of players that have funds in their bank

    while (active > 1) {

        for (int32_t p = 0; p < players; p += 1) {

            if (active == 1) {
                break; // Exit loop if only 1 active player
            }

            if (bank[p] == 0) {
                continue; // Continue to next player if current player has no money
                printf("%s has no funds.\n", philosophers[p]);
            }

            uint32_t dice = bank[p]; // Number of rolls player gets is based on their funds
            if (dice > 3) {
                dice = 3;
            }

            printf("%s rolls...", philosophers[p]);

            for (uint32_t r = dice; r > 0; r -= 1) {

                roll = random() % 6; // Generate a random number

                if (die[roll] == LEFT) {
                    bank[p] -= 1;

                    if (bank[p] == 0) {
                        active -= 1; // Player is out of the game.
                    }

                    left_player = left(p, players);
                    if (bank[left_player] == 0) {
                        active += 1; // Player is back in the game.
                    }
                    bank[left_player] += 1;
                    printf(" gives $1 to %s", philosophers[left_player]);
                }

                else if (die[roll] == RIGHT) {
                    bank[p] -= 1;

                    if (bank[p] == 0) {
                        active -= 1;
                    }

                    right_player = right(p, players);
                    if (bank[right_player] == 0) {
                        active += 1;
                    }
                    bank[right_player] += 1;
                    printf(" gives $1 to %s", philosophers[right_player]);
                }

                else if (die[roll] == CENTER) {
                    bank[p] -= 1;

                    if (bank[p] == 0) {
                        active -= 1;
                    }
                    pot += 1;
                    printf(" puts $1 in the pot");
                }

                else if (die[roll] == PASS) {
                    printf(" gets a pass");
                }
            }
            printf("\n");
        }
    }

    for (int32_t p = 0; p < players; p += 1) {
        if (bank[p] > 0) {
            printf(
                "%s wins the $%u pot with $%u left in the bank!\n", philosophers[p], pot, bank[p]);
        }
    }
}
