#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node
{
    vector<Node> children;
    vector<int> metadata;
};

void read(fstream& ifs, int nodes, int metadata, Node& parent)
{
    int childNodes, childMetadata;
    for (int i = 0; i < nodes; i++)
    {
        Node child;
        ifs >> childNodes >> childMetadata;
        read(ifs, childNodes, childMetadata, child);
        parent.children.push_back(child);
    }

    int value;
    for (int i = 0; i < metadata; i++)
    {
        ifs >> value;
        parent.metadata.push_back(value);
    }
}

int metadataSum(Node& node)
{
    int sum = 0;
    for (int value : node.metadata) 
    {
        sum += value;
    }

    for (Node child : node.children) 
    {
        sum += metadataSum(child);
    }

    return sum;
}

int nodeValue(Node& node)
{
    int sum = 0;
    int i;
    for (int value : node.metadata) 
    {
        i = value - 1;
        if (node.children.size() > 0) {
            if (i >= 0 && i < node.children.size()) {
                sum += nodeValue(node.children[i]);
            }
        }
        else {
            sum += value;
        }
    }

    return sum;
}

int main()
{
    fstream ifs("day8.in", fstream::in);

    Node root;
    int nodes, metadata;
    ifs >> nodes >> metadata;
    read(ifs, nodes, metadata, root);

    cout << "part 1: " << metadataSum(root) << endl;
    cout << "part 2: " << nodeValue(root) << endl;

    return 0;
}
