#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include"avl_controller.h"
#include"BTree_controller.h"
#include"RB_controller.h"
using namespace std;



int main() {

    while (true) {
        // creating the index
        int index;
        cout << "Enter(1) for B tree index" << endl
            << "Enter(2) for AVL tree index" << endl
            << "Enter(3) for Red-Black tree index" << endl
            << "Enter(4) for exit" << endl
            << "Option: ";
        cin >> index;
        int Option2 = 0;
        switch (index) {
            // B tree indexing
        case 1:
            cout << endl;
            cout << "Enter (1) for index by ID" << endl;
            cout << "Enter (2) for index by Year" << endl;
            cout << "Enter (3) for index by Cause" << endl;
            cout << "Enter (4) for index by State" << endl;
            cout << "Enter (5) for index by Deaths" << endl;
            cout << "Enter (6) for index by Deathrate" << endl;
            cin >> Option2;

            cout << "*****INDEXING AND BUILDING B TREE*****" << endl;
            if (Option2 == 1 || Option2 == 2 || Option2 == 5)
            {
                string for_where;
                if (Option2 == 1)
                    for_where = "ID";
                else if (Option2 == 2)
                    for_where = "Year";
                else
                    for_where = "Deaths";
                BtreeHandler(Option2, for_where);
            }

            else if (Option2 == 3 || Option2 == 4 || Option2 == 6)
            {
                string for_where;
                if (Option2 == 3)
                    for_where = "Cause Name";
                else if (Option2 == 4)
                    for_where = "State";
                else
                    for_where = "Age-adjusted Death Rate";
                StringBtreeHandler(Option2, for_where);
            }

            else
            {
                std::cout << "Invalid Option";
            }

            break;
            // AVL tree indexing
        case 2:
            cout << endl;
            cout << "Enter (1) for index by ID" << endl;
            cout << "Enter (2) for index by Year" << endl;
            cout << "Enter (3) for index by Cause" << endl;
            cout << "Enter (4) for index by State" << endl;
            cout << "Enter (5) for index by Deaths" << endl;
            cout << "Enter (6) for index by Deathrate" << endl;
            cin >> Option2;

            cout << "*****INDEXING AND BUILDING AVL TREE*****" << endl;
            if (Option2 == 1 || Option2 == 2 || Option2 == 5)
            {
                string for_where;
                if (Option2 == 1)
                    for_where = "ID";
                else if (Option2 == 2)
                    for_where = "Year";
                else
                    for_where = "Deaths";
                AVLHander(Option2, for_where);
            }

            else if (Option2 == 3 || Option2 == 4 || Option2 == 6)
            {
                string for_where;
                if (Option2 == 3)
                    for_where = "Cause Name";
                else if (Option2 == 4)
                    for_where = "State";
                else
                    for_where = "Age-adjusted Death Rate";
                AVLHandlerString(Option2, for_where);
            }

            else
            {
                std::cout << "Invalid Option";
            }

            break;
            // Red-Black tree indexing
        case 3:
            cout << endl;
            cout << "Enter (1) for index by ID" << endl;
            cout << "Enter (2) for index by Year" << endl;
            cout << "Enter (3) for index by Cause" << endl;
            cout << "Enter (4) for index by State" << endl;
            cout << "Enter (5) for index by Deaths" << endl;
            cout << "Enter (6) for index by Deathrate" << endl;
            cin >> Option2;

            cout << "*****INDEXING AND BUILDING Red-Black TREE*****" << endl;
            if (Option2 == 1 || Option2 == 2 || Option2 == 5)
            {
                string for_where;
                if (Option2 == 1)
                    for_where = "ID";
                else if (Option2 == 2)
                    for_where = "Year";
                else
                    for_where = "Deaths";
                RBHander(Option2, for_where);
            }

            else if (Option2 == 3 || Option2 == 4 || Option2 == 6)
            {
                string for_where;
                if (Option2 == 3)
                    for_where = "Cause Name";
                else if (Option2 == 4)
                    for_where = "State";
                else
                    for_where = "Age-adjusted Death Rate";
                StringRTreeHandler(Option2, for_where);
            }

            else
            {
                std::cout << "Invalid Option";
            }
            break;
        case 4:
            return 0;
            // Invalid option selected
        default:
            cout << "Invalid Option!" << endl;
            break;
        }
    }

    return 0;
}