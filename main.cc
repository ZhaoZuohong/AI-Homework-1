/*
 * Solve the problem about Missionaries and Cannibals with BFS
 * This file is created by Zhao Zuohong on Feb 25, 2020
 * All rights reserved.
 */

#include <cstdio>
#include <cstring>

// two directions
const int l = 0;
const int r = 1;

// if a status is considered
int Marked[4][4][2];

// the status
typedef struct status {
    int x; // num of missionaries
    int y; // num of cannibals
    int b; // location of boat
    int moves; // to hold the result
} status;

// begin and target
status begin = { 3, 3, l, 0 };
status target = { 0, 0, r, 0 };

// Queue of status
const int QLimit = 100;
status Queue[QLimit];
int QLength;
int QHead;

void EnQueue(status s)
{
    Queue[(QHead + QLength) % QLimit] = s;
    QLength = (QLength + 1) % QLimit;
}

bool DeQueue(status* s)
{
    if (QLength == 0) {
        return false;
    }
    *s = Queue[QHead];
    QHead = (QHead + 1) % QLimit;
    --QLength;
    return true;
}

void init(void)
{
    EnQueue(begin);
}

// check whether a move of m missionaries and n cannibals is valid
bool CheckMove(status* s, int m, int n)
{
    int leftx, lefty, rightx, righty;
    if (s->b == l) {
        leftx = s->x - m;
        lefty = s->y - n;
        rightx = 3 - s->x + m;
        righty = 3 - s->y + n;
    } else {
        leftx = s->x + m;
        lefty = s->y + n;
        rightx = 3 - s->x - m;
        righty = 3 - s->y - n;
    }
    if (leftx != 0) {
        if (leftx < lefty) {
            return false;
        }
    }
    if (rightx != 0) {
        if (rightx < righty) {
            return false;
        }
    }
    return true;
}

// check whether the agent has reached the target
bool ReachTarget(status s)
{
    if (s.x == target.x && s.y == target.y && s.b == target.b) {
        return true;
    } else {
        return false;
    }
}

// bfs algorithm to solve this problem
int bfs(void)
{
    status current_status;
    while (DeQueue(&current_status)) {
        int mlimit, nlimit; // range of m and n
        if (current_status.b == l) {
            mlimit = current_status.x;
            nlimit = current_status.y;
        } else {
            mlimit = 3 - current_status.x;
            nlimit = 3 - current_status.y;
        }
        for (int m = 0; m <= mlimit; ++m) {
            for (int n = 0; n <= nlimit; ++n) {
                if (m == 0 && n == 0) {
                    continue;
                }
                if (m + n > 2) {
                    continue;
                }
                if (CheckMove(&current_status, m, n)) {
                    status new_status; // transfer from current state to new state
                    if (current_status.b == l) {
                        new_status.b = r;
                        new_status.x = current_status.x - m;
                        new_status.y = current_status.y - n;
                    } else {
                        new_status.b = l;
                        new_status.x = current_status.x + m;
                        new_status.y = current_status.y + n;
                    }

                    if (Marked[new_status.x][new_status.y][new_status.b] == 1) {
                        continue;
                    }
                    Marked[new_status.x][new_status.y][new_status.b] = 1;

                    new_status.moves = current_status.moves + 1;
                    if (ReachTarget(new_status)) {
                        return new_status.moves;
                    }
                    EnQueue(new_status);
                }
            }
        }
    }
    return -1;
}

int main(void)
{
    init();
    int result = bfs();
    printf("%d\n", result);
    return 0;
}