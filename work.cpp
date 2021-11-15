#include <iostream>
#include <fstream>
#include "HuffmanTreeCode.cpp"
using namespace std;
int main()
{
	cout << "开始创建huffman树" << endl;
	cout << "================================================" << endl;
	HuffmanCodeCreat HT;
	cout << "创建huffman树结束，输出编码与字符的映射关系" << endl;
	cout << "================================================" << endl;
	for (auto it = HT.huffManMap.begin(); it != HT.huffManMap.end(); ++it)
		cout << it->first << "\t" << HT.ElementArr[HT.huffManMap[it->first]].Code << endl;

	cout << "开始对test.txt文件进行编码压缩保存为HuffmanCompress.dat" << endl;
	cout << "================================================" << endl;
	ifstream readFile("test.txt");
	ofstream writeFile("HuffmanCompress.dat", ios::binary);
	int compressedSize = 0, originalSize = 0;

	if (readFile.is_open() && writeFile.is_open())
	{
		int count = 0;
		char buf = 0x00;

		//string res;
		//string es;
		//string writeRes;

		while (!readFile.eof())
		{
			char c;
			readFile.get(c);
			string s = HT.ElementArr[HT.huffManMap[c]].Code;
			//res += s;
			//cout << "要转换的字符：" << c << "\t 其编码：" << s << endl;
			for (int i = 0; i < s.size(); ++i)
			{
				//es.push_back(s[i]);
				//cout << "单01压入： " << s << "\t" << s[i] << "\t" << i << endl;
				if (s[i] == '1')
				{
					buf = buf + 0x01;
				}
				if (++count == 8)
				{
					//cout << "char写入文件" << hex << (unsigned int)buf << "\t" << es << endl;
					writeFile << buf;
					buf = 0x00;
					count = 0;

					/* writeRes += es;
					es = ""; */
				}
				else
				{
					buf = buf << 1;
				}
			}
		}
		/* cout << "RES: " << res << endl;
		cout << "此时的写入WrR: " << writeRes << endl;
		cout << "应该编码位数" << res.size() << endl; */
		if (count != 0)
		{
			int i = 7 - count; // 易错点！！！
			while (i != 0)
			{
				buf = buf << 1;
				--i;
			}
		}
		/* cout << "WrR: " << writeRes << endl;
		cout << "实际编码位数" << writeRes.size() << endl; */
		writeFile.close();
		readFile.close();
		cout<<"编码成功"<<endl;
	}
	else
	{
		cout << "编码失败，原因文件打开失败" << endl;
		return 0;
	}

	cout << "开始对HuffmanCompress.dat文件进行解码保存为HuffmanDecode.txt" << endl;
	cout << "================================================" << endl;
	ifstream file("HuffmanCompress.dat", ios::binary);
	fstream decode("HuffmanDecode.txt");
	TreeNode *p = HT.HuffmanTreeHead;

	if (file.is_open() && decode.is_open())
	{
		compressedSize = file.tellg();
		int times = 0;
		//string fun = "";
		while (true && times < HT.textSize)
		{
			char c;

			file.get(c);
			//cout << "c:" << hex << (unsigned int)c << endl;
			//string t = "";

			if (file.eof())
				break;

			for (int i = 0; i < 8; ++i)
			{
				int flag = (((c >> (7 - i))) & 0x01);
				if (flag)
				{
					//cout << "左移动" << endl;
					p = p->leftChild;
				}
				else
				{
					//cout << "右移动" << endl;
					p = p->rightChild;
				}
				if (p->leftChild == NULL)
				{
					decode << (char)p->data;
					p = HT.HuffmanTreeHead;
					++times;
					//cout << (char)p->data << " 解码次数 " << times << " 实际字符数： " << HT.textSize << endl;
					if (times >= HT.textSize)
						break;
				}

				//t += flag + '0';
			}
			//cout << "T " << t.size() << endl;
			//fun += t;
		}
		//cout << "FUN: " << fun << endl;
		//cout << "实际读取位数" << fun.size() << endl;
		cout<<"Succeed!"<<endl;
		file.close();
		decode.close();
	}
	else
	{
		cout << "解码失败，原因文件打开失败" << endl;
		return 0;
	}
	return 0;
}
