

using namespace std;

template <class T>
class Tree {

public:

    bool rootIsSet = false;

    Tree() {}

    NodeB<T>* addNode(T elem, NodeB<T>* parent) {

        if (!rootIsSet) {

            parent = new NodeB<T>;
            parent->parent = NULL;
            parent->element = elem;
            rootIsSet = true;
            return parent;
        }
        parent->child.push_back(new NodeB<T>);

        parent->child.at(parent->child.size() - 1)->element = elem;
        parent->child.at(parent->child.size() - 1)->parent = parent;
        return parent;
    }

    void printAll(NodeB<T>* n) {

        if (isRoot(n))
            cout << "element = " << n->element << endl;

        if (n->child.size() == 0)
            return;

        int i = 0;
        while (i < n->child.size()) {

            cout << "element = " << n->child.at(i)->element << endl;
            printAll(n->child.at(i));
            ++i;
        }
    }

    bool isRoot(NodeB<T>* n) {

        return (n->parent == NULL);
    }

    bool isExternal(NodeB<T>* n) {

        return (n->child.size() == 0);
    }

    bool isInternal(NodeB<T>* n) {

        return (!isExternal(n));
    }

    int height(NodeB<T>* tree) {

        if (isExternal(tree))
            return 0;

        int i = 0;
        int greatest = 0;
        while (i < tree->child.size()) {

            int number = height(tree->child.at(i)) + 1;
            if (number > greatest)
                greatest = number;

            ++i;
        }
        return greatest;
    }

    int depthAtNode(NodeB<T>* n) {

        if (isRoot(n))
            return 1;

        return 1 + depthAtNode(n->parent);
    }
};



int main()
{

    // general tree

    Tree<int> gtree;
    NodeB<int>* root = NULL;
    root = gtree.addNode(8, root); // set Root
    gtree.addNode(5, root); // add first child of root
    gtree.addNode(4, root); // add second child of root
    gtree.addNode(3, root); // add third child of root
    gtree.addNode(2, root->child.at(0)); // add first child of roots first child
    gtree.addNode(6, root->child.at(0));
    gtree.addNode(10, root->child.at(0));
    gtree.addNode(1, root->child.at(1));
    gtree.addNode(15, root->child.at(2));
    gtree.addNode(20, root->child.at(2));
    gtree.addNode(17, root->child.at(0)->child.at(0));

    gtree.printAll(root);

    cout << "height == " << gtree.height(root) << endl;
    cout << "depth == " << gtree.depthAtNode(root->child.at(0)->child.at(0)) << endl;

    return 0;
}