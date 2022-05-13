#include<iostream>
#include<string>
#include<sstream>
using namespace std;

// An AVL tree node
class AVLNode
{
public:
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// get the height of tree
// need to handle null pointer
int getHeight(AVLNode* node)
{
    if (node == NULL)
    {
        return 0;
    }

    return node->height;
}

//a method to create a new AVL node
AVLNode* setNode(int value)
{
    AVLNode* node = new AVLNode();
    node->value = value;

    //define the height of a single AVL node is 1
    node->height = 1;

    return(node);
}

// perform right rotation
AVLNode* rightRotate(AVLNode* node)
{
    AVLNode* node_left = node->left;
    AVLNode* node_left_right = node_left->right;

    // rotate
    node_left->right = node;
    node->left = node_left_right;

    // set height again
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node_left->height = max(getHeight(node_left->left), getHeight(node_left->right)) + 1;

    // updated root
    return node_left;
}

// perform left rotation
AVLNode* leftRotate(AVLNode* node)
{
    AVLNode* node_right = node->right;
    AVLNode* node_right_left = node_right->left;

    // rotate
    node_right->left = node;
    node->right = node_right_left;

    // set height again
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node_right->height = max(getHeight(node_right->left), getHeight(node_right->right)) + 1;

    // updated root
    return node_right;
}

// return balance difference
int balanceDiff(AVLNode* node)
{
    if (node == NULL)
    {
        return 0;
    }

    //return left's height minus right's height
    return getHeight(node->left) - getHeight(node->right);
}

// insert new node to the AVL tree
AVLNode* insert(AVLNode* node, int value)
{
    //not null check
    if (node == NULL)
    {
        return(setNode(value));
    }

    if (value < node->value)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value);
    }
    else
    {
        //no equal value, cannot insert
        return node;
    }

    // set height again
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // check balance different for rotation
    int balance_diff = balanceDiff(node);

    // four situations as follows:
    if (balance_diff > 1 && value < node->left->value)
    {
        return rightRotate(node);
    }

    if (balance_diff < -1 && value > node->right->value)
    {
        return leftRotate(node);
    }

    if (balance_diff > 1 && value > node->left->value)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance_diff < -1 && value < node->right->value)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// get the max node on the left
AVLNode* getMaxNode(AVLNode* node)
{
    AVLNode* current = node;

    while (true)
    {
        if (current->right == NULL)
        {
            break;
        }

        current = current->right;
    }

    return current;
}

// remove given value
AVLNode* remove(AVLNode* root, int value)
{
    // not null check
    if (root == NULL)
    {
        return root;
    }

    // find the value on the left
    if (value < root->value)
    {
        root->left = remove(root->left, value);
    }
    // find the value on the left
    else if (value > root->value)
    {
        root->right = remove(root->right, value);
    }
    // find the value
    else
    {
        // zero or one child 
        if ((root->left == NULL) || (root->right == NULL))
        {
            AVLNode* tmp = root->left ? root->left : root->right;

            // zero child 
            if (tmp == NULL)
            {
                tmp = root;
                root = NULL;
            }
            else // one child
            {
                *root = *tmp;
            }

            //release memory
            free(tmp);
        }
        else
        {
            AVLNode* tmp = getMaxNode(root->left);
            root->value = tmp->value;
            root->left = remove(root->left, tmp->value);
        }
    }

    // not null check
    if (root == NULL)
    {
        return root;
    }

    // set height again 
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // get balance different
    int balance_diff = balanceDiff(root);

    // four situations as follows
    if (balance_diff > 1 && balanceDiff(root->left) >= 0)
    {
        return rightRotate(root);
    }

    if (balance_diff > 1 && balanceDiff(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance_diff < -1 && balanceDiff(root->right) <= 0)
        return leftRotate(root);

    if (balance_diff < -1 && balanceDiff(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// pre order of AVL tree
bool preOrder(AVLNode* node)
{
    if (node != NULL)
    {
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);

        return true;
    }

    return false;
}

// in order of AVL tree
bool inOrder(AVLNode* node)
{
    if (node != NULL)
    {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);

        return true;
    }

    return false;
}

// post order of AVL tree
bool postOrder(AVLNode* node)
{
    if (node != NULL)
    {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << " ";

        return true;
    }

    return false;
}

int main()
{
    string input;
    AVLNode* root = NULL;

    //continuously input until "IN", "PRE" OR "POST"
    while (true)
    {
        cin >> input;

        if (input == "IN")
        {
            if (!inOrder(root))
            {
                cout << "EMPTY" << endl;
            }

            break;
        }

        if (input == "PRE")
        {
            if (!preOrder(root))
            {
                cout << "EMPTY" << endl;
            }

            break;
        }

        if (input == "POST")
        {
            if (!postOrder(root))
            {
                cout << "EMPTY" << endl;
            }

            break;
        }

        stringstream ss;
        string str_int = input.substr(1);
        int num;
        ss << str_int;
        ss >> num;

        if (input[0] == 'A')
        {
            root = insert(root, num);
        }
        else if (input[0] == 'D')
        {
            root = remove(root, num);
        }
    }

    return 0;
}