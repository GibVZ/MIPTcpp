#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>
#include <queue>

using i8 = int8_t;
using TMap = std::vector<std::vector<i8>>;

const i8 WATER = 0;
const i8 LAND = 1;
const i8 OBSERVED_LAND = 2;

void IslandObserveQ(TMap & map, size_t x, size_t y) {
    std::queue<std::pair<size_t, size_t>> Q;

    Q.push({x, y});

    while (!Q.empty()) {
        auto cur = Q.front();
        x = cur.first; y = cur.second;
        Q.pop();

        if (map[x][y] != LAND) continue;
        
        map[x][y] = OBSERVED_LAND;
        

        if(map[x-1][y] == LAND) {
            Q.push({x - 1, y});
        }
        if(map[x+1][y] == LAND) {
            Q.push({x + 1, y});
        }
        if(map[x][y-1] == LAND) {
            Q.push({x, y - 1});
        }
        if(map[x][y+1] == LAND) {
            Q.push({x, y + 1});
        }
    }
}

struct ObserveState {

    static const int NONE;
    static const int LEFT;
    static const int  RIGHT; 
    static const int UP;
    static const int DOWN; 
    static const int DONE; 

    size_t x, y;
    i8 state;

    ObserveState(size_t x_, size_t y_, i8 state_) : x(x_), y(y_), state(state_) {}
};

const int ObserveState::NONE = 10;
const int ObserveState::LEFT = 11;
const int ObserveState::RIGHT = 12; 
const int ObserveState::UP = 13;
const int ObserveState::DOWN = 14; 
const int ObserveState::DONE = 15;

void IslandObserveS(TMap & map, size_t x, size_t y){
    std::vector<ObserveState> obs;
    obs.reserve(map.size() * map[0].size() + 5);

    obs.emplace_back(x, y, ObserveState::NONE);

    while (!obs.empty()) {
        ObserveState& cur = obs.back();
        x = cur.x; y = cur.y;

        switch (cur.state) {
            case ObserveState::NONE:
                map[x][y] = OBSERVED_LAND;
                cur.state = ObserveState::LEFT;
                [[fallthrough]];
            case ObserveState::LEFT:
                if(map[x-1][y] == LAND) {
                    obs.emplace_back(cur.x - 1, cur.y, ObserveState::NONE);
                    cur.state = ObserveState::RIGHT;
                    continue;
                }
                cur.state = ObserveState::RIGHT;
                [[fallthrough]];
            case ObserveState::RIGHT:
                if(map[x+1][y] == LAND) {
                    obs.emplace_back(cur.x + 1, cur.y, ObserveState::NONE);
                    cur.state = ObserveState::UP;
                    continue;
                }
                cur.state = ObserveState::UP;
                [[fallthrough]];
            case ObserveState::UP:
                if(map[x][y - 1] == LAND) {
                    obs.emplace_back(cur.x, cur.y - 1, ObserveState::NONE);
                    cur.state = ObserveState::DOWN;
                    continue;
                }
                cur.state = ObserveState::DOWN;
                [[fallthrough]];
            case ObserveState::DOWN:
                if(map[x][y + 1] == LAND) {
                    obs.emplace_back(cur.x, cur.y + 1, ObserveState::NONE);
                    cur.state = ObserveState::DONE;
                    continue;
                }
                cur.state = ObserveState::DONE;
                [[fallthrough]];

            case ObserveState::DONE:
                obs.pop_back();
        }
    }
}

void island_observe(TMap & map, size_t x, size_t y){
    map[x][y] = OBSERVED_LAND;
    if(map[x-1][y] == LAND) {
        island_observe(map, x-1, y);
    }
    if(map[x+1][y] == LAND) {
        island_observe(map, x+1, y);
    }
    if(map[x][y-1] == LAND) {
        island_observe(map, x, y-1);
    }
    if(map[x][y+1] == LAND) {
        island_observe(map, x, y+1);
    }
}

int main() {   
    size_t N, M;
    std::cin >> N >> M;
    TMap map(N + 2, std::vector<i8>(M + 2, WATER));

    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            int tmp;
            std::cin >> tmp;
            map[i+1][j+1] = tmp;
        }
    }
    
    size_t island_counter = 0;

    std::cerr << "OK read\n";

    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            if(map[i+1][j+1] == LAND) {
                IslandObserveS(map, i+1, j+1);
                ++island_counter;
            }
        }
    }
    std::cout << "islands: " << island_counter << "\n";
}