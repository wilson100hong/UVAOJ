#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <limit.h>

using namespace std;

class Road {
    char type;  // 'A' or 'S'
    int index;
}

class Addr{
    Road road;
    int num;
}

class Block{
    Addr start;
    Addr end;
};

class Node{
    Addr addr;
    int dist;
    // TODO:operator =
}

void ParseBlock(const string& line, Block* block) {
    // TODO
}

void ParseRoute(const string& line, Addr* start, Addr* end) {
    // TODO
}

int GetMinDist(const vector<Block>& blocks, const Addr& start, const Addr& end) {
    int min_dist = INT_MAX;
    map<Addr, int> best;
    
    // TODO: rearrange blocks 

    // TODO: priority_queue
    priority_queue<Node> heap;
    heap.push(new Node(start, 0));

    while (!heap.empty()) {
        Node node = heap.pop();
        // leave the loop if rest nodes' dist >= min_dist
        if (node.dist >= min_dist)
            break;

        // so now node.dist < min_dist

        if (node == end) {
            min_dist = node.dist;
            // no need to branch out
        } else if (best[node] != null && best[node] <= node.dist) {
            // skip the node
            continue;
        } else {
            vector<Node> branches;
            // TODO: Create all branched from node:
            // TODO 1. forward or u-turn
            //    
            // TODO 2. turn right

            for (Node& branch : branches) {  // TODO
                if (inbtw(node, branch, end)) {  // TODO
                    // cross end
                    int dist = node.dist + diff_same_road(end - node);  // TODO
                    if (dist < min_dist)
                        min_dist = dist;
                } else if (best[branch] == null || 
                        branch.dist < best[branch]) {
                    best[branch] = branch.dist; 
                    heap.push(branch);
                }
            }
        } 
    }
    return min_dist;

}
int main() {
    vector<Block> blocks;
    string line;
    while(getline(cin, line)) {
        if (line[0] == '#') {
            break;
        }
        Block block;
        ParseBlock(line, &block);
        blocks->push_back(block);
    }

    while(getline(cin, line)) {
        if (line[0] == '#') {
            break;
        }
        Addr start, end;
        ParseRoute(line, &start, &end);
        cout << GetMinDist(blocks, start, end) << endl;
    }
}


