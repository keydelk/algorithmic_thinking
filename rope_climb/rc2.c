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

typedef struct position {
    int height, state;
} position;

typedef int board[SIZE * 2][2];
typedef position positions[SIZE * 4];

void add_position_up(int from_height, int to_height, int max_height,
                  positions pos, int *num_pos,
                  int itching[], board min_moves) {
    printf("Checking up-  from: %d \t - to %d\n", from_height, to_height);
    int distance = 1 + min_moves[from_height][0];
    if (to_height <= max_height && !itching[to_height] && 
         (min_moves[to_height][0] == -1 || min_moves[to_height][0] > distance)) {
         min_moves[to_height][0] = distance;
         pos[*num_pos] = (position){to_height, 0};
         ++(*num_pos);
        printf("position added: %d \t - min: %d\n", to_height, min_moves[to_height][0]);
        
    }
}

void add_position_down(int from_height, int to_height,
                  positions pos, int *num_pos,
                  board min_moves) {
    int distance = min_moves[from_height][1];
    printf("Checking down - from: %d \t - to %d\n", from_height, to_height);
    if (to_height >= 0 && 
         (min_moves[to_height][1] == -1 || min_moves[to_height][1] > distance)) {
         min_moves[to_height][1] = distance;
         pos[*num_pos] = (position){to_height, 1};
         ++(*num_pos);
         printf("position added: %d \t - min: %d\n", to_height, min_moves[to_height][1]);
        
    }
}

void add_position_01(int from_height, positions pos, int *num_pos, board min_moves) {
    int distance = 1 + min_moves[from_height][0];
    printf("Checking 0-1 shift at %d\n", from_height);
    if (min_moves[from_height][1] == - 1 || min_moves[from_height][1] > distance) {
         min_moves[from_height][1] = distance;
         pos[*num_pos] = (position){from_height, 1};
         ++(*num_pos);
         printf("01 shift added - min_moves: %d\n", min_moves[from_height][1]);
    }
}

void add_position_10(int from_height, positions pos, int *num_pos, 
                     int itching[], board min_moves) {
    int distance = min_moves[from_height][1];
    printf("Checking 1-0 shift at %d\n", from_height);
    if (!itching[from_height] && (min_moves[from_height][0] == -1 || min_moves[from_height][0] > distance)) {
         min_moves[from_height][0] = distance;
         pos[*num_pos] = (position){from_height, 0};
         ++(*num_pos);
         printf("10 shift added - min moves: %d\n", distance);
    }
}

void find_distances(int target_height, int jump_distance, int itching[], board min_moves) {
    static positions cur_positions, new_positions;
    int num_cur_positions, num_new_positions;
    int i, j, from_height, from_state;
    
    for (i = 0; i < target_height + jump_distance; ++i)
        for (j = 0; j < 2; ++j)
            min_moves[i][j] = -1;
    
    min_moves[0][0] = 0;
    cur_positions[0] = (position){0, 0};
    num_cur_positions = 1;
    
   printf("----Finding Distances -----\n");
    
    while (num_cur_positions > 0) {
        num_new_positions = 0;
        for (i = 0; i < num_cur_positions; ++i) {
            from_height = cur_positions[i].height;
            from_state = cur_positions[1].state;
            printf("Current height: %d \t current # pos: %d\n", from_height, num_cur_positions);
            if (num_cur_positions > 10) return;
            
            if (from_state == 0) {
                printf("add_position_up(%d, %d, %d, %d, %d)\n", from_height, from_height + jump_distance, 
                                target_height + jump_distance, new_positions,
                                num_new_positions);
                add_position_up(from_height, from_height + jump_distance, 
                                target_height + jump_distance, new_positions,
                                &num_new_positions, itching, min_moves);
                printf("add_position_01(from_height = %d, new_positions = %d, num_new_positions = %d, min_moves = %d)\n", from_height, new_positions, num_new_positions, min_moves[from_height][0]);
                add_position_01(from_height, new_positions, &num_new_positions, min_moves);
            } else {
                add_position_down(from_height, from_height - 1, 
                                  cur_positions, &num_cur_positions, min_moves);
                add_position_10(from_height, cur_positions, &num_cur_positions,
                                 itching, min_moves);
            }
        }
        num_cur_positions = num_new_positions;
        for (i = 0; i < num_cur_positions; ++i)
            cur_positions[i] = new_positions[i];
    }
}

void solve(int target_height, int jump_height, board min_moves) {
    int best = -1;
    int i;
    for (i = target_height; i < target_height + jump_height; i++)
        if (min_moves[i][0] != -1 && (best == -1 || min_moves[i][0] < best))
            best = min_moves[i][0];
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

