#include "Animation.h"
#include "Game.h"
#include "Graphic.h"
#include "Sprite.h"

Animation::Animation()
{}
Animation::Animation(int _numImageInRow,int _numImageInColumn,float _timePerImage,Sprite *sprite)
{
	numImageInRow=_numImageInRow;
	numImageInColumn=_numImageInColumn;
	timePerImage=_timePerImage;
	widthOfFrame=sprite->width/numImageInRow;
	heightOfFrame=sprite->height/numImageInColumn;
	index=0;
	waitNextImage=0;
	rect.left=rect.top=0;
	rect.right=widthOfFrame;
	rect.bottom=heightOfFrame;
}
Animation::Animation(int _numImageInRow, int _numImageInColumn,float _timePerImage,int iWidth,int iHeight)
{
	numImageInRow=_numImageInRow;
	numImageInColumn=_numImageInColumn;
	timePerImage=_timePerImage;
	widthOfFrame=iWidth/numImageInRow;
	heightOfFrame=iHeight/numImageInColumn;
	index=0;
	waitNextImage=0;
	rect.left=rect.top=0;
	rect.right=widthOfFrame;
	rect.bottom=heightOfFrame;
}
Animation::~Animation(){}
void Animation::Update(int indexFirstImage,int indexLastImage,float TPF)
{
	if(indexFirstImage<0||indexLastImage>numImageInColumn*numImageInRow)
		return;
	if(index<indexFirstImage||index>indexLastImage) 
		SetIndex(indexFirstImage);
	waitNextImage+=TPF;
	if(waitNextImage>=timePerImage)
	{
		if(index<indexLastImage)
			SetIndex(index+1);
		else
			SetIndex(indexFirstImage);
		waitNextImage=0;
	}
}
RECT Animation::GetRect(int imageIndex)
{
	RECT result;
	result.top=imageIndex/numImageInRow*heightOfFrame;
	result.left=(imageIndex%numImageInRow)*widthOfFrame;
	result.bottom=result.top+heightOfFrame;
	result.right=result.left+widthOfFrame;
	return result;
}
void Animation::SetIndex(int _index)
{
	index	=_index;
	rect.top=(index/numImageInRow)*heightOfFrame;
	rect.left=(index%numImageInRow)*widthOfFrame;
	rect.bottom=rect.top+heightOfFrame;
	rect.right=rect.left+widthOfFrame;
}