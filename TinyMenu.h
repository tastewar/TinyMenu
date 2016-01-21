#ifndef TinyMenu_H
#define TinyMenu_H

#include <Arduino.h>

#define TM_MAX_LEVELS 8
typedef void (*FooterF)(void);
typedef uint8_t (*ButtonPressF)(void *MenuText, uint8_t ItemNumber, uint8_t Button);

typedef enum
{
	MIT_Title,
	MIT_Menu,
	MIT_ProgmemMenu,
	MIT_Text,
	MIT_Other,
} MenuItemType;

typedef struct
{
	MenuItemType mit;
	char *ItemList;
	ButtonPressF ButtonFunc;
} MenuItemsInfo;

class TinyMenu
{
public:
  TinyMenu(TinyScreen *ts, bool IsDynamic, const char *Items, const MenuItemsInfo *ItemsInfo, uint8_t MarginSize);
  void Stack(char *NewMenuItems, MenuItemsInfo *ItemsInfo);
  void UnStack(void);
  void Activity(uint8_t Button); // pass logical button or 0 == idle
  void Timeout(void); // resets context, stack level, so on next entry we start fresh
  void Display(void); // output title, initial list
  void SetFooterFunction(FooterF theFunction);
  void RefreshFooter(void); // called in loop when in menu mode, once per second when idle and with each button press
  void Idle(void);

  typedef struct
  {
	  char *MenuItems;
	  uint8_t CurrentItem;
  } StackLevel;

  TinyScreenRegion Body, Footer;

private:
  void DisplayTitle(char *Title);

  TinyScreen *_ts;
  bool	_Dynamic;
  const char  *_MenuItems;
  uint8_t _CurrentItem;
  uint8_t _MarginSize;
  unsigned long _lastDisplayMillis;
  unsigned long _lastFooterUpdateMillis;
  FooterF _FooterFunc; // this is called when in menu mode -- do we need this, or just leave footer region public?

  StackLevel  _StackArea[TM_MAX_LEVELS];
  TinyScreenRegion _TL, _TR, _ML, _MR, _BL, _BR, _Title;

};

/*
user should be able to pass a pointer to an array of strings, and
those strings should be able to be either in flash or ram. If Dynamic
is specified, the strings are read from RAM; otherwise they are read
from Flash. The MenuItems string is a series of concatenated null
terminated strings, with a double null to signify the end of the list

There is a companion struct that goes with the strings indicating each
item's type and possibly a pointer -- for either a menu or text item,
it's the text list address, and for an "other" item, it's the button
press function address. Menus and Text items are handled
When an item is selected (the "enter" button), the current state is
"stacked" (pointer to MenuItems, and current itemnumber)

An individual item can be another Menu (Flash or RAM address), a text
setting, or an externally defined type (generally numeric).



"



There is also an array of callback functions, 1 for each list member

MenuResult (*pCallback)(uint8_t itemNum, buttonName)

This function


*/

/*

when the main loop knows we're in "menu mode" it should pass any input
received (button press) to the Activity function. If there's been no
activity, it can pass a 0 to the Activity function. When there's no
activity, the menu can choose to update the footer, typically used
for displaying the time.

On an "enter" button press, the menu gets stacked, and the appropriate
code for the menu item gets called.




*/


#endif
