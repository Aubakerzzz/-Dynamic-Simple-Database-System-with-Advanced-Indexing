
#pragma once
#include<iostream>
#include<string>
#include<cstdio>
#include<sys/stat.h>
#include<sys/types.h>
#include<direct.h>
#include<fstream>
#include<limits>
#include"RB.h"

using namespace std;

template <typename myType>
void functionalities(RedBlackTree<myType>* tree, string for_where);

template <typename myType>
RedBlackTree<myType>* manageDataFiles(int Option);

// function to handle the AVL Tree Functionality

void RBHander(int Option, string for_where);


void Stringfunctionalities(RedBlackTreeString* tree, string for_where);


RedBlackTreeString* manageStringRTreeDataFiles(int Option);



void StringRTreeHandler(int Option, string for_where);