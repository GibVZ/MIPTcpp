#include <iostream>
#include <cstdint>
#include <algorithm>

using u32 = uint32_t;
using u64 = uint64_t;

struct Player{
  u32 skill;
  u32 number;
  
  bool operator<(Player& other) {
    return skill < other.skill;
  }
  bool operator>(Player& other) {
    return skill > other.skill;
  }
};


int main(){
  std::cout << "Please, enter the players amount  ";
  size_t pamount;
  std::cin >> pamount;
  if (pamount == 0) {
    std::cout << "You haven't players! Your team is empty!\n";
    return 0;
  }
  std::cout << "\nEnter the players skills in correct order\n";
  Player* players = new Player[pamount];
  for(size_t i = 0; i < pamount; ++i){
    std::cin >> players[i].skill;
    players[i].number = i;
  }
  
  std::sort(players, players + (pamount - 1));
  
  u64 total_skill = players[0].skill;
  Player *the_best_start = players, *the_best_end = players + 1;
  
  u64 max_skill = 0; // total_skill;
  Player *the_best = players + 1, *the_worst = players;
  // size_t lptr = 0;
  // size_t rptr = 1;
  while (the_best != players + (pamount-1)) {
    //total_skill += the_best.skill;
    if (the_best->skill >= the_worst->skill + (the_worst + 1)->skill) { // if team is uncorrect
      if (total_skill > max_skill){ // and the last team was better than previous
        max_skill = total_skill; // make the last team to the best 
        the_best_start = the_worst; the_best_end = the_best;
      }
      total_skill -= the_worst->skill; // decrement team skill on last the worst player
      ++the_worst; // and delete the worst player, so the best team with him already has seen
      
    }
    total_skill += the_best->skill; // add the best player's skill in team, because it is correct already
    ++the_best; // look at the next plyer
  } 
  if ((the_best->skill < the_worst->skill + (the_worst + 1)->skill) || (the_best == the_worst + 1)) {
    if (total_skill > max_skill){
      max_skill = total_skill;
      the_best_start = the_worst; the_best_end = the_best;
    }
  }
  std::cout << "The best team players numbers: ";
  while (the_best_start != the_best_end + 1) {
    std::cout << the_best_start->number << " ";
    ++the_best_start;
  }
  std::cout << "\n";
  delete[] players;
}
