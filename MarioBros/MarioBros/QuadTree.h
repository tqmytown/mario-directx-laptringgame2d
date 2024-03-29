
#pragma once

#include <list>
using namespace std;

#include "d3dx9.h"

#define MAX_LEVEL	7

enum TYPE_RECT{TR_NONE,TR_TL,TR_TR,TR_BL,TR_BR};
bool RectInRect(RECT rInner,RECT outerRect);
RECT GetChildRect(RECT rect,int typeRect);

class Object;
class QuadTree
{
private:
	char CheckInChildRect(RECT rInner);		//Kiểm tra xem thuộc rect con nào
	QuadTree** GetChildNodeFromChildRect(char childRectType);
	bool IsExistDynamic(Object* obj);
	bool IsContainable(Object* obj);
public:

	RECT		rect;
	char		level;

	QuadTree*	topLeft;
	QuadTree*	topRight;
	QuadTree*	bottomLeft;
	QuadTree*	bottomRight;

	list<Object*>	staticObj;
	list<Object*>	dynamicObj;

	QuadTree(int x,int y,int size,char _level);
	~QuadTree();

	bool Add(Object* obj,bool isStatic);
	void GetObjectsInNode(list<Object*>* staticList,list<Object*>* dynamicList);
	void GetObjectsAllNode(list<Object*>* staticList,list<Object*>* dynamicList);
	void GetObjectsInNode(list<Object*>* l,bool isStatic);	
	void GetObjectsAllNode(list<Object*>* l,bool isStatic);
	void GetObjectsFromCamera(RECT rCamera,list<Object*>* staticList,list<Object*>* dynamicList);
	void DeleteObj(Object* obj,bool isStatic);
	void Update(/*list<Object*> l*/);	
	void QuadTree::Update(list<Object*> l);
};