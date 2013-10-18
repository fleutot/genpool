/*----------------------------------------------------------------------------
Copyright (c) 2013 Gauthier Östervall
----------------------------------------------------------------------------*/

#ifndef GENPOOL_H_INCLUDED
#define GENPOOL_H_INCLUDED

void genpool_create(const int nb_individuals);
void genpool_mutation_rate_set(const double new_mutation_rate);
void genpool_destroy(void);

#endif // GENPOOL_H_INCLUDED
