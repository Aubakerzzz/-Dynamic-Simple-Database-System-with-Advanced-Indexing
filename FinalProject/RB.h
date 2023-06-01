#pragma once



#include <iostream>
#include<string.h>
#include<fstream>
using namespace std;
template <typename myType>
class redblackNode {
public:
    myType data;
    redblackNode<myType>* parent;
    redblackNode<myType>* left;
    redblackNode<myType>* right;
    int color;
};


template <typename myType>
class RedBlackTree {
public:
    //private:
    redblackNode<myType>* root;
    redblackNode<myType>* nullNode;

    redblackNode<myType>* SearchTreeFunc(redblackNode<myType>* node, myType key) {
        if (node == nullNode || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return SearchTreeFunc(node->left, key);
        }
        return SearchTreeFunc(node->right, key);
    }

   
    void Balance(redblackNode<myType>* x) {
        redblackNode<myType>* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->left->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }   
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void redblackTransplant(redblackNode<myType>* u, redblackNode<myType>* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void delRedBlackFunc(redblackNode<myType>* node, myType key) {
        redblackNode<myType>* z = nullNode;
        redblackNode<myType>* x, * y;
        while (node != nullNode) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == nullNode) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == nullNode) {
            x = z->right;
            redblackTransplant(z, z->right);
        }
        else if (z->right == nullNode) {
            x = z->left;
            redblackTransplant(z, z->left);
        }
        else {
            y = Min(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                redblackTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            redblackTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            Balance(x);
        }
    }




    


    RedBlackTree() {
        nullNode = new redblackNode<myType>;
        nullNode->color = 0;
        nullNode->left = nullptr;
        nullNode->right = nullptr;
        root = nullNode;
    }



    redblackNode<myType>* searchTree(myType d) {
        return SearchTreeFunc(this->root, d);
    }

    redblackNode<myType>* Min(redblackNode<myType>* node) {
        while (node->left != nullNode) {
            node = node->left;
        }
        return node;
    }

    redblackNode<myType>* Max(redblackNode<myType>* node) {
        while (node->right != nullNode) {
            node = node->right;
        }
        return node;
    }

    redblackNode<myType>* successor(redblackNode<myType>* x) {
        if (x->right != nullNode) {
            return Min(x->right);
        }

        redblackNode<myType>* y = x->parent;
        while (y != nullNode && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    redblackNode<myType>* predecessor(redblackNode<myType>* x) {
        if (x->left != nullNode) {
            return Max(x->left);
        }

        redblackNode<myType>* y = x->parent;
        while (y != nullNode && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(redblackNode<myType>* x) {
        redblackNode<myType>* y = x->right;
        x->right = y->left;
        if (y->left != nullNode) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(redblackNode<myType>* x) {
        redblackNode<myType>* y = x->left;
        x->left = y->right;
        if (y->right != nullNode) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(myType d) {
        redblackNode<myType>* node = new redblackNode<myType>;
        node->parent = nullptr;
        node->data = d;
        node->left = nullNode;
        node->right = nullNode;
        node->color = 1;

        redblackNode<myType>* y = nullptr;
        redblackNode<myType>* x = this->root;

        while (x != nullNode) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }




        redblackNode<myType>* u;
        while (node->parent->color == 1) {
            if (node->parent == node->parent->parent->right) {
                u = node->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    leftRotate(node->parent->parent);
                }
            }
            else {
                u = node->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rightRotate(node->parent->parent);
                }
            }
            if (node == root) {
                break;
            }
        }
        root->color = 0;
    }

    redblackNode<myType>* getRoot() {
        return this->root;
    }

    void deleteredblackNode(myType data) {
        delRedBlackFunc(this->root, data);
    }

   
        

    void pointSearch(int id) {
        redblackNode<myType>* node = this->searchTree(id);
        if (node == nullNode) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            cout << endl;
           
            // reading the reference from the files
            string references[2];
            fstream myFile;
            ifstream DataFile;
            myFile.open("RBStorage/RBIn" + to_string(id) + ".txt");
            while (!myFile.eof())
            {
                getline(myFile, references[0]);
                getline(myFile, references[1]);
                //myFile.close();
                if (references[0] == "")
                {
                    break;
                }
                // reading the file to extract the data
                DataFile.open(references[0]);
                int referencedLineNumber = stoi(references[1]);
                int lineNum = 1;
                string temp;
                while (getline(DataFile, temp)) {
                    if (lineNum == referencedLineNumber)
                        break;
                    else
                        lineNum++;
                }
                DataFile.close();
                //parsing the line to get the data
                temp += ",";
                string array[6];
                int counter = 0;
                string data = "";
                for (int l = 0; l < temp.length(); l++) {
                    if (temp[l] == ',') {
                        array[counter++] = data;
                        data = "";
                    }
                    else {
                        data += temp[l];
                    }
                }
                cout << "ID: " << array[0] << endl;
                cout << "Year: " << array[1] << endl;
                cout << "Cause Name: " << array[2] << endl;
                cout << "State: " << array[3] << endl;
                cout << "Deaths: " << array[4] << endl;
                cout << "Age-adjusted Death Rate: " << array[5] << endl;
                cout << endl << endl;
            }

            myFile.close();
        }
    }

    void rangeSearch(int startID, int endID) {
        for (int i = startID; i <= endID; i++) {
            pointSearch(i);
        }
    }

    void updateNode(myType id, string field, string old_val, string new_val) {
        redblackNode<myType>* node = this->searchTree(id);
        if (node == nullNode) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // reading the reference from the files
            string references[2];
            fstream myFile;
            myFile.open("RBStorage/RBIn" + to_string(id) + ".txt");
            getline(myFile, references[0]);
            getline(myFile, references[1]);
            myFile.close();
            // reading the actual file to get the total number of lines
            myFile.open(references[0]);
            string temp;
            int size = 0;
            while (getline(myFile, temp)) {
                size++;
            }
            myFile.close();
            // reading the data from file into string
            string* lines = new string[size];
            int iter = 0;
            myFile.open(references[0]);
            while (getline(myFile, temp)) {
                lines[iter++] = temp;
            }
            myFile.close();
            // getting the line that we want to update
            string currLine = lines[stoi(references[1]) - 1];
            // parsing the line
            currLine += ",";
            string array[6];
            int counter = 0;
            string data = "";
            for (int l = 0; l < currLine.length(); l++) {
                if (currLine[l] == ',') {
                    array[counter++] = data;
                    data = "";
                }
                else {
                    data += currLine[l];
                }
            }

            bool checkflag = false;

            if (field == "Year") {
                if (array[1] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[1] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Year!" << endl;
                }
            }
            else if (field == "Cause Name") {
                if (array[2] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[2] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Cause Name!" << endl;
                }
            }
            else if (field == "State") {
                if (array[3] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[3] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old State!" << endl;
                }
            }
            else if (field == "Deaths") {
                if (array[4] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[4] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Deaths!" << endl;
                }
            }
            else if (field == "Age-adjusted Death Rate") {
                if (array[5] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[5] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Age-adjusted Death Rate!" << endl;
                }
            }
            else {
                cout << "\nInvalid Field Name!" << endl;
            }
            // check if any updates occurred in the data
            if (checkflag) {
                //updating the data in lines array
                lines[stoi(references[1]) - 1] = array[0] + "," + array[1] + "," + array[2] + "," + array[3] + "," + array[4] + "," + array[5];
                // re-writing all the lines into .csv file
                ofstream newFile(references[0]);
                for (int i = 0; i < size; i++) {
                    newFile << lines[i] << endl;
                }
                newFile.close();
            }
            // releasing the memory
            delete[] lines;
        }
        cout << endl;
    }

    void delNode(myType id) {
        redblackNode<myType>* node = this->searchTree(id);
        if (node == nullNode) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // deleting the node from AVL
            deleteredblackNode(id);
            // reading the reference from the files
            string references[2];
            fstream myFile;
            myFile.open("AVLStorage/AVLIn" + to_string(id) + ".txt");
            getline(myFile, references[0]);
            getline(myFile, references[1]);
            myFile.close();
            // reading the actual file to get the total number of lines
            myFile.open(references[0]);
            string temp;
            int size = 0;
            while (getline(myFile, temp)) {
                size++;
            }
            myFile.close();
            // reading the data from file into string
            string* lines = new string[size];
            int iter = 0;
            myFile.open(references[0]);
            while (getline(myFile, temp) && iter < size) {
                lines[iter++] = temp;
            }
            myFile.close();
            //deleting the node from .csv
            ofstream newFile(references[0]);
            for (int i = 0; i < size; i++) {
                if (i != stoi(references[1]) - 1)
                    newFile << lines[i] << endl;
            }
            newFile.close();
            // deleting the node form directory
            string path = "RBStorage/RBIn" + to_string(id) + ".txt";
            remove(path.c_str());
            cout << "Node Deleted Successfully!" << endl;
        }
        cout << endl;
    }

};




class redblackNodeString {
public:
    string data;
    redblackNodeString* parent;
    redblackNodeString* left;
    redblackNodeString* right;
    int color;
};



class RedBlackTreeString {
public:
    //private:
    redblackNodeString* root;
    redblackNodeString* nullNode;

    redblackNodeString* SearchTreeFunc(redblackNodeString* node, string key) {
        if (node == nullNode || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return SearchTreeFunc(node->left, key);
        }
        return SearchTreeFunc(node->right, key);
    }


    void Balance(redblackNodeString* x) {
        redblackNodeString* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->left->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void redblackTransplant(redblackNodeString* u, redblackNodeString* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void delRedBlackFunc(redblackNodeString* node, string key) {
        redblackNodeString* z = nullNode;
        redblackNodeString* x, * y;
        while (node != nullNode) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == nullNode) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == nullNode) {
            x = z->right;
            redblackTransplant(z, z->right);
        }
        else if (z->right == nullNode) {
            x = z->left;
            redblackTransplant(z, z->left);
        }
        else {
            y = Min(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                redblackTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            redblackTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            Balance(x);
        }
    }







    RedBlackTreeString() {
        nullNode = new redblackNodeString;
        nullNode->color = 0;
        nullNode->left = nullptr;
        nullNode->right = nullptr;
        root = nullNode;
    }



    redblackNodeString* searchTree(string d) {
        return SearchTreeFunc(this->root, d);
    }

    redblackNodeString* Min(redblackNodeString* node) {
        while (node->left != nullNode) {
            node = node->left;
        }
        return node;
    }

    redblackNodeString* Max(redblackNodeString* node) {
        while (node->right != nullNode) {
            node = node->right;
        }
        return node;
    }

    redblackNodeString* successor(redblackNodeString* x) {
        if (x->right != nullNode) {
            return Min(x->right);
        }

        redblackNodeString* y = x->parent;
        while (y != nullNode && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    redblackNodeString* predecessor(redblackNodeString* x) {
        if (x->left != nullNode) {
            return Max(x->left);
        }

        redblackNodeString* y = x->parent;
        while (y != nullNode && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(redblackNodeString* x) {
        redblackNodeString* y = x->right;
        x->right = y->left;
        if (y->left != nullNode) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(redblackNodeString* x) {
        redblackNodeString* y = x->left;
        x->left = y->right;
        if (y->right != nullNode) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(string d) {
        redblackNodeString* node = new redblackNodeString;
        node->parent = nullptr;
        node->data = d;
        node->left = nullNode;
        node->right = nullNode;
        node->color = 1;

        redblackNodeString* y = nullptr;
        redblackNodeString* x = this->root;

        while (x != nullNode) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }




        redblackNodeString* u;
        while (node->parent->color == 1) {
            if (node->parent == node->parent->parent->right) {
                u = node->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    leftRotate(node->parent->parent);
                }
            }
            else {
                u = node->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rightRotate(node->parent->parent);
                }
            }
            if (node == root) {
                break;
            }
        }
        root->color = 0;
    }

    redblackNodeString* getRoot() {
        return this->root;
    }

    void deleteredblackNode(string data) {
        delRedBlackFunc(this->root, data);
    }




    void pointSearch(std::string id) {
        redblackNodeString* node = this->searchTree(id);
        if (node == nullNode) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            cout << endl;

            // reading the reference from the files
            string references[2];
            fstream myFile;
            ifstream DataFile;
            myFile.open("RBStorage/RBIn" + (id) + ".txt");
            while (!myFile.eof())
            {
                getline(myFile, references[0]);
                getline(myFile, references[1]);
                //myFile.close();
                if (references[0] == "")
                {
                    break;
                }
                // reading the file to extract the data
                DataFile.open(references[0]);
                int referencedLineNumber = stoi(references[1]);
                int lineNum = 1;
                string temp;
                while (getline(DataFile, temp)) {
                    if (lineNum == referencedLineNumber)
                        break;
                    else
                        lineNum++;
                }
                DataFile.close();
                //parsing the line to get the data
                temp += ",";
                string array[6];
                int counter = 0;
                string data = "";
                for (int l = 0; l < temp.length(); l++) {
                    if (temp[l] == ',') {
                        array[counter++] = data;
                        data = "";
                    }
                    else {
                        data += temp[l];
                    }
                }
                cout << "ID: " << array[0] << endl;
                cout << "Year: " << array[1] << endl;
                cout << "Cause Name: " << array[2] << endl;
                cout << "State: " << array[3] << endl;
                cout << "Deaths: " << array[4] << endl;
                cout << "Age-adjusted Death Rate: " << array[5] << endl;
                cout << endl << endl;
            }

            myFile.close();
        }
    }

   

    void updateNode(string id, string field, string old_val, string new_val) {
        redblackNodeString* node = this->searchTree(id);
        if (node == nullNode) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // reading the reference from the files
            string references[2];
            fstream myFile;
            myFile.open("RBStorage/RBIn" + (id) + ".txt");
            getline(myFile, references[0]);
            getline(myFile, references[1]);
            myFile.close();
            // reading the actual file to get the total number of lines
            myFile.open(references[0]);
            string temp;
            int size = 0;
            while (getline(myFile, temp)) {
                size++;
            }
            myFile.close();
            // reading the data from file into string
            string* lines = new string[size];
            int iter = 0;
            myFile.open(references[0]);
            while (getline(myFile, temp)) {
                lines[iter++] = temp;
            }
            myFile.close();
            // getting the line that we want to update
            string currLine = lines[stoi(references[1]) - 1];
            // parsing the line
            currLine += ",";
            string array[6];
            int counter = 0;
            string data = "";
            for (int l = 0; l < currLine.length(); l++) {
                if (currLine[l] == ',') {
                    array[counter++] = data;
                    data = "";
                }
                else {
                    data += currLine[l];
                }
            }

            bool checkflag = false;

            if (field == "Year") {
                if (array[1] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[1] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Year!" << endl;
                }
            }
            else if (field == "Cause Name") {
                if (array[2] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[2] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Cause Name!" << endl;
                }
            }
            else if (field == "State") {
                if (array[3] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[3] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old State!" << endl;
                }
            }
            else if (field == "Deaths") {
                if (array[4] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[4] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Deaths!" << endl;
                }
            }
            else if (field == "Age-adjusted Death Rate") {
                if (array[5] == old_val) {
                    cout << "Node Updated Successfully!" << endl;
                    array[5] = new_val;
                    checkflag = true;
                }
                else {
                    cout << "Invalid Old Age-adjusted Death Rate!" << endl;
                }
            }
            else {
                cout << "\nInvalid Field Name!" << endl;
            }
            // check if any updates occurred in the data
            if (checkflag) {
                //updating the data in lines array
                lines[stoi(references[1]) - 1] = array[0] + "," + array[1] + "," + array[2] + "," + array[3] + "," + array[4] + "," + array[5];
                // re-writing all the lines into .csv file
                ofstream newFile(references[0]);
                for (int i = 0; i < size; i++) {
                    newFile << lines[i] << endl;
                }
                newFile.close();
            }
            // releasing the memory
            delete[] lines;
        }
        cout << endl;
    }

    void delNode(string id) {
        redblackNodeString* node = this->searchTree(id);
        if (node == nullNode) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // deleting the node from AVL
            deleteredblackNode(id);
            // reading the reference from the files
            string references[2];
            fstream myFile;
            myFile.open("AVLStorage/AVLIn" + id + ".txt");
            getline(myFile, references[0]);
            getline(myFile, references[1]);
            myFile.close();
            // reading the actual file to get the total number of lines
            myFile.open(references[0]);
            string temp;
            int size = 0;
            while (getline(myFile, temp)) {
                size++;
            }
            myFile.close();
            // reading the data from file into string
            string* lines = new string[size];
            int iter = 0;
            myFile.open(references[0]);
            while (getline(myFile, temp) && iter < size) {
                lines[iter++] = temp;
            }
            myFile.close();
            //deleting the node from .csv
            ofstream newFile(references[0]);
            for (int i = 0; i < size; i++) {
                if (i != stoi(references[1]) - 1)
                    newFile << lines[i] << endl;
            }
            newFile.close();
            // deleting the node form directory
            string path = "RBStorage/RBIn" + (id) + ".txt";
            remove(path.c_str());
            cout << "Node Deleted Successfully!" << endl;
        }
        cout << endl;
    }

};