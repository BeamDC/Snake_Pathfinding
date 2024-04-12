#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>
using namespace std;

const int width = 9, height = 9;
int screen[height][width];
deque<pair<int,int>> snake;
pair<int,int> apple;
//pair<int,int> next_apple;

void spawn_apple(){
    srand(time(0));
    bool valid_spawn = false;
    int apple_x;
    int apple_y;

    //check that the apple doesnt collide with a segment of the snake
    while(!valid_spawn){
        apple_x = rand() % width;
        apple_y = rand() % height;
        valid_spawn = true;
        for(auto& pos : snake){
            if(pos.first == apple_y && pos.second == apple_x){
                valid_spawn = false;
                break;
            }
        }
    }
    apple = {apple_y, apple_x};
    cout << "New Apple @ (" << apple_x << ", " << apple_y << ")\n";
}
void eat(){
    snake.push_back(snake.back());
    spawn_apple();
}
void move(char dir){
    pair<int,int> head = snake.front();
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

    if (head.first == apple.first 
        && head.second == apple.second)eat();
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
