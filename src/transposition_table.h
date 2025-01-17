#ifndef TRANSPOSITION_TABLE_H
#define TRANSPOSITION_TABLE_H
#include <cstdint>
#include "position.h"

#define no_hashmap_entry 100000

#define hashFlagEXACT 0
#define hashFlagALPHA 1
#define hashFlagBETA 2

struct TranspositionTable
{
    uint64_t key;  // unique chess position key
    int depth;          // current search depth
    int hash_flag;           // flag the type of node (fail-low/fail-high/PV) 
    int score;          // score (alpha/beta/PV)
    int best_move;
};

extern int hashmap_len;
extern TranspositionTable* hashmap;

void init_hashmap(int mb);

void reset_hashmap();

int probeHashMap(thrawn::Position& pos, int depth, int alpha, int beta, int* bestMove, int ply);

void writeToHashMap(thrawn::Position& pos, int depth, int score, int hashFlag, int bestMove, int ply);

#endif