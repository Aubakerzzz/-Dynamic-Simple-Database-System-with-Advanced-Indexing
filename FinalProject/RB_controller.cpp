#include "RB_controller.h"

// function to perform other functionalities on the tree
template <typename myType>
void functionalities(RedBlackTree<myType>* tree, string for_where) {
    while (true) {
        int option;
        cout << "Enter(1) for Point Search" << endl
            << "Enter(2) for Range Search" << endl
            << "Enter(3) to update the specific node" << endl
            << "Enter(4) to delete the node" << endl
            << "Enter (5) for where Clause"<< endl
            << "Enter(6) to exit" << endl
            << "Option: ";
        cin >> option;
        if (option == 1) {
            cout << "****POINT SEARCH****" << endl;
            int id;
            cout << "Enter the ID: ";
            cin >> id;
            tree->pointSearch(id);
        }
        else if (option == 2) {
            cout << "****RANGE SEARCH****" << endl;
            int startID;
            int endID;
            cout << "Enter the Start ID of Range: ";
            cin >> startID;
            cout << "Enter the End ID of Range: ";
            cin >> endID;
            if (startID <= endID)
                tree->rangeSearch(startID, endID);
            else
                cout << "Invalid Range!" << endl << endl;
        }
        else if (option == 3) {
            cout << "****UPDATE NODE****" << endl;
            int id;
            cout << "Enter the ID: ";
            cin >> id;
            cin.clear();
            cin.ignore();
            string field;
            cout << "Enter Field: ";
            getline(cin, field);
            string old_val;
            cout << "Enter old value: ";
            getline(cin, old_val);
            string new_val;
            cout << "Enter new value: ";
            getline(cin, new_val);
            tree->updateNode(id, field, old_val, new_val);
        }
        else if (option == 4) {
            cout << "****DELETE NODE****" << endl;
            int id;
            cout << "Enter the ID: ";
            cin >> id;
            tree->delNode(id);
        }
        else if (option == 5) {
            cout << "****WHERE CLAUSE USAGE INFO****" << endl
                //selecting clause
                << "SELECT WHERE " << for_where << " = (?)" << endl
                // range 
                << "SELECT WHERE " << for_where << " >= (?) AND " << for_where << " <= (?)" << endl
                //update prev value with new value input by user 
                << "UPDATE (FIELD_NAME) = (?) WHERE " << for_where << " = (?) AND (FIELD_NAME) = (?)" << endl
                //  deleting the value enter by user 
                << "DELETE WHERE " << for_where << " = (?)" << endl;
            string clause;
            cout << "Enter clause: ";
            cin.clear();
            cin.ignore();
            getline(cin, clause);
            clause += " ";
            int numTokens = 0;
            // getting the number of tokens
            for (int i = 0; i < clause.length(); i++) {
                if (clause[i] == ' ')
                    numTokens++;
            }
            // point search and delete
            if (numTokens == 5) {
                string tokens[5];
                int counter = 0;
                string temp = "";
                for (int i = 0; i < clause.length(); i++) {
                    if (clause[i] == ' ') {
                        tokens[counter++] = temp;
                        temp = "";
                    }
                    else {
                        temp += clause[i];
                    }
                }
                // check if it is search clause 
                if (tokens[0] == "SELECT") {
                    tree->pointSearch(stoi(tokens[4]));
                }

                else if (tokens[0] == "DELETE") {
                    tree->delNode(stoi(tokens[4]));
                }
                else
                    cout << "Invalid Clause!" << endl;
            }
            // range search
            else if (numTokens == 9) {
                string tokens[9];
                int counter = 0;
                string temp = "";
                for (int i = 0; i < clause.length(); i++) {
                    if (clause[i] == ' ') {
                        tokens[counter++] = temp;
                        temp = "";
                    }
                    else {
                        temp += clause[i];
                    }
                }
                tree->rangeSearch(stoi(tokens[4]), stoi(tokens[8]));
            }
            // update field
            else if (numTokens == 12) {
                string tokens[12];
                int counter = 0;
                string temp = "";
                for (int i = 0; i < clause.length(); i++) {
                    if (clause[i] == ' ') {
                        tokens[counter++] = temp;
                        temp = "";
                    }
                    else {
                        temp += clause[i];
                    }
                }
                for (int i = 0; i < tokens[1].length(); i++)
                    if (tokens[1][i] == '_')
                        tokens[1][i] = ' ';
                for (int i = 0; i < tokens[9].length(); i++)
                    if (tokens[9][i] == '_')
                        tokens[9][i] = ' ';
                tree->updateNode(stoi(tokens[7]), tokens[1], tokens[11], tokens[3]);
            }
            // invalid clause
            else {
                cout << "Invalid Clause!" << endl;
            }
        }

        else if (option == 6) {
            return;
        }
        else {
            cout << "Invalid Option!" << endl;
        }
    }
}

RedBlackTree<int>* manageDataFiles(int Option) {

    //Creating a node of AVLTree
    RedBlackTree<int>* tree = new RedBlackTree<int>;

    // store the indexed files in given directory
    string avlStorage = "RBStorage";
    // initial file name, ID will be concatenated later
    string file_name = "RBIn";
    // path to read the data files
    string datafiles = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_";
    // reading the files
    for (int i = 1; i <= 10; i++) {
        // flag to ignore the header
        bool flag = true;
        int lineCounter = 1;
        fstream file;
        file.open(datafiles + to_string(i) + ".csv");
        string currLine;
        while (getline(file, currLine)) {
            if (flag) {
                flag = false;
                lineCounter++;
                continue;
            }
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
            // extracting the id from the data
            int ID = stoi(array[Option-1]);
            // inserting the id to tree
            tree->insert(ID);
            // creating file to store the data of the node
            ofstream newFile(avlStorage + "/" + file_name + array[Option - 1] + ".txt",ios::app);
            // file reference to write
            string nameOfFile = datafiles + to_string(i) + ".csv";
            // line number to write
            newFile << nameOfFile << endl;
            newFile << to_string(lineCounter) << endl;
            newFile.close();
            // update the line counter
            lineCounter++;
        }
        file.close();
    }
    return tree;
}



void RBHander(int Option, string for_where) {
    // Object of AVLTree
    RedBlackTree<int>* tree;
    // path where all the file will be stored
    string directoryPath = "RBStorage";
    // checking if the directory exists or not
    struct stat sb;
    // if the directory exist delete the directory and all the files in it 
    if (stat(directoryPath.c_str(), &sb) == 0) {
        //cout << "Directory exist" << endl;
        // deleting the directory and files in it
        string a = "rmdir /s /q " + directoryPath;
        system(a.c_str());
        // creating the directory again
        int status = _mkdir(directoryPath.c_str());
        // reading the given files from the folder
        tree = manageDataFiles(Option);
        functionalities(tree, for_where);
    }
    // if directory do not exist
    else {
        // cout << "Directory do not exist" << endl;
        // create a directory
        int status = _mkdir(directoryPath.c_str());
        // reading the given files from the folder
        tree = manageDataFiles(Option);
        functionalities(tree, for_where);
    }
}


void Stringfunctionalities(RedBlackTreeString* tree, string for_where)
{
    while (true) {

        int option;
        cout << "Enter(1) for Point Search" << endl
            << "Enter(2) for Range Search" << endl
            << "Enter(3) to update the specific node" << endl
            << "Enter(4) to delete the node" << endl
            << "Enter(5) for_where Clause" << endl
            << "Enter(6) to exit" << endl
            << "Option: ";
        cin >> option;
        if (option == 1) {
            cout << "****POINT SEARCH****" << endl;
            std::string id;
            cout << "Enter the Value: ";
            cin.clear();
            cin.ignore();
            getline(cin, id);
            cin.clear();
            cin.ignore();
            tree->pointSearch(id);
        }
        else if (option == 2) {
            cout << "Invalid Range!" << endl << endl;
        }
        else if (option == 3) {
            cout << "****UPDATE NODE****" << endl;
            string id;
            cout << "Enter the ID: ";
            getline(cin, id);
            cin.clear();
            cin.ignore();
            string field;
            cout << "Enter Field: ";
            getline(cin, field);
            string old_val;
            cout << "Enter old value: ";
            getline(cin, old_val);
            string new_val;
            cout << "Enter new value: ";
            getline(cin, new_val);
            tree->updateNode(id, field, old_val, new_val);
        }
        else if (option == 4) {
            cout << "****DELETE NODE****" << endl;
            cin.clear();
            cin.ignore();
            string id;
            cout << "Enter the ID: ";
            getline(cin, id);
            tree->delNode(id);
        }
        else if (option == 5) {
            cout << "****WHERE CLAUSE USAGE INFO****" << endl
                //selecting clause
                << "SELECT WHERE " << for_where << " = (?)" << endl
                // range 
                << "SELECT WHERE " << for_where << " >= (?) AND " << for_where << " <= (?)" << endl
                //update prev value with new value input by user 
                << "UPDATE (FIELD_NAME) = (?) WHERE " << for_where << " = (?) AND (FIELD_NAME) = (?)" << endl
                //  deleting the value enter by user 
                << "DELETE WHERE " << for_where << " = (?)" << endl;
            string clause;
            cout << "Enter clause: ";
            cin.clear();
            cin.ignore();
            getline(cin, clause);
            clause += " ";
            int numTokens = 0;
            // getting the number of tokens
            for (int i = 0; i < clause.length(); i++) {
                if (clause[i] == ' ')
                    numTokens++;
            }
            // point search and delete
            if (numTokens == 5) {
                string tokens[5];
                int counter = 0;
                string temp = "";
                for (int i = 0; i < clause.length(); i++) {
                    if (clause[i] == ' ') {
                        tokens[counter++] = temp;
                        temp = "";
                    }
                    else {
                        temp += clause[i];
                    }
                }
                // check if it is search clause 
                if (tokens[0] == "SELECT") {
                    tree->pointSearch((tokens[4]));
                }

                else if (tokens[0] == "DELETE") {
                    tree->delNode((tokens[4]));
                }
                else
                    cout << "Invalid Clause!" << endl;
            }

            // update field
            else if (numTokens == 12) {
                string tokens[12];
                int counter = 0;
                string temp = "";
                for (int i = 0; i < clause.length(); i++) {
                    if (clause[i] == ' ') {
                        tokens[counter++] = temp;
                        temp = "";
                    }
                    else {
                        temp += clause[i];
                    }
                }
                for (int i = 0; i < tokens[1].length(); i++)
                    if (tokens[1][i] == '_')
                        tokens[1][i] = ' ';
                for (int i = 0; i < tokens[9].length(); i++)
                    if (tokens[9][i] == '_')
                        tokens[9][i] = ' ';
                tree->updateNode((tokens[7]), tokens[1], tokens[11], tokens[3]);
            }
            // invalid clause
            else {
                cout << "Invalid Clause!" << endl;
            }
        }

        else if (option == 6) {
            return;
        }
        else {
            cout << "Invalid Option!" << endl;
        }
    }
}


RedBlackTreeString* manageStringRTreeDataFiles(int Option) {

    //Creating a node of AVLTree
    RedBlackTreeString* tree = new RedBlackTreeString;

    // store the indexed files in given directory
    string avlStorage = "RBStorage";
    // initial file name, ID will be concatenated later
    string file_name = "RBIn";
    // path to read the data files
    string datafiles = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_";
    // reading the files
    for (int i = 1; i <= 10; i++) {
        // flag to ignore the header
        bool flag = true;
        int lineCounter = 1;
        fstream file;
        file.open(datafiles + to_string(i) + ".csv");
        string currLine;
        while (getline(file, currLine)) {
            if (flag) {
                flag = false;
                lineCounter++;
                continue;
            }
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
            // extracting the id from the data
            
            // inserting the id to tree
            tree->insert(array[Option-1]);
            // creating file to store the data of the node
            ofstream newFile(avlStorage + "/" + file_name + array[Option - 1] + ".txt", ios::app);
            // file reference to write
            string nameOfFile = datafiles + to_string(i) + ".csv";
            // line number to write
            newFile << nameOfFile << endl;
            newFile << to_string(lineCounter) << endl;
            newFile.close();
            // update the line counter
            lineCounter++;
        }
        file.close();
    }
    return tree;


}


void StringRTreeHandler(int Option, string for_where) {
    // Object of AVLTree
    RedBlackTreeString* tree;
    // path where all the file will be stored
    string directoryPath = "RBStorage";
    // checking if the directory exists or not
    struct stat sb;
    // if the directory exist delete the directory and all the files in it 
    if (stat(directoryPath.c_str(), &sb) == 0) {
        //cout << "Directory exist" << endl;
        // deleting the directory and files in it
        string a = "rmdir /s /q " + directoryPath;
        system(a.c_str());
        // creating the directory again
        int status = _mkdir(directoryPath.c_str());
        // reading the given files from the folder
        tree = manageStringRTreeDataFiles(Option);
        Stringfunctionalities(tree, for_where);
    }
    // if directory do not exist
    else {
        // cout << "Directory do not exist" << endl;
        // create a directory
        int status = _mkdir(directoryPath.c_str());
        // reading the given files from the folder
        tree = manageStringRTreeDataFiles(Option);
        Stringfunctionalities(tree, for_where);
    }
}