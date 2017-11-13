/*
 * Name:      WAng_particle.h
 * Title:     A particle system
 * Descripts: A particle system is a collection of many many minute 
 *            particles that together represent a fuzzy object. Over 
 *            a period of time, particles are generated into a system, 
 *            move and change from within the system, and die from 
 *            the system.
 * Author:    Wenjing Wang
 * Date:      2016-11-17
 */

#include <time.h>

void printUsage(const char *pgm);
void reportTime(clock_t start_t, clock_t end_t, const char *type);
