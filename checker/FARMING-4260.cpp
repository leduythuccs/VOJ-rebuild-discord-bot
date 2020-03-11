#include <spoj.h>
#include <stdio.h>
#include <stdlib.h>

#define maxSeason 100005
#define maxFruit 105
#define maxPaddy 105

// Begin cut here
/*
FILE *spoj_p_in,     // problem's input 
     *spoj_p_out,    // problem's output 
     *spoj_t_out,    // tested program's output 
     *spoj_score;    // score for the program, for challenge problems 

void spoj_init() {
     spoj_p_in  = fopen("farm.in", "r");
     spoj_p_out = fopen("farm.ans", "r");
     spoj_t_out = fopen("farm.out", "r");
     spoj_score = fopen("score.txt", "w");
}

void spoj_assert(bool b) {
     if (!b) {
        fprintf(spoj_score, "Wrong answer.\n");
        exit(0);
     }
}
*/
// End cut here

class Fruit {
      public:
             int requiredExperience;
             int timeUntilHarvest;
             int seedPrice;
             int promisedIncome;
             int gainedExperience;
};

class Season {
      public:
             int startDate;
             int finishDate;
             int fruit;
};

class Paddy {
      public:
             int numberSeason;
             Season season[maxSeason];
};

int numberPaddy, numberFruit, numberDay, fund, experience, income, best;
Fruit kindFruit[maxFruit];
Paddy paddy[maxPaddy];

bool checkCorrectness() {
     for (int i = 1; i <= numberPaddy; ++ i)
         for (int j = 1; j <= paddy[i].numberSeason; ++ j) {
             if (paddy[i].season[j].fruit < 0 || paddy[i].season[j].fruit > numberFruit) {
//                fprintf(spoj_score, "-> Khong ton tai loai cay trong nay.\n");
                return false;
             }
             paddy[i].season[j].finishDate = paddy[i].season[j].startDate - 1
                                           + kindFruit[paddy[i].season[j].fruit].timeUntilHarvest;
             Season currentSeason = paddy[i].season[j];
             if (currentSeason.finishDate > numberDay) {
//                fprintf(spoj_score, "-> Canh tac qua so ngay quy dinh.\n");
                return false;
             }
             if (j > 1) {
                Season previousSeason = paddy[i].season[j-1];
                if (currentSeason.startDate <= previousSeason.finishDate) {
//                   fprintf(spoj_score, "-> Bat dau vu moi truoc khi ket thuc vu cu.\n");
                   return false;
                }
             }
         }
     int currentFund = fund;
     int currentExperience = experience;
     for (int currentDate = 1; currentDate <= numberDay; ++ currentDate) {
//         fprintf(spoj_score, "---------------------------------\n");
//         fprintf(spoj_score, "Ngay thu %d: %d tien von + %d kinh nghiem.\n\n", currentDate, currentFund, currentExperience);
         for (int i = 1; i <= numberPaddy; ++ i) {
             for (int j = 1; j <= paddy[i].numberSeason; ++ j) {
                 Season currentSeason = paddy[i].season[j];
                 Fruit currentFruit = kindFruit[currentSeason.fruit];
                 if (currentSeason.startDate == currentDate) {
                    if (currentFruit.requiredExperience > currentExperience) {
//                       fprintf(spoj_score, "-> Khong du kinh nghiem.\n");
                       return false;
                    }
                    if (currentFruit.seedPrice > currentFund) {
//                       fprintf(spoj_score, "-> Khong du tien mua hat giong.\n");
                       return false;
                    }
                    currentFund -= currentFruit.seedPrice;
                 }
                 if (currentSeason.finishDate == currentDate) {
                    currentFund += currentFruit.promisedIncome;
                    currentExperience += currentFruit.gainedExperience;
                 }
             }
         }
     }
     
//     fprintf(spoj_score, "---------------------------------\n");
//     fprintf(spoj_score, "Ngay cuoi cung: %d tien von + %d kinh nghiem.\n\n", currentFund, currentExperience);
     
     if (currentFund != income) {
//        fprintf(spoj_score, "-> Tinh sai tong thu nhap.");
        return false;
     }
     return true;
}

void getOutput() {
     fscanf(spoj_t_out, "%d", &income);
     for (int i = 1; i <= numberPaddy; ++ i) {
         fscanf(spoj_t_out, "%d", &paddy[i].numberSeason);
         for (int j = 1; j <= paddy[i].numberSeason; ++ j)
             fscanf(spoj_t_out, "%d %d", &paddy[i].season[j].startDate, &paddy[i].season[j].fruit);
     }
}

void getInput() {
     fscanf(spoj_p_in, "%d %d %d %d %d", &numberPaddy, &numberFruit, &numberDay, &fund, &experience);
     for (int i = 1; i <= numberFruit; ++ i)
         fscanf(spoj_p_in, "%d %d %d %d %d", &kindFruit[i].requiredExperience, &kindFruit[i].timeUntilHarvest,
         &kindFruit[i].seedPrice, &kindFruit[i].promisedIncome, &kindFruit[i].gainedExperience);
}

void getAnswer() {
     fscanf(spoj_p_out, "%d", &best);
}

int main() {
    spoj_init();
    
    getInput();
    getOutput();
    getAnswer();
    
    double points = 0;
    if (checkCorrectness())
       points = (double)income/best;
    
    fprintf(spoj_score, "%0.2lf", points);
}
