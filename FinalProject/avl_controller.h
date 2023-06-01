#pragma once
#include<iostream>
#include<string>
#include<cstdio>
#include<sys/stat.h>
#include<sys/types.h>
#include<direct.h>
#include<fstream>
#include<limits>
#include"avl.h"
using namespace std;

// function to perform other functionalities on the tree
void functionalities(AVLTree* tree, string for_where);

AVLTree* manageDataFiles(int Option);

// function to handle the AVL Tree Functionality
void AVLHander(int Option, string for_where);

void Stringfunctionalities(AVLStringTree* tree, string for_where);

AVLStringTree* manageStringAVLDataFiles(int Option);

void AVLHandlerString(int Option, string for_where);