#include<iostream>
#include<stdlib.h>
#include<assert.h>
using namespace std;

enum Type
{
	HEAD,
	VALUE,
	SUB,
};
struct GeneralListNode
{
	Type _type;
	GeneralListNode *_next;
	union{
		char _value;
		GeneralListNode *SubLink;
	};
	GeneralListNode(Type type = VALUE,char value = 0)
		:_type(type)
		,_next(NULL)
	{
		if(_type == VALUE){
			_value = value;
		}else if(_type == SUB){
			SubLink = NULL;
		}
	}
};
class GerneralList{
private:
	GeneralListNode *_head;
protected:
	GeneralListNode *_CreateGerneralList(char * &s)
	{
		assert(*s == '(');
		++s;
		GeneralListNode * head = new GeneralListNode(HEAD);
		GeneralListNode * cur = head;
		while(*s){
			if(*s == '('){
				GeneralListNode * subnode = new GeneralListNode(SUB);
				cur->_next = subnode;
				cur = cur->_next;
				subnode->SubLink = _CreateGerneralList(s);
			}else if(*s == ')'){
				++s;
				break;
			}else if(Isvalue(*s)){
				GeneralListNode * valuenode = new GeneralListNode(VALUE,*s);
				cur->_next = valuenode;
				cur = cur->_next;
				++s;
			}else{
				++s;
			}
		}
		return head;
	}
	bool Isvalue(char ch)
	{
		if((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
			return true;
		}else{
			return false;
		}
	}
	GeneralListNode * _copy(GeneralListNode * head)
	{
		GeneralListNode *newhead = new GeneralListNode(HEAD);
		GeneralListNode *newcur = newhead;
		GeneralListNode * cur = head;
		while(cur){
			if(cur->_type == VALUE){
				GeneralListNode * valuenode = new GeneralListNode(VALUE,cur->_value);
				newcur->_next = valuenode;
				newcur = newcur->_next;
			}else if(cur->_type == SUB){
				newcur->_next = new GeneralListNode(SUB);
				newcur = newcur->_next;
				newcur->SubLink	= _copy(cur->SubLink);
			}
			cur = cur->_next;
		}
		return newhead;
	}
	size_t _Size(GeneralListNode * head)
	{
		GeneralListNode * cur = head->_next;
		size_t size = 0;
		while(cur){
			if(cur->_type == VALUE){
				++size;
			}else if(cur->_type == SUB){
				size += _Size(cur->SubLink);
			}
			cur = cur->_next;
		}
		return size;
	}
	void _Destroy(GeneralListNode * head)
	{
		GeneralListNode * cur = head;
		while(cur){
			GeneralListNode * del = cur;
			cur = cur->_next;
			if(del->_type == SUB)
				_Destroy(del->SubLink);
			else
				delete del;
		}
	}
	void _print(GeneralListNode * &head)
	{
		GeneralListNode * cur = head;
		while(cur){
			if(cur->_type == HEAD){
				cout<<"(";
			}else if(cur->_type == VALUE){
				cout<<cur->_value;
				if(cur->_next != NULL)
					cout<<",";
			}else{
				_print(cur->SubLink);
			}
			cur = cur->_next;
		}
		cout<<")";
	}
	size_t _Depth(GeneralListNode * head)
	{
		GeneralListNode * cur = head;
		size_t depth = 1;
		while(cur){
			if(cur->_type == SUB){
				if(_Depth(cur->SubLink) + 1 > depth)
					depth = _Depth(cur->SubLink) + 1;
			}
			cur = cur->_next;
		}
		return depth;
	}
public:
	GerneralList()
		:_head(NULL)
	{}
	GerneralList(char *s)
		:_head(NULL)
	{
		_head = _CreateGerneralList(s);
	}
	GerneralList(const GerneralList &s)
		:_head(NULL)
	{
		_head = _copy(s._head);
	}
	/*GerneralList &operator =(const GerneralList &s)
	{
		 if(this != &s)
		 {
			 this->_Destroy(_head);
			 _head = _copy(s._head);
		 }
		 return *this;
	}*/
	GerneralList &operator =(GerneralList s)  //ÏÖ´úÐ´·¨
	{
		swap(_head,s._head);
		return *this;
	}

	~GerneralList()
	{
		_Destroy(_head);
	}
	size_t Size()
	{
		return _Size(_head);
	}
	void Print()
	{
		_print(_head);
		cout<<endl;
	}
	size_t Depth()
	{
		return _Depth(_head);
	}
};
void test()
{
	GerneralList g1("(a,b,(c,d))");
	g1.Print();
	cout<<g1.Size()<<endl;
	cout<<g1.Depth()<<endl;
	GerneralList g2("(1,2)");
	g2 = g1;
	g2.Print();
}
int main()
{
	test();
	system("pause");
	return 0;
}