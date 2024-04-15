#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>
using namespace std;

const int width = 8, height = 8;
int screen[height][width];
deque<pair<int,int>> snake;
vector<pair<int,int>> possible_spawns;
pair<int,int> apple;

void find_possible_spawns(){
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j){
            bool is_valid = true;
            for(auto segment : snake){
                if(segment.first == i && segment.second == j){
                    is_valid = false;
                }
            }
            if(is_valid)possible_spawns.push_back({i,j});
        }
    }
} 
void spawn_apple(){
    srand(time(0));
    bool valid_spawn = false;
    int pos = rand() % possible_spawns.size();
    int apple_x = possible_spawns[pos].first;
    int apple_y = possible_spawns[pos].second;

    apple = {apple_y, apple_x};
    cout << "New Apple @ (" << apple_x << ", " << apple_y << ")\n";
}
void eat(){
    snake.push_back(snake.back());
    spawn_apple();
}
void move(char dir){
    pair<int,int> head = snake.front();
    possible_spawns.clear();
    find_possible_spawns();
    if(dir == 'w'){
        --head.first;
    }
    else if(dir == 'a'){
        --head.second;
    }
    else if(dir == 's'){
        ++head.first;
    }
    else if(dir == 'd'){
        ++head.second;
    }

    if (head.first == apple.first && 
        head.second == apple.second)eat();
    snake.push_front(head);
    snake.pop_back();
}

void start_game(int width, int height){
    int head_x = floor(width/2)-1;
    int head_y = floor(height/2);

    pair <int,int> head = {head_y,head_x};
    pair <int,int> tail = {head_y,head_x - 1};
    snake.push_front(head);
    snake.push_back(tail);

    apple = {snake.front().first, snake.front().second + 2};
}
void print_screen(){ 
    //add snake to the screen
    for(auto pos : snake){
        screen[pos.first][pos.second] = 1;
    }

    //add apple to the screen
    screen[apple.first][apple.second] = 6;

    //display the screen
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j){
            cout << screen[i][j] << ' ';
        }
        cout << '\n';
    }cout << "\n\n";

    //clear the screen
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j){
            screen[i][j] = 0;
        }
    }
}

int main(){
    char dir;
    
    start_game(width, height);
    print_screen();
    
    move('d');
    print_screen();
    move('d');
    print_screen();
    move('w');
    print_screen();

    return 0;
}
