#include<iostream>

using namespace std;

//Node for user and recharge amount
struct node
{
    int user_id;
    int recharge;
    int height;
    node * left;
    node * right;

    node(int u, int r) : user_id{u}, recharge{r}, height{1}, left{nullptr}, right{nullptr}
    {}
};

//Cumulative Maximum Recharge
struct cumulative_maximum
{
    int max_recharge;
    int user_id;

    cumulative_maximum() : max_recharge{-1}, user_id{-1}
    {}
};

//function declarations
int max(int, int);
int height(node *);
node * rightRotate(node *);
node * leftRotate(node *);
int getBalance(node *);
node * insert(node *, int, int);
node * search(node *, int);

int main()
{
    int n, user_id, recharge, operation;
    node * AVL = nullptr, * temp;
    cumulative_maximum m;
    cin >> n;
    while(n--)
    {
        cin >> operation;
        if(operation == 1)
        {
            cin >> user_id;
            cin >> recharge;
            temp = search(AVL, user_id);
            if(temp == nullptr)
            {
                temp = insert(AVL, user_id, recharge);
                if(m.max_recharge < recharge)
                {
                    m.max_recharge = recharge;
                    m.user_id = user_id;
                }
            }
            else
            {
                temp -> recharge = temp -> recharge + recharge;
                if(m.max_recharge < temp -> recharge)
                {
                    m.max_recharge = temp -> recharge;
                    m.user_id = temp -> user_id;
                }
            }
            
        }
        if(operation == 2)
        {
            if(m.max_recharge == -1)
                cout << "No Data Availabe\n";
            else
            {
                cout << m.user_id << '\n';
            }
            
        }
    }
    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(node * n)
{
    if(n == nullptr)
        return 0;
    else
        return n -> height;
    
}

node * rightRotate(node * y)
{
    node * x = y -> left;
    node * T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    y -> height = max(height(y -> left), height(y -> right)) + 1;
    y -> height = max(height(x -> left), height(x -> right)) + 1;

    return x;
}

node * leftRotate(node * x)
{
    node * y = x -> right;
    node * T2 = y -> left;

    y -> left = x;
    x -> right = T2;

    x -> height = max(height(x -> left), height(x -> right)) + 1;
    y -> height = max(height(y -> left), height(y -> right)) + 1;

    return y;

}

int getBalance(node * n)
{
    if(n == nullptr)
        return 0;
    return height(n -> left) - height(n -> right);
}

node * insert(node * root, int user_id, int recharge)
{
    if(root == nullptr)
    {
        node * temp = new node(user_id, recharge);
        return temp;
    }
    if(user_id < root -> user_id)
    {
        root -> left = insert(root -> left, user_id, recharge);
    }
    else if (user_id > root -> user_id)
    {
        root -> right = insert(root -> right, user_id, recharge);
    }
    else
    {
        return root;
    }

    root -> height = max(height(root -> left), height(root -> right)) + 1;

    int balance = getBalance(root);
    
    if(balance > 1 && user_id < root -> left -> user_id)
        return rightRotate(root);

    if(balance < -1 && user_id > root -> right -> user_id)
        return leftRotate(root);
    
    if(balance > 1 && user_id > root -> left -> user_id)
    {
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }

    if(balance > -1 && user_id < root -> right -> user_id)
    {
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }

    return root;
}

node * search(node * node, int user_id)
{
    if(node == nullptr || node -> user_id == user_id)
    {
        return node;
    }
    if(node -> user_id < user_id)
        return search(node -> right, user_id);

    return search(node -> left, user_id);
}