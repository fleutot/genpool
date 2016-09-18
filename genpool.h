/*----------------------------------------------------------------------------
Copyright (c) 2013 Gauthier Östervall
----------------------------------------------------------------------------*/

#ifndef GENPOOL_H_INCLUDED
#define GENPOOL_H_INCLUDED

#include <stdbool.h>

struct genpool;

struct genpool *genpool_create(const int nb_individuals,
                               const double mutation_rate);

void genpool_mutation_rate_set(struct genpool *gp,
                               const double new_mutation_rate);
void genpool_destroy(struct genpool **gp);

#endif // GENPOOL_H_INCLUDED
