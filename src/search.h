#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <array>
#include <cstdint>
#include <atomic>
#include "position.h"

using namespace std;

#define full_depth_moves 4
#define reduction_limit 3
#define INFINITY 50000
#define mateVal 49000
#define mateScore 48000
#define MAX_DEPTH 256

extern int ply;
extern uint64_t nodes;

extern std::vector<std::vector<int>> killer_moves;
extern std::vector<std::vector<int>> history_moves;
extern std::vector<int> pv_depth;
extern std::vector<std::vector<int>> pv_table;

extern bool follow_pv_flag;
extern bool score_pv_flag;

extern bool allowNullMovePruning;
extern bool allowFutilityPruning;

extern std::array<int, 4> LateMovePruning_factors;
extern int RFP_factor;

// repetition
extern std::vector<uint64_t> repetition_table;
extern int repetition_index;
extern int fifty_move;

// threading
extern std::atomic<bool> stop_threads;


// negamax with alpha beta pruning
int negamax(Position* pos, int depth, int alpha, int beta);

int quiescence(Position* pos, int alpha, int beta);

void search_position(Position* pos, int depth);

void search_position_threaded(Position* pos, int depth, int numThreads);

int score_move(Position* pos, int move);

void sort_moves(Position* pos, vector<int>& moves, int bestMove);

void score_pv(vector<int>& moves);

void print_move_scores(Position* pos, const vector<int>& moves);

int isRepetition(Position* pos);

void quicksort_moves(std::vector<int> &moves, std::vector<int> &move_scores, int low, int high);

int futility_margin(int depth);

int futility_move_count(int depth);

#endif