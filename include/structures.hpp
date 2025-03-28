#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

struct Node
{
    int number;
    int degree;
    int x;
    int y;

    // Default constructor
    Node() : number(0), degree(0), x(0), y(0) {}

    // Constructor with parameters
    Node(int number, int degree = 0, int x = 0, int y = 0) : number(number), degree(degree), x(x), y(y) {}
};

struct Edge
{
    Node* start;
    Node* destination;
    float weight;
};

struct Compare {
    bool operator()(const Edge& e1, const Edge& e2){
        return e1.weight > e2.weight;
    }
};

#endif // STRUCTURES_HPP