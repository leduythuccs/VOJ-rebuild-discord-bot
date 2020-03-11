#include <spoj.h>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

// FILE *spoj_p_in, *spoj_p_out, *spoj_t_out, *spoj_score;
// #define PIN "in.txt"
// #define POUT "ans.txt"
// #define TOUT "out.txt"
// #define SCORE "score.txt"

// void spoj_init()
// {
//   spoj_p_in=fopen(PIN, "r");
//   spoj_p_out=fopen(POUT, "r");
//   spoj_t_out=fopen(TOUT, "r");
//   spoj_score=fopen(SCORE, "w");
// }

// #define spoj_assert assert

const int MAX = 20;

queue<int> q_row;
queue<int> q_col;
int dist[MAX][MAX];
const int dir_row[] = {-1, 0, 1, 0};
const int dir_col[] = {0, 1, 0, -1};
char board[MAX][MAX];
int n_row, n_col;
double diff;

const int INF = 1000000;

bool game_end = false;

bool inside(int row, int col) {
  return 0 <= row && row < n_row && 0 <= col && col < n_col;
}

void recompute_dist() {
  memset(dist, -1, sizeof(dist));
  for (int row = 0; row < n_row; ++row) {
    for (int col = 0; col < n_col; ++col) {
      if (board[row][col] == 'O') {
        dist[row][col] = 0;
        q_row.push(row);
        q_col.push(col);
      }
    }
  }

  while (q_row.size() > 0) {
    int row = q_row.front();
    int col = q_col.front();
    q_row.pop();
    q_col.pop();

    for (int dir = 0; dir < 4; ++dir) {
      int next_row = row + dir_row[dir];
      int next_col = col + dir_col[dir];

      if (inside(next_row, next_col)) {
        char c = board[next_row][next_col];
        if (dist[next_row][next_col] == -1 && (c=='.' || c=='*')) {
          dist[next_row][next_col] = dist[row][col] + 1;
          q_row.push(next_row);
          q_col.push(next_col);
        }
      }
    }
  }
}

bool can_mouse_move() {
  for (int row = 0; row<n_row; ++row) {
    for (int col = 0; col < n_col; ++col) {
      if (board[row][col] == '*') {
        return dist[row][col] != -1;
      }
    }
  }
  return false;
}

void move_mouse() {
  for (int row = 0; row<n_row; ++row) {
    for (int col = 0; col < n_col; ++col) {
      if (board[row][col] == '*') {
        int min_dist = INF;
        for (int dir = 0; dir < 4; ++dir) {
          int next_row = row + dir_row [dir];
          int next_col = col + dir_col [dir];
          if (inside(next_row, next_col)) {
            char c = board[next_row][next_col];
            if (c=='.' || c=='O') {
              min_dist = min(min_dist, dist[next_row][next_col]);
            }
          }
        }
        for (int dir = 0; dir < 4; ++dir) {
          int next_row = row + dir_row [dir];
          int next_col = col + dir_col [dir];
          if (inside(next_row, next_col)) {
            char c = board[next_row][next_col];
            if (c=='.' || c=='O') {
              if (dist[next_row][next_col] == min_dist) {
                if (c=='O') {
                  game_end=true;
                } else {
                  swap(board[row][col], board[next_row][next_col]);
                }
                return;
              }
            }
          }
        }
      }
    }
  }
}

void print_board() {
  cerr << "Board status:" << endl;
  for (int row = 0; row < n_row; ++row)
    cerr << board[row] << endl;
  cerr << endl;
}

int main() {
  spoj_init();

  fscanf(spoj_p_in, "%d%d", &n_row, &n_col);

  for (int row = 0; row < n_row; ++row) {
    fscanf(spoj_p_in, "%s", board[row]);
  }

  fscanf(spoj_p_in, "%lf", &diff);

  int n_block, ret = 0;
  spoj_assert (fscanf(spoj_t_out, "%d", &n_block) == 1);

  bool win = false;

  if (!can_mouse_move()) {
    win = true;
  } else {
    while (n_block --) {
      int r, c;
      spoj_assert (fscanf(spoj_t_out, "%d%d", &r, &c) == 2);

      cerr << "Put a block at " << r << ", " << c << endl;

      --r;
      --c;

      spoj_assert (inside(r,c));

      spoj_assert (board[r][c] == '.');

      ++ ret;

      board[r][c] = '#';

      recompute_dist();

      if (!can_mouse_move()) {
        win = true;
        print_board();
        cerr << "No way to move!" << endl;
        break;
      } else {
        move_mouse();
        print_board();
        if (game_end) {
          cerr << "The mouse goes back to his home! Game ended." << endl;
          break;
        }
      }
    }
  }
  double score = 0;
  if (win) {
    score = (double) 5 / (ret + 4);
  }

  score = diff * score;

  fprintf(spoj_score, "%.6lf\n", score);
  return 0;
}
