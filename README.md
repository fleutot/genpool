# genpool

(work in progress)

Manage a pool of genomes, making them fight against each others according to a fitness function, hopefully evolving the population to better individuals, generation after generation.

## Cloning

Since the project comprises submodules, clone it with:

    $ git clone --recursive https://github.com/fleutot/genpool.git

## Building and testing

The application is not finished, but you can run unit tests:

    <path>/genpool $ make -C test test

You can also run `make test` from any directory `test` in the submodules:

    for d in $(find -name test -type d) ; do make -C $d test; done


## Why?

- genetic algorithms are fun
- to test git submodules (which is why I may have overdone it)
- have freely available C code to show. Now most of the code isn't very recent, and I have evolved as a programmer since then, but hopefully the newer code reflects my current skills. Likewise, implementing yet-another-version of linked lists may not be the most effective choice, but it was fun to do and works as a showcase.