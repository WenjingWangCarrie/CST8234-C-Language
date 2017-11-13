/*
 * Name:      Ayala_particles.c
 * Title:     A particle system
 * Descripts: Design, code and test a simple implementation of linked lists
 * Author:    Wenjing Wang
 * Date:      2016-11-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Wang_particles.h"
#include "Wang_particle.h"

struct particle *head = NULL;

int main(int argc, char *argv[]) {
    clock_t start_t;
    clock_t end_t;
    long initial_particles;
    long i;

	if (argc != 2) {
		printUsage(argv[0]);
		exit(EXIT_FAILURE);
	}

    initial_particles = atol(argv[1]);

    if (initial_particles <= 0) {
        printf("The argument must be a positive integer.\n");

		printUsage(argv[0]);
		exit(EXIT_FAILURE);
    }

    /* Add particles to the system. */
    start_t = clock();
    for (i = 0; i < initial_particles; i++) {
        particle_add(&head);
    }
    end_t = clock();

    printf("%ld particles have been created.\n", initial_particles);
    reportTime(start_t, end_t, "creation");

    /* Update the particle system. */
    start_t = clock();
    particle_update(&head);
    end_t = clock();

    reportTime(start_t, end_t, "animation");

    /* Finally destroy the particle system. */
    start_t = clock();
    particle_destroy(&head);
    end_t = clock();

    reportTime(start_t, end_t, "destroy");

    return EXIT_SUCCESS;
}

void printUsage(const char *pgm) {
    printf("Usage: %s number-of-particles\n", pgm);
}

void reportTime(clock_t start_t, clock_t end_t, const char *type) {
    float total_t = ((float)(end_t - start_t) / CLOCKS_PER_SEC) * 1000;
    printf("Total time taken by %s in milliseconds: %d\n", type, (int)total_t);
}
