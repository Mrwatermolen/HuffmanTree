#include "HuffmanTreeCode.hpp"
#include <iomanip>
#include <string>
#include <fstream>

HuffmanCodeCreat::HuffmanCodeCreat()
{
    CreateHuffmanTree();
}
void HuffmanCodeCreat::InitailizeAll()
{
    length = 0;
    int l = 0;
    map<char, double> frequenceMap;
    ifstream readFile("test.txt");
    if (readFile.is_open())
    {
        while (true)
        {
            char c;
            readFile.get(c);
            if(readFile.eof())
                break;
            if (frequenceMap.count(c))
                frequenceMap[c] = 1;
            else
                frequenceMap[c] += 1;

            ++l;
        }
    }
    readFile.close();
    this->textSize = l;
    this->ElementArr = new TreeNode[(l * 2) - 1]; // 实际上用不到那么多的空间 但此时无法知道输入了多少的独立字符
    int i = 0;
    for (map<char, double>::iterator it = frequenceMap.begin(); it != frequenceMap.end(); ++it, ++i)
    {
        //cout << it->first << " " << it->second << " " << it->second / (l) << endl;
        ElementArr[i].leftChild = NULL;
        ElementArr[i].rightChild = NULL;
        ElementArr[i].markdown = 0;
        ElementArr[i].data = it->first;
        ElementArr[i].weight = it->second / (l);
        huffManMap[it->first] = i;
    }
    length = i;
    for (; i < (length * 2) - 1; i++)
    {
        ElementArr[i].leftChild = NULL;
        ElementArr[i].rightChild = NULL;
        ElementArr[i].markdown = 0;
        //ElementArr[i].Code = "";
        ElementArr[i].weight = 10.0;
        ElementArr[i].data = -1;
    }
}
void HuffmanCodeCreat::SelectTheMinElement(int pos, int &indexLeft, int &indexRight)
{
    double weight1 = 1.0;
    double weight2 = 1.0;
    for (int i = 0; i <= pos; i++)
    {
        if (ElementArr[i].weight < weight1 && ElementArr[i].markdown == 0)
        {
            weight1 = ElementArr[i].weight;
            indexLeft = i;
        }
    }
    for (int i = 0; i <= pos; i++)
    {
        if (i == indexLeft)
        {
            continue;
        }
        if (ElementArr[i].weight < weight2 && ElementArr[i].markdown == 0)
        {
            weight2 = ElementArr[i].weight;
            indexRight = i;
        }
    }
}
void HuffmanCodeCreat::CreateHuffmanTree()
{
    InitailizeAll();
    if (this->length == 0)
        return;

    int indexLeft = 0;
    int indexRight = 0;
    int indexMax = (this->length * 2) - 1;
    int indexNow = this->length;
    for (; indexNow < indexMax; indexNow++)
    {
        indexLeft = -1;
        indexRight = -1;
        SelectTheMinElement(indexNow - 1, indexLeft, indexRight);
        ElementArr[indexLeft].markdown = 1;
        ElementArr[indexRight].markdown = 1;
        ElementArr[indexNow].leftChild = &ElementArr[indexLeft];
        ElementArr[indexNow].rightChild = &ElementArr[indexRight];
        ElementArr[indexNow].weight = ElementArr[indexRight].weight + ElementArr[indexLeft].weight;
    }

    this->HuffmanTreeHead = &ElementArr[indexMax - 1]; //最后一个肯定是头结点
    InCodeHuffmanCode(HuffmanTreeHead->Code, *HuffmanTreeHead);
}
void HuffmanCodeCreat::InCodeHuffmanCode(string &Code_now, TreeNode &head)
{
    if (head.leftChild)
    {
        string Code_next = Code_now + '1';
        InCodeHuffmanCode(Code_next, *(head.leftChild));
    }
    if (head.rightChild)
    {
        string Code_next = Code_now + '0';
        InCodeHuffmanCode(Code_next, *(head.rightChild));
    }
    if (head.leftChild == NULL && head.rightChild == NULL)
    {
        head.Code = Code_now;
    }
}

HuffmanCodeCreat::~HuffmanCodeCreat()
{
    if (ElementArr != nullptr)
        delete[] ElementArr;
}
