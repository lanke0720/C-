#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "HeapBinaryTree.h"
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

template <class T> 
struct HuffmanTreeNode
{
	T _weight;  //权重
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;

	HuffmanTreeNode<T>* _parent; //三叉树

	HuffmanTreeNode(const T& x)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_weight(x)
	{}
};

template <class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}

	~HuffmanTree()
	{
		Destroy(_root);
	}

	HuffmanTree( T* a, size_t n, const T& invalid)
	{
		struct Compare
		{
			bool operator()(Node* l, Node* r)   
			{
				return l->_weight < r->_weight;
			}
		};

		//选数据
		Heap<Node* ,Compare> hp;
		for(size_t i = 0; i < n; ++i)
		{
			if(a[i] != invalid)
				hp.Push(new Node(a[i]));
		}
		while (hp.Size() > 1)
		{
			Node* left = hp.Top();
			hp.Pop();
			Node* right = hp.Top();
			hp.Pop();
			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
			hp.Push(parent);
		}
		_root = hp.Top();
	}
	Node* GetRoot()
	{
		return _root;
	}

protected:
	HuffmanTree (const HuffmanTree& t);
	HuffmanTree operator=(const HuffmanTree& t);


	void Destroy(Node* root)
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		if (cur)
		{
			Destroy(cur->_left);
			Destroy(cur->_right);
			delete cur;
			cur = NULL;
			return;
		}
	}
private:
	Node* _root;
};


typedef long long LongType;
struct CharInfo               //统计一个字符的信息
{
	unsigned char _ch;             //字符
	LongType _count;      //字符出现的次数
	string _code;         //huffman code

	CharInfo(LongType count = 0)
		:_count(count)
	{}

	bool operator != (const CharInfo& info)
	{
		return _count != info._count;
	}

	CharInfo operator+(const CharInfo& info)
	{
		CharInfo ret;
		ret._count = _count + info._count;
		return ret;
	}

	bool operator<(const CharInfo& info)
	{
		return _count < info._count;
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[(unsigned char)i]._ch = i;
			_infos[(unsigned char)i]._count = 0;
		}
	}

	void Compress(const char* filename)
	{
		assert (filename);
		//1.统计字符出现的次数
		FILE* fout = fopen(filename ,"rb");
		assert(fout);
		unsigned char ch = fgetc(fout);
		while (!feof(fout))  
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fout);
		}

		//2构造HuffmanTree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);


		//3.生成huffman code
		GetHuffmanCode(tree.GetRoot());
		/*string code;
		GetHuffmanCodeR(tree.GetRoot(), code);
		*/
		//编写配置文件
		string configfilename = filename;  
		configfilename += ".config";                     //命名配置文件
		FILE* configfile = fopen(configfilename.c_str(),"wb");
		assert(configfile);
		string line;
		for (size_t i = 0; i < 256; i++)
		{
			if (_infos[i]._count != 0)
			{
				fputc(_infos[i]._ch, configfile);
				int c = _infos[i]._count;
				char buff[128] = {0};
				line += ',';
				line += itoa(c, buff, 10);
				line += '\n';
				fputs(line.c_str(), configfile);
				line.clear();
			}
		}
		fclose(configfile);


		//4.压缩
		string compressFile = filename;
		compressFile += ".huff";
		FILE* fIn = fopen(compressFile.c_str(), "wb");
		assert(fIn);

		fseek(fout, 0, SEEK_SET);//统计完次数以后使得头文件指向了最后，所以需要使指针指向头文件

		ch = fgetc(fout);
		unsigned char value = 0;
		int pos = 0;
		while (!feof(fout))  
		{

			string& code = _infos[ch]._code;
			for(size_t i =0; i < code.size(); ++i)
			{
				value <<= 1;
				if (code[(unsigned char)i] == '1')
				{
					value |= 1;
				}
				pos++;
				if (pos == 8)
				{
					fputc(value, fIn);
					pos = 0;
					value = 0;
				}
			}
			ch = fgetc(fout);
		}
		if(pos != 0)
		{
			value <<= (8 - pos);
			fputc(value, fIn);
		}
		fclose(fout);
		fclose(fIn);
	}

	void UnCompress(const char* filename, const char* configfilename)
	{
		assert(filename);
		string uncompress(filename);
		size_t pos = uncompress.rfind('.');
		assert(pos != string::npos);
		uncompress.replace(pos, (uncompress.size() - pos), ".unhuff");
		FILE* fin = fopen(uncompress.c_str(), "wb");
		FILE* fout = fopen(filename, "rb");

		//在解压缩之前先构建HuffmanTree
		//1,读取配置文件
		assert(configfilename);
		FILE* Fout = fopen(configfilename, "rb");
		assert(Fout);
		char conf = fgetc(Fout);
		while (!feof(Fout))  
		{
			char buff[125] = {0};
			fgetc(Fout);
			fgets(buff, 125, Fout);
			int i = atoi(buff);
			_infos[(unsigned char)conf]._count = i;

			conf = fgetc(Fout);
		}
		//2，再次构建HuffmanTree
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> HT(_infos, 256, invalid);

		HuffmanTreeNode<CharInfo>* root = HT.GetRoot();
		assert(root);
		//只有一个
		if (root->_left == NULL && root->_right == NULL)
		{
			for (int i = 0; i < root->_weight._count; ++i)
			{
				fputc(root->_weight._ch, fin);
			}
			return;
		}
		
		HuffmanTreeNode<CharInfo>* cur = root;
		char ch = fgetc(fout);
		while (!feof(fout))  
		{
			int pos = 7;
			int value = 1;
			while (pos >= 0)
			{
				if (ch & (value << pos))
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
				
				if(cur->_left == NULL && cur->_right == NULL)
				{
					fputc(cur->_weight._ch, fin);
					cur = root;
					root->_weight._count--;
				}
				if(root->_weight._count == 0)
				{
					fclose(fin);
					fclose(fout);
					return;
				}
				pos--;
			}
			ch = fgetc(fout);
		}
	}

protected:
	/*
	void GetHuffmanCodeR(HuffmanTreeNode<CharInfo>* root, string code)
	{
		if (NULL == root)
			return;

		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
		}

		GetHuffmanCodeR(root->_left, code.push_back(0));
		GetHuffmanCodeR(root->_right, code.push_back(1));
	}
	*/
	
	void GetHuffmanCode(HuffmanTreeNode<CharInfo>* root)
	{
		if(root == NULL)
			return;	
		GetHuffmanCode(root->_left);
		GetHuffmanCode(root->_right);

		if(root->_left == NULL && root->_right == NULL)
		{
			HuffmanTreeNode<CharInfo>* cur  = root;
			HuffmanTreeNode<CharInfo>* parent = cur->_parent;

			string& code = _infos[root->_weight._ch]._code;
			while(parent)
			{
				if(cur == parent->_left)
				{
					code.push_back('0');
				}
				else
					code.push_back('1');

				cur = parent;
				parent = cur->_parent;
			}
			reverse(code.begin(), code.end());
			//_infos[root->_weight._ch]._code = code;
		}
		//GetHuffmanCode(root->_left);
		//GetHuffmanCode(root->_right);
	}
	
protected:
		CharInfo _infos[256];
};

