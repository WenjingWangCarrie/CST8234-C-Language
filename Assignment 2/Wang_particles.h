/*
 * Name:      Wang_particles.h
 * Title:     A particle system
 * Descripts: A particle system is a collection of many many minute 
 *            particles that together represent a fuzzy object. Over 
 *            a period of time, particles are generated into a system, 
 *            move and change from within the system, and die from 
 *            the system.
 * Author:    Wenjing Wang
 * Date:      2016-11-17
 */

#include <stdio.h>

#define INITIAL_LIFE_SPAN 256
#define DELTA_LIFE_SPAN 5

#define PARTICLE_SIZE 10

struct color {
    float r;
    float g;
    float b;
    float a;
};

typedef struct color Color4;

struct vector {
    float x;
    float y;
    float z;
};

typedef struct vector Point3D;
typedef struct vector Vector3D;

struct particle {
    Color4 color;
    Point3D pos;
    Vector3D dir;
    Vector3D spd;
    int lifespan; /* keep track of how long the particle should be alive */
    int size;
    struct particle *next;
};

/*********************************************************************/
/* FUNCTION :  particle_init                                         */
/* PURPOSE  :  initialize the properties of a single particle        */
/* INPUT    :  pointer to the particle structure to be initialized   */
/* OUTPUT   :  returns 1 on error, 0 on success                      */
/* NOTES    :                                                        */
/*********************************************************************/
int particle_init(struct particle *p);

/*********************************************************************/
/* FUNCTION :  particle_add                                          */
/* PURPOSE  :  add a particle to the dynamic particle linked list    */
/* INPUT    :  struct particle *head. Head of the particle list      */
/* OUTPUT   :  returns ­1 on error, 0 on success                      */
/* NOTES    :  Calls particle_init()                                 */
/*********************************************************************/
int particle_add(struct particle **head);

/*********************************************************************/
/* FUNCTION :  particle_remove                                       */
/* PURPOSE  :  remove a specific particle from the dynamic particle  */
/*             linked list                                           */
/* INPUT    :  pointer to the particle to remove                     */
/* OUTPUT   :  returns 1 on error, 0 on success                      */
/* NOTES    :  Particle can be situated in any place in the list.    */
/*             Usually deleted because the lifespan ran out          */
/*********************************************************************/
int particle_remove(struct particle *p, struct particle *prev);

/*********************************************************************/
/* FUNCTION :  particle_destroy                                      */
/* PURPOSE  :  free memory used by the dynamic particle linked list  */
/* INPUT    :  struct particle **head. Head of the particle list     */
/* OUTPUT   :  returns 1 on error, the number of particles destroyed */
/*             on success                                            */
/* NOTES    :  removes all particles from the list                   */
/*             Calls particle_remove()                               */
/*********************************************************************/
int particle_destroy(struct particle **head);

/*********************************************************************/
/* FUNCTION :  particle_update                                       */
/* PURPOSE  :  update the particles properties to be rendered in     */
/*             the next frame                                        */
/* INPUT    :  struct particle **head. Head of the particle list     */
/* OUTPUT   :  returns 1 on error, 0 on success                      */
/* NOTES    :  Creativity and more creativity here for you !!!       */
/*********************************************************************/
int particle_update(struct particle **head);

/*********************************************************************/
/* FUNCTION :  particle_transform                                    */
/* PURPOSE  :  transform a specific particle                         */
/* INPUT    :  pointer to the particle to be transformed             */
/* OUTPUT   :  returns 1 on error, 0 on success                      */
/*********************************************************************/
int particle_transform(struct particle *p);
