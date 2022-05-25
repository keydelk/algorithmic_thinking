/* Rope Climb
   DMOJ problem: wc18c1s3
   Bob must get to a height of at least h meters.
   He can move up by jumping a height of exactly j meters.
   He can fall any number of meters.
   There is itching powder on some segments of the rope - intervals [a, b]
   Bob cannot land (via jump or fall) on any part with itching powder [a, b]
   The goal is to determine the minimum number of moves needed to get to height h or higher.
   
   Input: one test case consisting of the following lines:
               1 - a line with three integers: h, j, and n - each no more than 1,000,000
                   h = the minimum height bob must reach
                   j = the distance Bob can jump
                   n = the number of segments with itching powder
               2+ - n lines with 2 integers, a and b. Each is at most h - 1
*/
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000000

typedef int board[SIZE * 2];
typedef int positions[SIZE * 2];


void add_position(int from_height, int to_height, int max_height,
                  positions new_positions, int *num_new_positions,
                  int itching[], board min_moves);

void find_distances(int target_height, int jump_distance, int itching[], board min_moves) {
    static positions cur_positions, new_positions;
    int num_cur_positions, num_new_positions;
    int i, j, from_height;
    
    for (i = 0; i < target_height + jump_distance; ++i)
        min_moves[i] = -1;
    
    min_moves[0] = 0;
    cur_positions[0] = 0;
    num_cur_positions = 1;
    
//    printf("----Finding Distances -----\n");
    
    while (num_cur_positions > 0) {
        num_new_positions = 0;
        for (i = 0; i < num_cur_positions; ++i) {
            from_height = cur_positions[i];
            
            add_position(from_height, from_height + jump_distance,
                         target_height + jump_distance - 1, new_positions,
                         &num_new_positions, itching, min_moves);
            for (j = (from_height - jump_distance) > 1 ? (from_height - jump_distance) : 1; j < from_height; j++)
                add_position(from_height, j, target_height + jump_distance - 1,
                             new_positions, &num_new_positions, itching, min_moves);
        }
        num_cur_positions = num_new_positions;
        for (i = 0; i < num_cur_positions; ++i)
            cur_positions[i] = new_positions[i];
    }
}

void add_position(int from_height, int to_height, int max_height,
                  positions new_positions, int *num_new_positions,
                  int itching[], board min_moves) {
//    printf("Checking - from: %d \t - to %d\n", from_height, to_height);
    if (to_height <= max_height && !itching[to_height] && min_moves[to_height] == -1) {
        min_moves[to_height] = 1 + min_moves[from_height];
        new_positions[*num_new_positions] = to_height;
//        printf("position added: %d \t - min: %d\n", to_height, min_moves[to_height]);
        ++(*num_new_positions);
    }
}

void solve(int target_height, int jump_height, board min_moves) {
    int best = -1;
    int i;
    for (i = target_height; i < target_height + jump_height; i++)
        if (min_moves[i] != -1 && (best == -1 || min_moves[i] < best))
            best = min_moves[i];
    printf("%d\n", best);
}

int main() {
    int target_height, jump_distance, num_itching_sections;
    static int itching[SIZE * 2] = {0};
    static board min_moves;
    int i, j, itch_start, itch_end;
    
    /* read input */
    scanf("%d %d %d", &target_height, &jump_distance, &num_itching_sections);
    for (i = 0; i < num_itching_sections; ++i) {
        scanf("%d %d", &itch_start, &itch_end);
        for (j = itch_start; j <= itch_end; ++j)
            itching[j] = 1;
    }
//    printf("Target height: %d \t Jump dist: %d \t # itching: %d\n", target_height, jump_distance, num_itching_sections);
    
    find_distances(target_height, jump_distance, itching, min_moves);
    solve(target_height, jump_distance, min_moves);
    
    return EXIT_SUCCESS;
}
