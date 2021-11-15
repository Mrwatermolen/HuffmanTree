//
//  HuffmanTreeCode.hpp
//  BTree_HuffmanTree

#ifndef HuffmanTreeCode_hpp
#define HuffmanTreeCode_hpp
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;
struct TreeNode
{
    int data;
    double weight;
    string Code;
    int markdown;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

class HuffmanCodeCreat
{
public:
    HuffmanCodeCreat();
    ~HuffmanCodeCreat();
    TreeNode* ElementArr;
    int length;
    TreeNode * HuffmanTreeHead;
    TreeNode * HUffmanCode_B_Tree_Chart;
    map<char,int> huffManMap;
    int textSize;
public:
    void InitailizeAll();
    void SelectTheMinElement(int index_for_search, int &min_Index_1,int &min_index_2);
    void CreateHuffmanTree();
    void InCodeHuffmanCode(string &Code,TreeNode &head);
    
};
#endif /* HuffmanTreeCode_hpp */
