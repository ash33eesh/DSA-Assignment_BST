#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class BSTNode
{
public:
    BSTNode *left;
    int SerialNumber;
    string Url;
    string Description;
    BSTNode *right;

    BSTNode();
};

BSTNode::BSTNode()
{
    left = right = NULL;
}

class BST
{
public:
    BSTNode *root;

    BST();

    void Insert(int, string, string);
    void Display(BSTNode *);
    void Searchtemp(const char[]); // Change the parameter type

    void Destroy(BSTNode *);
    ~BST();
};

BST::BST()
{
    root = NULL;
}

void BST::Insert(int sno, string url, string desc)
{
    BSTNode *bstnode = new BSTNode;
    bstnode->SerialNumber = sno;
    bstnode->Url = url;
    bstnode->Description = desc;

    if (root == NULL)
    {
        root = bstnode;
    }
    else
    {
        BSTNode *temp = root;
        BSTNode *prev;

        while (temp != NULL)
        {
            prev = temp;
            if (bstnode->SerialNumber < temp->SerialNumber)
            {
                temp = temp->left;
            }
            else if (bstnode->SerialNumber > temp->SerialNumber)
            {
                temp = temp->right;
            }
            else
            {
                return;
            }
        }

        if (bstnode->SerialNumber > prev->SerialNumber)
        {
            prev->right = bstnode;
        }
        else if (bstnode->SerialNumber < prev->SerialNumber)
        {
            prev->left = bstnode;
        }
    }
}

void BST::Destroy(BSTNode *node)
{
    if (node)
    {
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }
}

BST::~BST()
{
    Destroy(root);
}

void BST::Display(BSTNode *nodeptr)
{
    if (nodeptr == NULL)
    {
        return;
    }

    Display(nodeptr->left);
    cout << nodeptr->SerialNumber << endl;
    cout << nodeptr->Url << endl;
    Display(nodeptr->right);
}

bool findword(string str,const char word[]) // Change the parameter type
{
    char arr[200];
    int q = 0;
    while (q != str.length())
    {
        arr[q] = str[q];
        q++;
    }
    arr[q] = '\0';

    int i = 0;
    int count = 0;
    bool chk = false;
    while (arr[i] != '\0')
    {
        int j = 0;

        if (arr[i] == word[j])
        {
            while (true)
            {
                if (arr[i] == word[j])
                {
                    i++;
                    j++;
                    count++;
                }
                else
                {
                    break;
                }
            }

            if (count == strlen(word))
            {
                chk = true;
            }
            else
            {
                count = 0;
            }
        }

        if (chk == true)
        {
            break;
        }

        i++;
    }

    if (chk == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Search(BSTNode *nodeptr,const char word[]) 
{
    if (nodeptr == NULL)
    {
        return;
    }
    else
    {
        Search(nodeptr->left, word);

        if (findword(nodeptr->Description, word))
        {
            cout << nodeptr->Url << endl;
        }

        Search(nodeptr->right, word);
    }
}

void BST::Searchtemp(const char word[]) 
{
    Search(root, word);
}

void Implementation()
{
    cout << "\n---------------------------" << endl;
    cout << "Please Enter the filename: ";
    string filename;
    cin >> filename;

    fstream myfile;
    myfile.open(filename, ios::in);

    BST bst;

    if (myfile.is_open())
    {
        cout << "\nFile loaded successfully!" << endl;
        cout << "---------------------------" << endl;

        string data;

        int i = 0;

        BSTNode *bstnode = new BSTNode;

        int sno;
        string Url;
        string Description;

        
        vector<string> keywords;

        while (getline(myfile, data))
        {
            if (i == 0)
            {
                Url = data;

                int num;
                if (data[1] == ' ')
                {
                    num = data[0] - 48;
                }
                else if (data[1] != ' ' && data[0] == '1')
                {
                    num = (data[0] + data[1]) - 87;
                }
                else if (data[1] != ' ' && data[0] == '2')
                {
                    num = (data[0] + data[1]) - 78;
                }
                else if (data[1] != ' ' && data[0] == '3')
                {
                    num = (data[0] + data[1]) - 69;
                }
                else if (data[1] != ' ' && data[0] == '4')
                {
                    num = (data[0] + data[1]) - 60;
                }
                else if (data[1] != ' ' && data[0] == '5')
                {
                    num = (data[0] + data[1]) - 51;
                }

                sno = num;

                i++;
                continue;
            }
            else if (i == 1)
            {
                Description = data;
                keywords.push_back(Description); 

                i++;
                continue;
            }
            else if (i == 2)
            {
                i = 0;
            }

            bst.Insert(sno, Url, Description);
        }

        myfile.close();

        
        int randomIndex = rand() % keywords.size();
        string randomKeyword = keywords[randomIndex];

        cout << "Randomly selected keyword: " << randomKeyword << endl;
        cout << "---------------------------" << endl;

        
        const char* randomKeywordChar = randomKeyword.c_str();
        bst.Searchtemp(randomKeywordChar);
        cout << "_______________________" << endl;
    }
    else
    {
        cout << "File not found!" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    while (true)
    {
        cout << "\nPress: " << endl;
        cout << "1: To Search" << endl;
        cout << "2: To Terminate" << endl;
        cout << "Enter: ";
        int chk;
        cin >> chk;

        if (chk == 1)
        {
            char word[100];
            cout << "\n-----------------------" << endl;
            cout << "Enter Word: ";
            cin >> word;
            cout << "-----------------------" << endl;
            cout << "\n";
            bst.Searchtemp(word);
            cout << "_______________________" << endl;
        }
        else if (chk == 2)
        {
            cout << "\nTerminated!" << endl;
            cout << "_____________\n" << endl;
            break;
        }
    }
}

int main()
{
    Implementation();
    return 0;
}

