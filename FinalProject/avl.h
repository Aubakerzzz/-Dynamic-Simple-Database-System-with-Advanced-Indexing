#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

class AVLNode {
public:
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int k)
    {
        key = k;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
private:
    AVLNode* root;

    //Calculating Height
    int Height(AVLNode* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    // Right Rotation
    AVLNode* rightRotation(AVLNode* L1)
    {
        AVLNode* L2 = L1->left;
        AVLNode* temp = L2->right;

        L2->right = L1;
        L1->left = temp;

        L1->height = max(Height(L1->left), Height(L1->right)) + 1;
        L2->height = max(Height(L2->left), Height(L2->right)) + 1;
        return L2;
    }

    // Left Rotation
    AVLNode* leftRotation(AVLNode* L1)
    {
        AVLNode* L2 = L1->right;
        AVLNode* temp = L2->left;

        L2->left = L1;
        L1->right = temp;

        L1->height = max(Height(L1->left), Height(L1->right)) + 1;
        L2->height = max(Height(L2->left), Height(L2->right)) + 1;
        return L2;
    }

    //RL Rotation
    AVLNode* RLrotation(AVLNode* L1)
    {
        L1->left = leftRotation(L1->left);
        return rightRotation(L1);
    }

    //LR Rotation
    AVLNode* LRrotation(AVLNode* L1)
    {
        L1->right = rightRotation(L1->right);
        return leftRotation(L1);
    }

    // Get balance factor
    int getBalanceFactor(AVLNode* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return Height(node->left) - Height(node->right);
    }

    // Insert a AVLNode
    AVLNode* insertAVLNode(AVLNode* node, int k)
    {
        if (node == NULL)
        {
            node = new AVLNode(k);
            return node;
        }

        else if (k < node->key)
        {
            node->left = insertAVLNode(node->left, k);
        }

        else if (k > node->key)
        {
            node->right = insertAVLNode(node->right, k);
        }

        else
        {
            return node;
        }

        node->height = 1 + max(Height(node->left), Height(node->right));

        if (getBalanceFactor(node) > 1) 		//It means key is added to the left subtree
        {
            if (k < node->left->key)			//Due to insertion at left side of left subtree
            {
                return rightRotation(node);
            }

            else if (k > node->left->key)		//Due to insertion at right side of left subtree
            {
                return RLrotation(node);
            }
        }

        else if (getBalanceFactor(node) < -1) 	//It means key is added to the right subtree
        {
            if (k > node->right->key)			//Due to insertion at right side of right subtree
            {
                return leftRotation(node);
            }

            else if (k < node->right->key) 		//Due  to insertion at left side of right subtree
            {
                return LRrotation(node);
            }
        }

        return node;
    }

    // Getting Node with minimum value
    AVLNode* AVLNodeWithMimumValue(AVLNode* node)
    {
        AVLNode* temp = node;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }

    //Deleting Node
    AVLNode* deleteAVLNode(AVLNode* node, int k) {
        if (node == NULL)
        {
            return node;
        }

        else if (k < node->key)
        {
            node->left = deleteAVLNode(node->left, k);
        }

        else if (k > node->key)
        {
            node->right = deleteAVLNode(node->right, k);
        }

        else
        {
            if (!node->left || !node->right)
            {
                AVLNode* temp;
                if (node->left)
                {
                    temp = node->left;
                }

                else
                {
                    temp = node->right;
                }

                if (temp == NULL)
                {
                    temp = node;
                    node = NULL;
                }

                else
                {
                    *node = *temp;
                }
                delete temp;
            }

            else
            {
                AVLNode* temp = AVLNodeWithMimumValue(node->right);
                node->key = temp->key;
                node->right = deleteAVLNode(node->right, temp->key);
            }
        }

        if (node == NULL)
        {
            return node;
        }

        node->height = 1 + max(Height(node->left), Height(node->right));

        if (getBalanceFactor(node) > 1)
        {
            if (getBalanceFactor(node->left) >= 0)
            {
                return rightRotation(node);
            }

            else
            {
                return RLrotation(node);
            }
        }

        else if (getBalanceFactor(node) < -1)
        {
            if (getBalanceFactor(node->right) <= 0)
            {
                return leftRotation(node);
            }

            else
            {
                return LRrotation(node);
            }
        }
        else
        {
            return node;
        }
    }

    // searching the node in AVL Tree
    AVLNode* searching(AVLNode* node, int key) {
        if (node == NULL) {
            return NULL;
        }
        else if (node->key == key) {
            return node;
        }
        else if (key < node->key)
            return searching(node->left, key);
        else
            return searching(node->right, key);
    }

    // Printing in Pre-Order
    void print(AVLNode* AVLNode)
    {
        if (AVLNode == NULL)
        {
            return;
        }

        cout << AVLNode->key << " ";

        print(AVLNode->left);

        print(AVLNode->right);
    }

public:
    // constructor
    AVLTree() {
        root = NULL;
    }

    // insert node in tree
    void insertNode(int key) {
        this->root = this->insertAVLNode(this->root, key);
    }

    // delete node from tree
    void deleteNode(int key) {
        this->root = this->deleteAVLNode(this->root, key);
    }

    // print in pre-order
    void printInPreOrder() {
        this->print(this->root);
    }

    // find the particular node in tree
    void search(int key) {
        AVLNode* node = this->searching(this->root, key);
        if (node == NULL) {
            cout << "Node not found!" << endl;
        }
        else {
            cout << "Node found!" << endl;
            cout << "Key: " << node->key << endl;
            cout << "Height: " << node->height << endl;
        }
        cout << endl;
    }

    // function for point search
    void pointSearch(int id) {
        AVLNode* node = this->searching(this->root, id);
        if (node == NULL) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            cout << endl;
            // reading the reference from the files
            string references[2];
            fstream myFile;
            ifstream DataFile;
            myFile.open("AVLStorage/AVLIn" + to_string(id) + ".txt");
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

    // function for range search
    void rangeSearch(int startID, int endID) {
        for (int i = startID; i <= endID; i++) {
            pointSearch(i);
        }
    }

    // function for updating the node
    void updateNode(int id, string field, string old_val, string new_val) {
        AVLNode* node = this->searching(this->root, id);
        if (node == NULL) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
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

    // function for deleting the particular node
    void delNode(int id) {
        AVLNode* node = this->searching(this->root, id);
        if (node == NULL) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // deleting the node from AVL
            deleteNode(id);
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
                if(i != stoi(references[1]) - 1)
                    newFile << lines[i] << endl;
            }
            newFile.close();
            // deleting the node form directory
            string path = "AVLStorage/AVLIn" + to_string(id) + ".txt";
            remove(path.c_str());
            cout << "Node Deleted Successfully!" << endl;
        }
        cout << endl;
    }
};

class AVLNodeString {
public:
    string key;
    int height;
    AVLNodeString* left;
    AVLNodeString* right;
    AVLNodeString(string k)
    {
        key = k;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLStringTree {
private:
    AVLNodeString* root;

    //Calculating Height
    int Height(AVLNodeString* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    // Right Rotation
    AVLNodeString* rightRotation(AVLNodeString* L1)
    {
        AVLNodeString* L2 = L1->left;
        AVLNodeString* temp = L2->right;

        L2->right = L1;
        L1->left = temp;

        L1->height = max(Height(L1->left), Height(L1->right)) + 1;
        L2->height = max(Height(L2->left), Height(L2->right)) + 1;
        return L2;
    }

    // Left Rotation
    AVLNodeString* leftRotation(AVLNodeString* L1)
    {
        AVLNodeString* L2 = L1->right;
        AVLNodeString* temp = L2->left;

        L2->left = L1;
        L1->right = temp;

        L1->height = max(Height(L1->left), Height(L1->right)) + 1;
        L2->height = max(Height(L2->left), Height(L2->right)) + 1;
        return L2;
    }

    //RL Rotation
    AVLNodeString* RLrotation(AVLNodeString* L1)
    {
        L1->left = leftRotation(L1->left);
        return rightRotation(L1);
    }

    //LR Rotation
    AVLNodeString* LRrotation(AVLNodeString* L1)
    {
        L1->right = rightRotation(L1->right);
        return leftRotation(L1);
    }

    // Get balance factor
    int getBalanceFactor(AVLNodeString* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return Height(node->left) - Height(node->right);
    }

    // Insert a AVLNodeString
    AVLNodeString* insertAVLNode(AVLNodeString* node, string k)
    {
        if (node == NULL)
        {
            node = new AVLNodeString(k);
            return node;
        }

        else if (k < node->key)
        {
            node->left = insertAVLNode(node->left, k);
        }

        else if (k > node->key)
        {
            node->right = insertAVLNode(node->right, k);
        }

        else
        {
            return node;
        }

        node->height = 1 + max(Height(node->left), Height(node->right));

        if (getBalanceFactor(node) > 1) 		//It means key is added to the left subtree
        {
            if (k < node->left->key)			//Due to insertion at left side of left subtree
            {
                return rightRotation(node);
            }

            else if (k > node->left->key)		//Due to insertion at right side of left subtree
            {
                return RLrotation(node);
            }
        }

        else if (getBalanceFactor(node) < -1) 	//It means key is added to the right subtree
        {
            if (k > node->right->key)			//Due to insertion at right side of right subtree
            {
                return leftRotation(node);
            }

            else if (k < node->right->key) 		//Due  to insertion at left side of right subtree
            {
                return LRrotation(node);
            }
        }

        return node;
    }

    // Getting Node with minimum value
    AVLNodeString* AVLNodeWithMimumValue(AVLNodeString* node)
    {
        AVLNodeString* temp = node;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }

    //Deleting Node
    AVLNodeString* deleteAVLNode(AVLNodeString* node, string k) {
        if (node == NULL)
        {
            return node;
        }

        else if (k < node->key)
        {
            node->left = deleteAVLNode(node->left, k);
        }

        else if (k > node->key)
        {
            node->right = deleteAVLNode(node->right, k);
        }

        else
        {
            if (!node->left || !node->right)
            {
                AVLNodeString* temp;
                if (node->left)
                {
                    temp = node->left;
                }

                else
                {
                    temp = node->right;
                }

                if (temp == NULL)
                {
                    temp = node;
                    node = NULL;
                }

                else
                {
                    *node = *temp;
                }
                delete temp;
            }

            else
            {
                AVLNodeString* temp = AVLNodeWithMimumValue(node->right);
                node->key = temp->key;
                node->right = deleteAVLNode(node->right, temp->key);
            }
        }

        if (node == NULL)
        {
            return node;
        }

        node->height = 1 + max(Height(node->left), Height(node->right));

        if (getBalanceFactor(node) > 1)
        {
            if (getBalanceFactor(node->left) >= 0)
            {
                return rightRotation(node);
            }

            else
            {
                return RLrotation(node);
            }
        }

        else if (getBalanceFactor(node) < -1)
        {
            if (getBalanceFactor(node->right) <= 0)
            {
                return leftRotation(node);
            }

            else
            {
                return LRrotation(node);
            }
        }
        else
        {
            return node;
        }
    }

    // searching the node in AVL Tree
    AVLNodeString* searching(AVLNodeString* node, string key) {
        if (node == NULL) {
            return NULL;
        }
        else if (node->key == key) {
            return node;
        }
        else if (key < node->key)
            return searching(node->left, key);
        else
            return searching(node->right, key);
    }

    // Printing in Pre-Order
    void print(AVLNodeString* AVLNodeString)
    {
        if (AVLNodeString == NULL)
        {
            return;
        }

        cout << AVLNodeString->key << " ";

        print(AVLNodeString->left);

        print(AVLNodeString->right);
    }

public:
    // constructor
    AVLStringTree() {
        root = NULL;
    }

    // insert node in tree
    void insertNode(string key) {
        this->root = this->insertAVLNode(this->root, key);
    }

    // delete node from tree
    void deleteNode(string key) {
        this->root = this->deleteAVLNode(this->root, key);
    }

    // print in pre-order
    void printInPreOrder() {
        this->print(this->root);
    }

    // find the particular node in tree
    void search(string key) {
        AVLNodeString* node = this->searching(this->root, key);
        if (node == NULL) {
            cout << "Node not found!" << endl;
        }
        else {
            cout << "Node found!" << endl;
            cout << "Key: " << node->key << endl;
            cout << "Height: " << node->height << endl;
        }
        cout << endl;
    }

    // function for point search
    void pointSearch(string id) {
        AVLNodeString* node = this->searching(this->root, id);
        if (node == NULL) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            cout << endl;
            // reading the reference from the files
            string references[2];
            fstream myFile;
            ifstream DataFile;
            myFile.open("AVLStorage/AVLIn" + (id) + ".txt");
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

    // function for range search
  

    // function for updating the node
    void updateNode(string id, string field, string old_val, string new_val) {
        AVLNodeString* node = this->searching(this->root, id);
        if (node == NULL) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // reading the reference from the files
            string references[2];
            fstream myFile;
            myFile.open("AVLStorage/AVLIn" + (id) + ".txt");
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

    // function for deleting the particular node
    void delNode(string id) {
        AVLNodeString* node = this->searching(this->root, id);
        if (node == NULL) {
            cout << "Node-" << id << " not found!" << endl;
        }
        else {
            // deleting the node from AVL
            deleteNode(id);
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
            string path = "AVLStorage/AVLIn" + (id) + ".txt";
            remove(path.c_str());
            cout << "Node Deleted Successfully!" << endl;
        }
        cout << endl;
    }
};