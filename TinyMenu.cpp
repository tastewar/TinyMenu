#include <TinyScreen.h>
#include <TinyScreenRegion.h>
#include "TinyMenu.h"

TinyMenu::TinyMenu(TinyScreen *ts, bool IsDynamic, const char *Items, const MenuItemsInfo *ItemsInfo, uint8_t MarginSize)
{
	uint8_t RtMargin, BotMargin, LeftMargin, TopMargin, MidWidth, MidHeight;

	_MarginSize=MarginSize;
	_ts=ts;
	_MenuItems=Items;

	LeftMargin=MarginSize;
	TopMargin=MarginSize;
	RtMargin=ts->xMax+1-MarginSize;
	BotMargin=ts->yMax+1-MarginSize;
	MidWidth=ts->xMax+1-(2*MarginSize);
	MidHeight=ts->yMax+1-(2*MarginSize);

	_TL.begin(ts, 0, 0, MarginSize, MarginSize);
	_Title.begin(ts, LeftMargin, 0, MidWidth, MarginSize);
	_TR.begin(ts, RtMargin, 0, MarginSize, MarginSize);
	_ML.begin(ts, 0, TopMargin, MarginSize, MidHeight);
	Body.begin(ts, LeftMargin, TopMargin, MidWidth, MidHeight);
	_MR.begin(ts, RtMargin, TopMargin, MarginSize, MidHeight);
	_BL.begin(ts, 0, BotMargin, MarginSize, MarginSize);
	Footer.begin(ts, LeftMargin, BotMargin, MidWidth, MarginSize);
	_BR.begin(ts, RtMargin, BotMargin, MarginSize, MarginSize);
}