#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

int main(){
    std::vector<std::pair<int, bool>> timetable;
    int n;
    std::cin>>n;
    for(int i=0; i<n; ++i){
        int arrival;
        int departure;
        std::cin>>arrival>>departure;
        timetable.emplace_back(arrival, true);
        timetable.emplace_back(departure, false);
    }
    std::sort(timetable.begin(), timetable.end(), 
    [](const std::pair<int, bool>& a, const std::pair<int, bool>& b){return a.first<b.first;});
    int num_max=0;
    int current_num=0;
    int j=0;
    auto sentinel = timetable.end();
    auto it = timetable.begin();
    while(it != sentinel){
        int time = it->first;
        while((it != sentinel)&&(it->first==time)){
            if(it->second){
                current_num++;
            }else{
                current_num--;
            }
            ++it;
        }
        if(current_num>num_max){
            num_max=current_num;
        }
    }
    std::cout<<num_max;
    return 0;
}