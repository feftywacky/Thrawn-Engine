#include "transposition_table.h"
#include "zobrist_hashing.h"
#include "search.h"
#include <iostream>

int hashmap_len = 0;

TranspositionTable *hashmap = nullptr;

void reset_hashmap()
{
    TranspositionTable *hashval = nullptr;

    for (hashval = hashmap; hashval<hashmap+hashmap_len; hashval++)
    {
        hashval->key = 0;
        hashval->depth = 0;
        hashval->hash_flag = 0;
        hashval->score = 0;
    }
}

void init_hashmap(int mb)
{
    int size = 0x100000 * mb;

    hashmap_len = size / sizeof(TranspositionTable);

    if (hashmap != nullptr)
    {
        std::cout<<"hashmp memory cleared"<<std::endl;
        delete[] hashmap;
    }

    hashmap = new TranspositionTable[hashmap_len];

    if (hashmap == nullptr)
    {
        std::cout<<"cannot allocate memory for hashmap, re-allocating with "<<mb/2<<" MB"<<std::endl;
        init_hashmap(mb/2);
    }
    else
    {
        reset_hashmap();
        std::cout<<"hashmap sucessfully initialized with size "<<mb<<" MB"<<std::endl;
    }
}

int probeHashMap(thrawn::Position& pos, int depth, int alpha, int beta, int *best_move, int ply)
{
    // tt instance pointer that points to the hashmap entry that stores board data
    // hash function key is defined as key % size
    TranspositionTable *hashEntryPtr = &hashmap[pos.zobristKey % hashmap_len]; 

    if (hashEntryPtr->key == pos.zobristKey)
    {
        if (hashEntryPtr->depth >= depth)
        {
            int score = hashEntryPtr->score;

            if (score < -mateScore) 
                score += ply;
            if (score > mateScore) 
                score -= ply;

            if (hashEntryPtr->hash_flag == hashFlagEXACT) // pv node
                return score;
            if (hashEntryPtr->hash_flag == hashFlagALPHA && score <= alpha) // fail-low score
                return alpha;
            if (hashEntryPtr->hash_flag == hashFlagBETA && score >= beta) // fail-high score
                return beta;
        }
        
        *best_move = hashEntryPtr->best_move;
    }
    return no_hashmap_entry;
}

void writeToHashMap(thrawn::Position& pos, int depth, int score, int hashFlag, int bestMove, int ply)
{
    TranspositionTable *hashEntryPtr = &hashmap[pos.zobristKey % hashmap_len]; 

    if (score < -mateScore) score -= ply;
    if (score > mateScore) score += ply;
    

    hashEntryPtr->key = pos.zobristKey;
    hashEntryPtr->depth = depth;
    hashEntryPtr->hash_flag = hashFlag;
    hashEntryPtr->score = score;
    hashEntryPtr->best_move = bestMove;
}