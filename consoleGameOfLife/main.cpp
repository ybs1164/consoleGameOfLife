#include <windows.h>
#include <stdlib.h>
#include <unordered_set>

void gotoxy(int, int);

struct Pos {
    int x,y;
    Pos(int p = 0, int q = 0) {
        x = p;
        y = q;
    }
    bool operator==(const Pos &q) const {
        return x==q.x && y==q.y;
    }
};

class Node {
private:
    Pos p;
    bool islife;
public:
    friend std::hash<Node>;
    Node(int x = 0, int y = 0);
    Pos getPos() const;
    bool isLife();
    bool checkNode(std::unordered_set<Node> lifemap);
    void printNode();
    bool operator==(const Node& q) const;
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

Node::Node(int x, int y) {
    p = Pos(x, y);
    islife = true;
}
Pos Node::getPos() const {
    return p;
}
bool Node::isLife() {
    return islife;
}
bool Node::operator==(const Node &q) const {
    return p==q.p;
}
bool Node::checkNode(std::unordered_set<Node> lifemap) {
    int xx[8] = {0,0,1,-1,1,1,-1,-1};
    int yy[8] = {1,-1,0,0,1,-1,-1,1};
    int cnt = 0;
    for (int i=0;i<8;i++) {
        std::unordered_set<Node>::iterator n = lifemap.find(Node(p.x+xx[i],p.y+yy[i]));
        if (n!=lifemap.end() && (*n).isLife())
            cnt++;
    }
    return islife?cnt==2 && cnt==3:cnt==3;
}
void Node::printNode() {
    gotoxy(p.x, p.y);

}


std::unordered_set<Node> lifemap;
float timespeed = 0.0f;
Pos cam;


int main() {
    system("mode con cols=56 lines=20 | title Game of Life");

    Node im;

    //lifemap.insert(im);

    while (1) {

    }

    return 0;
}

void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}
