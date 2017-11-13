/*
 * Name:      Wang_particles.c
 * Title:     A particle system
 * Descripts: Design, code and test a simple implementation of linked lists
 * Author:    Wenjing Wang
 * Date:      2016-11-17
 */

#include <stdlib.h>
#include "Wang_particles.h"	

/**************************************************************************/
/* Function to initialize a particle                                      */
/**************************************************************************/
int particle_init(struct particle *p) {
    /* Set the color to the very intense red. */
    p->color.r = 1.0;
    p->color.g = 0.0;
    p->color.b = 0.0;
    p->color.a = 1.0;

    /* Set the position. */
    p->pos.x = 0.0;
    p->pos.y = 0.0;
    p->pos.z = 0.0;

    /* Set the move direction to upwards. */
    p->dir.x = 0.0;
    p->dir.y = 1.0;
    p->dir.z = 0.0;

    /* Set the move speed to 5 units. */
    p->spd.x = 5.0;
    p->spd.y = 5.0;
    p->spd.z = 5.0;

    /* Set the life span. */
	p->lifespan = INITIAL_LIFE_SPAN;

    /* Set the size. */
    p->size = PARTICLE_SIZE;

	p->next = NULL;

	return 0;
}

/**************************************************************************/
/* Function to add a particle                                             */
/**************************************************************************/
int particle_add(struct particle **head) {
    struct particle *p = (struct particle *)malloc(sizeof(struct particle));

    if (p == NULL) {
        printf("Particle node creation failed.\n");
        return 1;
    }

    particle_init(p);

    p->next = *head;
    *head = p;

    return 0;
}

/**************************************************************************/
/* Function to remove a particle                                          */
/**************************************************************************/
int particle_remove(struct particle *p, struct particle *prev) {
    if (prev != NULL) {
        prev->next = p->next;
    }

    return 0;
}

/**************************************************************************/
/* Function to free memory used by the dynamic particle linked list       */
/**************************************************************************/
int particle_destroy(struct particle **head) {
    struct particle *p = *head;
    struct particle *temp = NULL;

    while (p != NULL)
    {
        temp = p->next;

        free(p);

        p = temp;
    }

    *head = NULL;

	return 0;
}

/**************************************************************************/
/* Function to update the particles properties                            */
/**************************************************************************/
int particle_update(struct particle **head) {
    struct particle *p = *head;
    struct particle *prev = NULL;
    struct particle *temp = NULL;

    while (p != NULL)
    {
        particle_transform(p);

        /* Remove the particle if its lifespan is 0. */
        if (p->lifespan <= 0) {
            temp = p->next;

            /* Adjust the head if the particle is the first element. */
            if (p == *head) {
                *head = temp;
            }

            particle_remove(p, prev);
            free(p);

            p = temp;
        } else {
            prev = p;
            p = p->next;
        }
    }

	return 0;
}

/**************************************************************************/
/* Function to transform a particle                                       */
/**************************************************************************/
int particle_transform(struct particle *p) {
    /* Update the position to simulate the movement. */
    p->pos.x += p->spd.x * p->dir.x;
    p->pos.y += p->spd.y * p->dir.y;
    p->pos.z += p->spd.y * p->dir.z;

    /* Update the life span. */
    p->lifespan -= DELTA_LIFE_SPAN;

    /* This is just simulation, we don't actually draw the particle. */

    return 0;
}
