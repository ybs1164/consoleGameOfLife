#include <windows.h>
#include <stdlib.h>
#include <unordered_set>

struct Pos{
    int x,y;
    Pos(int p = 0, int q = 0){
        x = p;
        y = q;
    }
    bool operator==(const Pos &q) const {
        return x==q.x && y==q.y;
    }
};

class Node{
private:
    Pos p;
    bool islife;
public:
    friend std::hash<Node>;
    Node(int x = 0, int y = 0){
        p = Pos(x, y);
        islife = true;
    }
    Pos getPos() const{
        return p;
    }
    bool operator==(const Node &q) const {
        return p==q.p;
    }
};

namespace std {
    template <>
    class hash<Node> {
    public:
        size_t operator()(const Node &p) const {
            Pos pos = p.getPos();
            using std::hash;
            return hash<int>()(pos.x) ^
                   hash<int>()(pos.y);
        }
    };
}

void gotoxy(int, int);
bool checkNodeLife(Node node);

std::unordered_set<Node> lifemap;
float timespeed = 0.0f;
Pos cam;

int main(){
    system("mode con cols=56 lines=20 | title Game of Life");

    Node im;

    lifemap.insert(im);

    return 0;
}

void gotoxy(int x, int y){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

bool checkNodeLife(Node node){

}
