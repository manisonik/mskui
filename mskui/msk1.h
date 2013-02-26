#pragma once

#ifndef _MSK1_H_
#define _MSK1_H_

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#endif // #ifndef COM_NO_WINDOWS_H
#include <unknwn.h>
#include <d2d1.h>

#ifndef MSK_USE_C_DEFINITIONS

#ifndef __cplusplus
#define MSK_USE_C_DEFINITIONS
#endif

#endif // #ifndef MSK_USE_C_DEFINITIONS

#ifndef MSK_DECLARE_INTERFACE
#define MSK_DECLARE_INTERFACE(X) interface DECLSPEC_UUID(X) DECLSPEC_NOVTABLE
#endif

// Foward Declaration
#ifndef MSK_USE_C_DEFINITIONS
interface IMSK1Framework;
interface IMSK1Application;
interface IMSK1CommandHandler;
interface IMSK1Window;
interface IMSK1StatusBarCtrl;
interface IMSK1ScrollBarCtrl;
interface IMSK1ProgressBarCtrl;
interface IMSK1ReBarCtrl;
interface IMSK1ToolBarCtrl;
interface IMSK1TrackBarCtrl;
interface IMSK1TextBoxCtrl;
interface IMSK1ListBoxCtrl;
interface IMSK1ComboBoxCtrl;
interface IMSK1RichTextBoxCtrl;
interface IMSK1TabViewCtrl;
interface IMSK1TreeViewCtrl;
interface IMSK1PropertySheetDialog;
interface IMSK1TaskDialog;
interface IMSK1DateTimePickerCtrl;
interface IMSK1HeaderCtrl;
interface IMSK1AnimationCtrl;
interface IMSK1UpDownCtrl;
interface IMSK1ButtonCtrl;
interface IMSK1MonthCalendarCtrl;
interface IMSK1ToolTipCtrl;
interface IMSK1HotKeyCtrl;
interface IMSK1ImageListCtrl;
interface IMSK1PagerCtrl;
interface IMSK1StaticCtrl;
interface IMSK1SysLinkCtrl;
interface IMSK1ToolWindow;
#else
typedef interface IMSK1Framework			IMSK1Framework;
typedef interface IMSK1Application			IMSK1Application;
typedef interface IMSK1CommandHandler		IMSK1CommandHandler;
typedef interface IMSK1Window				IMSK1Window;
typedef interface IMSK1StatusBarCtrl		IMSK1StatusBarCtrl;
typedef interface IMSK1ScrollBarCtrl		IMSK1ScrollBarCtrl;
typedef interface IMSK1ProgressBarCtrl		IMSK1ProgressBarCtrl;
typedef interface IMSK1ReBarCtrl			IMSK1ReBarCtrl;
typedef interface IMSK1ToolBarCtrl			IMSK1ToolBarCtrl;
typedef interface IMSK1TrackBarCtrl			IMSK1TrackBarCtrl;
typedef interface IMSK1TextBoxCtrl			IMSK1TextBoxCtrl;
typedef interface IMSK1ListBoxCtrl			IMSK1ListBoxCtrl;
typedef interface IMSK1ComboBoxCtrl			IMSK1ComboBoxCtrl;
typedef interface IMSK1RichTextBoxCtrl		IMSK1RichTextBoxCtrl;
typedef interface IMSK1TabViewCtrl			IMSK1TabViewCtrl;
typedef interface IMSK1TreeViewCtrl			IMSK1TreeViewCtrl;
typedef interface IMSK1PropertySheetDialog	IMSK1PropertySheetDialog;
typedef interface IMSK1TaskDialog			IMSK1TaskDialog;
typedef interface IMSK1DateTimePickerCtrl	IMSK1DateTimePickerCtrl;
typedef interface IMSK1HeaderCtrl			IMSK1HeaderCtrl;
typedef interface IMSK1AnimationCtrl		IMSK1AnimationCtrl;
typedef interface IMSK1UpDownCtrl			IMSK1UpDownCtrl;
typedef interface IMSK1ButtonCtrl			IMSK1ButtonCtrl;
typedef interface IMSK1MonthCalendarCtrl	IMSK1MonthCalendarCtrl;
typedef interface IMSK1ToolTipCtrl			IMSK1ToolTipCtrl;
typedef interface IMSK1HotKeyCtrl			IMSK1HotKeyCtrl;
typedef interface IMSK1ImageListCtrl		IMSK1ImageListCtrl;
typedef interface IMSK1PagerCtrl			IMSK1PagerCtrl;
typedef interface IMSK1StaticCtrl			IMSK1StaticCtrl;
typedef interface IMSK1SysLinkCtrl			IMSK1SysLinkCtrl;
typedef interface IMSK1ToolWindow			IMSK1ToolWindow;
#endif

typedef enum MSK1_RESOURCE_TYPE
{
	MSK1_RESOURCE_CURSOR,
	MSK1_RESOURCE_BITMAP,
	MSK1_RESOURCE_ICON,
	MSK1_RESOURCE_MENU,
	MSK1_RESOURCE_DIALOG,
	MSK1_RESOURCE_STRING,
	MSK1_RESOURCE_FONTDIR,
	MSK1_RESOURCE_FONT,
	MSK1_RESOURCE_ACCELERATOR,
	MSK1_RESOURCE_RCDATA,
	MSK1_RESOURCE_MESSAGETABLE,
	MSK1_RESOURCE_GROUPID,
	MSK1_RESOURCE_GROUP_CURSOR,
	MSK1_RESOURCE_VERSION,
	MSK1_RESOURCE_DLGINCLUDE,
	MSK1_RESOURCE_PLUGPLAY,
	MSK1_RESOURCE_VXD,
	MSK1_RESOURCE_ANICURSOR,
	MSK1_RESOURCE_ANIICON,
	MSK1_RESOURCE_HTML,
	MSK1_RESOURCE_MANIFEST
} MSK1_RESOURCE_TYPE;

typedef struct MSK1_STATUSBAR_BORDERSIZE_U
{
	UINT nHorizontal;
	UINT nVertical;
	UINT nSpacing;
} MSK1_STATUSBAR_BORDERSIZE_U;

typedef enum MSK1_SBARSTYLE_FLAGS
{
	MSK1_SBARSTYLE_TOOLTIP,
	MSK1_SBARSTYLE_SIZEGRIP
} MSK1_SBARSTYLE_FLAGS;

typedef enum MSK1_ANISTYLE_FLAGS
{
	MSK1_ANISTYLE_AUTOPLAY,
	MSK1_ANISTYLE_CENTER,
	MSK1_ANISTYLE_TIMER,
	MSK1_ANISTYLE_TRANSPARENT
} MSK1_ANISTYLE_FLAGS;

typedef enum MSK1_BTNSTYLE_FLAGS
{
	MSK1_BTNSTYLE_3DSTATE,
	MSK1_BTNSTYLE_AUTO3DSTATE,
	MSK1_BTNSTYLE_AUTOCHECKBOX,
	MSK1_BTNSTYLE_AUTORADIOBUTTON,
	MSK1_BTNSTYLE_CHECKBOX,
	MSK1_BTNSTYLE_DEFPUSHBUTTON,
	MSK1_BTNSTYLE_GROUPBOX,
	MSK1_BTNSTYLE_LEFTTEXT,
	MSK1_BTNSTYLE_OWNERDRAW,
	MSK1_BTNSTYLE_PUSHBUTTON,
	MSK1_BTNSTYLE_RADIOBUTTON,
	MSK1_BTNSTYLE_USERBUTTON,
	MSK1_BTNSTYLE_BITMAP,
	MSK1_BTNSTYLE_BOTTOM,
	MSK1_BTNSTYLE_CENTER,
	MSK1_BTNSTYLE_ICON,
	MSK1_BTNSTYLE_FLAT,
	MSK1_BTNSTYLE_LEFT,
	MSK1_BTNSTYLE_MULTILINE,
	MSK1_BTNSTYLE_NOTIFY,
	MSK1_BTNSTYLE_PUSHLIKE,
	MSK1_BTNSTYLE_RIGHT,
	MSK1_BTNSTYLE_RIGHTBUTTON,
	MSK1_BTNSTYLE_TEXT,
	MSK1_BTNSTYLE_TOP,
	MSK1_BTNSTYLE_TYPEMASK,
	MSK1_BTNSTYLE_VCENTER,
	MSK1_BTNSTYLE_SPLITBUTTON,
	MSK1_BTNSTYLE_DEFSPLITBUTTON,
	MSK1_BTNSTYLE_COMMANDLINK,
	MSK1_BTNSTYLE_DEFCOMMANDLINK
} MSK1_BTNSTYLE_FLAGS;

typedef enum MSK1_BTNSETCHECK_STATE
{
	MSK1_BTNSETCHECK_CHECKED,
	MSK1_BTNSETCHECK_INDETERMINATE,
	MSK1_BTNSETCHECK_UNCHECKED
} MSK1_BTNSETCHECK_STATE;

typedef enum MSK1_CBSTYLE_FLAGS
{
	MSK1_CBSTYLE_AUTOHSCROLL,
	MSK1_CBSTYLE_DISABLENOSCROLL,
	MSK1_CBSTYLE_DROPDOWN,
	MSK1_CBSTYLE_DROPDOWNLIST,
	MSK1_CBSTYLE_HASSTRIGNS,
	MSK1_CBSTYLE_LOWERCASE,
	MSK1_CBSTYLE_NOINTERGRALHEIGHT,
	MSK1_CBSTYLE_OEMCONVERT,
	MSK1_CBSTYLE_OWNERDRAWFIXED,
	MSK1_CBSTYLE_OWNERDRAWVARIABLE,
	MSK1_CBSTYLE_SIMPLE,
	MSK1_CBSTYLE_SHORT,
	MSK1_CBSTYLE_UPPERCASE
} MSK1_CBSTYLE_FLAGS;

typedef enum MSK1_CBEXSTYLE_FLAGS
{
	MSK1_CBEXSTYLE_CASESENSITIVE,
	MSK1_CBEXSTYLE_NOEDITIMAGE,
	MSK1_CBEXSTYLE_NOEDITIMAGEINDENT,
	MSK1_CBEXSTYLE_NOSIZELIMIT,
	MSK1_CBEXSTYLE_PATHWORDBREAKPROC,
	MSK1_CBEXSTYLE_TEXTENDELLIPSIS
} MSK1_CBEXSTYLE_FLAGS;

typedef enum MSK1_CBDDL_ATTR
{
	MSK1_CBDDL_ARCHIVE = DDL_ARCHIVE,
	MSK1_CBDDL_DIRECTORY = DDL_DIRECTORY,
	MSK1_CBDDL_DRIVES = DDL_DRIVES,
	MSK1_CBDDL_EXCLUSIZE = DDL_EXCLUSIVE,
	MSK1_CBDDL_HIDDEN = DDL_HIDDEN,
	MSK1_CBDDL_READONLY = DDL_READONLY,
	MSK1_CBDDL_READWRITE = DDL_READWRITE,
	MSK1_CBDDL_SYSTEM = DDL_SYSTEM
} MSK1_CBDDL_ATTR;

typedef enum MSK1_DTSTYLE_FLAGS
{
	MSK1_DTSTYLE_APPCANPARSE,
	MSK1_DTSTYLE_LONGDATEFORMAT,
	MSK1_DTSTYLE_RIGHTALIGN,
	MSK1_DTSTYLE_SHOWNONE,
	MSK1_DTSTYLE_SHORTDATEFORMAT,
	MSK1_DTSTYLE_SHORTDATECENTURYFORMAT,
	MSK1_DTSTYLE_FORMAT,
	MSK1_DTSTYLE_UPDOWN
} MSK1_DTSTYLE_FLAGS;

typedef enum MSK1_ESTYLE_FLAGS
{
	MSK1_ESTYLE_AUTOHSCROLL,
	MSK1_ESTYLE_AUTOVSCROLL,
	MSK1_ESTYLE_CENTER,
	MSK1_ESTYLE_LEFT,
	MSK1_ESTYLE_LOWERCASE,
	MSK1_ESTYLE_MULTILINE,
	MSK1_ESTYLE_NOHIDESEL,
	MSK1_ESTYLE_NUMBER,
	MSK1_ESTYLE_OWMCONVERT,
	MSK1_ESTYLE_PASWORD,
	MSK1_ESTYLE_READONLY,
	MSK1_ESTYLE_RIGHT,
	MSK1_ESTYLE_UPPERCASE,
	MSK1_ESTYLE_WANTRETURN
} MSK1_ESTYLE_FLAGS;

typedef enum MSK1_HDSTYLE_FLAGS
{
	MSK1_HDSTYLE_BUTTONS,
	MSK1_HDSTYLE_DRAGDROP,
	MSK1_HDSTYLE_FILTERBAR,
	MSK1_HDSTYLE_FLAT,
	MSK1_HDSTYLE_FULLDRAG,
	MSK1_HDSTYLE_HIDDEN,
	MSK1_HDSTYLE_HORZ,
	MSK1_HDSTYLE_HOTTRACK,
	MSK1_HDSTYLE_CHECKBOXES,
	MSK1_HDSTYLE_NOSIZING,
	MSK1_HDSTYLE_OVERFLOW
} MSK1_HDSTYLE_FLAGS;

typedef enum MSK1_LBSTYLE_FLAGS
{
	MSK1_LBSTYLE_COMBOBOX,
	MSK1_LBSTYLE_DISABLENOSCROLL,
	MSK1_LBSTYLE_EXTENDEDSEL,
	MSK1_LBSTYLE_HASSTRINGS,
	MSK1_LBSTYLE_MULTICOLUMN,
	MSK1_LBSTYLE_MULTIPLESEL,
	MSK1_LBSTYLE_NODATA,
	MSK1_LBSTYLE_NOINTERGRALHEIGHT,
	MSK1_LBSTYLE_NOREDRAW,
	MSK1_LBSTYLE_NOSEL,
	MSK1_LBSTYLE_NOTIFY,
	MSK1_LBSTYLE_OWNERDRAWFIXED,
	MSK1_LBSTYLE_OWNERDRAWVARIABLE,
	MSK1_LBSTYLE_SORT,
	MSK1_LBSTYLE_STANDARD,
	MSK1_LBSTYLE_USETABSTOPS,
	MSK1_LBSTYLE_WANTKEYBOARDINPUT
} MSK1_LBSTYLE_FLAGS;

typedef enum MSK1_LVSTYLE_FLAGS
{
	MSK1_LVSTYLE_ALIGNLEFT,
	MSK1_LVSTYLE_ALIGNMASK,
	MSK1_LVSTYLE_ALIGNTOP,
	MSK1_LVSTYLE_AUTOARRANGE,
	MSK1_LVSTYLE_EDITLABELS,
	MSK1_LVSTYLE_ICON,
	MSK1_LVSTYLE_LIST,
	MSK1_LVSTYLE_NOCOLUMNHEADER,
	MSK1_LVSTYLE_NOLABELWRAP,
	MSK1_LVSTYLE_NOSCROLL,
	MSK1_LVSTYLE_NOSORTHEADER,
	MSK1_LVSTYLE_OWNERDATA,
	MSK1_LVSTYLE_OWNERDRAWFIXED,
	MSK1_LVSTYLE_REPORT,
	MSK1_LVSTYLE_SHAREIMAGELISTS,
	MSK1_LVSTYLE_SHOWSELALWAYS,
	MSK1_LVSTYLE_SINGLESEL,
	MSK1_LVSTYLE_SMALLICON,
	MSK1_LVSTYLE_SORTASCENDING,
	MSK1_LVSTYLE_SORTDESCENDING,
	MSK1_LVSTYLE_TYPEMASK,
	MSK1_LVSTYLE_TYPESTYLEMASK
} MSK1_LVSTYLE_FLAGS;

typedef enum MSK1_LVSTYLE_EX_FLAGS
{
	MSK1_LVSTYLE_EX_AUTOAUTOARRANGE,
	MSK1_LVSTYLE_EX_AUTOCHECKSELECT,
	MSK1_LVSTYLE_EX_AUTOSIZECOLUMNS,
	MSK1_LVSTYLE_EX_BORDERSELECT,
	MSK1_LVSTYLE_EX_CHECKBOXES,
	MSK1_LVSTYLE_EX_COLUMNOVERFLOW,
	MSK1_LVSTYLE_EX_COLUMNSNAPPOINTS,
	MSK1_LVSTYLE_EX_DOUBLEBUFFER,
	MSK1_LVSTYLE_EX_FLATSB,
	MSK1_LVSTYLE_EX_FULLROWSELECT,
	MSK1_LVSTYLE_EX_GRIDLINES,
	MSK1_LVSTYLE_EX_HEADERDRAGDROP,
	MSK1_LVSTYLE_EX_HEADERINALLVIEWS,
	MSK1_LVSTYLE_EX_HIDELABELS,
	MSK1_LVSTYLE_EX_INFOTIP,
	MSK1_LVSTYLE_EX_JUSTIFYCOLUMNS,
	MSK1_LVSTYLE_EX_LABELTIP,
	MSK1_LVSTYLE_EX_MULTIWORKAREAS,
	MSK1_LVSTYLE_EX_ONECLICKACTIVATE,
	MSK1_LVSTYLE_EX_REGIONAL,
	MSK1_LVSTYLE_EX_SIMPLESELECT,
	MSK1_LVSTYLE_EX_SINGLEROW,
	MSK1_LVSTYLE_EX_SNAPTOGRID,
	MSK1_LVSTYLE_EX_SUBITEMIMAGES,
	MSK1_LVSTYLE_EX_TRACKSELECT,
	MSK1_LVSTYLE_EX_TRANSPARENTBKGND,
	MSK1_LVSTYLE_EX_TRANSPARENTSHADOWTEXT,
	MSK1_LVSTYLE_EX_TWOCLICKACTIVATE,
	MSK1_LVSTYLE_EX_UNDERLINECOLD,
	MSK1_LVSTYLE_EX_UNDERLINEHOT
} MSK1_LVSTYLE_EX_FLAGS;

typedef enum MSK1_MCSTYLE_FLAGS
{
	MSK1_MCSTYLE_DAYSTATE,
	MSK1_MCSTYLE_MULTISELECT,
	MSK1_MCSTYLE_WEEKNUMBERS,
	MSK1_MCSTYLE_NOTODAYCIRCLE,
	MSK1_MCSTYLE_NOTODAY,
	MSK1_MCSTYLE_NOTRAILINGDATES,
	MSK1_MCSTYLE_SHORTDAYOFWEEK,
	MSK1_MCSTYLE_NOSELCHANGEONNAV
} MSK1_MCSTYLE_FLAGS;

typedef enum MSK1_PGSTYLE_FLAGS
{
	MSK1_PGSTYLE_AUTOSCROLL,
	MSK1_PGSTYLE_DRAGNDROP,
	MSK1_PGSTYLE_HORZ,
	MSK1_PGSTYLE_VERT
} MSK1_PGSSTYLE_FLAGS;

typedef enum MSK1_PBSTYLE_FLAGS
{
	MSK1_PBSTYLE_MARQUEE,
	MSK1_PBSTYLE_SMOOTH,
	MSK1_PBSTYLE_SMOOTHREVERSE,
	MSK1_PBSTYLE_VERTICAL
} MSK1_PBSTYLE_FLAGS;

typedef enum MSK1_RBSTYLE_FLAGS
{
	MSK1_RBSTYLE_AUTOSIZE,
	MSK1_RBSTYLE_BANDBORDERS,
	MSK1_RBSTYLE_DBLCLKTOGGLE,
	MSK1_RBSTYLE_FIXEDORDER,
	MSK1_RBSTYLE_REGISTERDROP,
	MSK1_RBSTYLE_TOOLTIPS,
	MSK1_RBSTYLE_VARHEIGHT,
	MSK1_RBSTYLE_VERTICALGRIPPER
} MSK1_RBSTYLE_FLAGS;

typedef enum MSK1_RESTYLE_FLAGS
{
	MSK1_RESTYLE_DISABLENOSCROLL,
	MSK1_RESTYLE_EX_NOCALLOLEINIT,
	MSK1_RESTYLE_NOIME,
	MSK1_RESTYLE_NOOLEDRAGDROP,
	MSK1_RESTYLE_SAVESEL,
	MSK1_RESTYLE_SELECTIONBAR,
	MSK1_RESTYLE_SELFIME,
	MSK1_RESTYLE_SUNKEN,
	MSK1_RESTYLE_VERTICAL,
	MSK1_RESTYLE_AUTOSCROLL,
	MSK1_RESTYLE_AUTOVSCROLL,
	MSK1_RESTYLE_CENTER,
	MSK1_RESTYLE_LEFT,
	MSK1_RESTYLE_MULTILINE,
	MSK1_RESTYLE_NOHIDESEL,
	MSK1_RESTYLE_NUMBER,
	MSK1_RESTYLE_PASSWORD,
	MSK1_RESTYLE_READONLY,
	MSK1_RESTYLE_RIGHT,
	MSK1_RESTYLE_WANTRETURN
} MSK1_RESTYLE_FLAGS;

typedef enum MSK1_SBSTYLE_FLAGS
{
	MSK1_SBSTYLE_BOTTOMALIGN,
	MSK1_SBSTYLE_HORZ,
	MSK1_SBSTYLE_LEFTALIGN,
	MSK1_SBSTYLE_RIGHTALIGN,
	MSK1_SBSTYLE_SIZEBOX,
	MSK1_SBSTYLE_SIZEBOXBOTTOMRIGHTALIGN,
	MSK1_SBSTYLE_SIZEBOXTOPLEFTALIGN,
	MSK1_SBSTYLE_SIZEGRIP,
	MSK1_SBSTYLE_TOPALIGN,
	MSK1_SBSTYLE_VERT
} MSK1_SBSTYLE_FLAGS;

typedef enum MSK1_TCSTYLE_FLAGS
{
	MSK1_TCSTYLE_BOTTOM,
	MSK1_TCSTYLE_BUTTONS,
	MSK1_TCSTYLE_FIXEDWIDTH,
	MSK1_TCSTYLE_FLATBUTTONS,
	MSK1_TCSTYLE_FOCUSNEVER,
	MSK1_TCSTYLE_FOCUSONBUTTONDOWN,
	MSK1_TCSTYLE_FORCEICONLEFT,
	MSK1_TCSTYLE_FORCELABELLEFT,
	MSK1_TCSTYLE_HOTTRACK,
	MSK1_TCSTYLE_MULTISELECT,
	MSK1_TCSTYLE_OWNERDRAWFIXED,
	MSK1_TCSTYLE_RAGGEDRIGHT,
	MSK1_TCSTYLE_RIGHT,
	MSK1_TCSTYLE_RIGHTJUSTIFY,
	MSK1_TCSTYLE_SCROLLOPPOSITE,
	MSK1_TCSTYLE_SINGLELINE,
	MSK1_TCSTYLE_TABS,
	MSK1_TCSTYLE_TOOLTIPS,
	MSK1_TCSTYLE_VERTICAL
} MSK1_TCSTYLE_FLAGS;

typedef enum MSK1_TCSTYLE_EX_FLAGS
{
	MSK1_TCSTYLE_EX_FLATSEPARATORS,
	MSK1_TCSTYLE_EX_RIGISTERDROP
} MSK1_TCSTYLE_EX_FLAGS;

typedef enum MSK1_TBSTYLE_FLAGS
{
	MSK1_TBSTYLE_ALTDRAG,
	MSK1_TBSTYLE_CUSTOMERASE,
	MSK1_TBSTYLE_FLAT,
	MSK1_TBSTYLE_LIST,
	MSK1_TBSTYLE_REGISTERDROP,
	MSK1_TBSTYLE_TOOLTIPS,
	MSK1_TBSTYLE_TRANSPARENT,
	MSK1_TBSTYLE_WRAPABLE,
	MSK1_TBSTYLE_AUTOSIZE,
	MSK1_TBSTYLE_BUTTON,
	MSK1_TBSTYLE_CHECK,
	MSK1_TBSTYLE_CHECKGROUP,
	MSK1_TBSTYLE_DROPDOWN,
	MSK1_TBSTYLE_GROUP,
	MSK1_TBSTYLE_NOPREFIX,
	MSK1_TBSTYLE_SEP
} MSK1_TBSTYLE_FLAGS;

typedef enum MSK1_TBSTYLE_EX_FLAGS
{
	MSK1_TBSTYLE_EX_DRAWDDARROWS,
	MSK1_TBSTYLE_EX_HIDECLIPPEDBUTTONS,
	MSK1_TBSTYLE_EX_DOUBLEBUFFER,
	MSK1_TBSTYLE_EX_MIXEDBUTTONS,
	MSK1_TBSTYLE_EX_MULTICOLUMN,
	MSK1_TBSTYLE_EX_VERTICAL
} MSK1_TBSTYLE_EX_FLAGS;

typedef enum MSK1_TTSTYLE_FLAGS
{
	MSK1_TTSTYLE_ALWAYSTIP,
	MSK1_TTSTYLE_BALLOON,
	MSK1_TTSTYLE_CLOSE,
	MSK1_TTSTYLE_NOANIMATE,
	MSK1_TTSTYLE_NOFADE,
	MSK1_TTSTYLE_NOPREFIX,
	MSK1_TTSTYLE_USEVISUALSTYLES
} MSK1_TTSTYLE_FLAGS;

typedef enum MSK1_TKBSTYLE_FLAGS
{
	MSK1_TKBSTYLE_AUTOTICKS,
	MSK1_TKBSTYLE_VERT,
	MSK1_TKBSTYLE_HORZ,
	MSK1_TKBSTYLE_TOP,
	MSK1_TKBSTYLE_BOTTOM,
	MSK1_TKBSTYLE_LEFT,
	MSK1_TKBSTYLE_RIGHT,
	MSK1_TKBSTYLE_BOTH,
	MSK1_TKBSTYLE_NOTICKS,
	MSK1_TKBSTYLE_ENABLESELRANGE,
	MSK1_TKBSTYLE_FIXEDLENGTH,
	MSK1_TKBSTYLE_NOTHUMB,
	MSK1_TKBSTYLE_TOOLTIPS,
	MSK1_TKBSTYLE_REVERSED,
	MSK1_TKBSTYLE_DOWNISLEFT,
	MSK1_TKBSTYLE_NOTIFYBEFOREMOVE,
	MSK1_TKBSTYLE_TRANSPARENTBKGND
} MSK1_TKBSTYLE_FLAGS;

typedef enum MSK1_TVSTYLE_FLAGS
{
	MSK1_TVSTYLE_CHECKBOXES,
	MSK1_TVSTYLE_DISABLEDRAGDROP,
	MSK1_TVSTYLE_EDITLABLES,
	MSK1_TVSTYLE_FULLROWSELECT,
	MSK1_TVSTYLE_HASBUTTONS,
	MSK1_TVSTYLE_HASLINES,
	MSK1_TVSTYLE_INFOTIP,
	MSK1_TVSTYLE_LINESATROOT,
	MSK1_TVSTYLE_NOHSCROLL,
	MSK1_TVSTYLE_NONEVENHEIGHT,
	MSK1_TVSTYLE_NOSCROLL,
	MSK1_TVSTYLE_NOTOOLTIPS,
	MSK1_TVSTYLE_RTLREADING,
	MSK1_TVSTYLE_SHOWSELALWAYS,
	MSK1_TVSTYLE_SINGLEEXPAND,
	MSK1_TVSTYLE_TRACKSELECT
} MSK1_TVSTYLE_FLAGS;

typedef enum MSK1_TVSTYLE_EX_FLAGS
{
	MSK1_TVSTYLE_EX_AUTOHSCROLL,
	MSK1_TVSTYLE_EX_DIMMEDCHECKBOXES,
	MSK1_TVSTYLE_EX_DOUBLEBUFFER,
	MSK1_TVSTYLE_EX_DRAWIMAGESYNC,
	MSK1_TVSTYLE_EX_EXLUSIONCHECKBOCES,
	MSK1_TVSTYLE_EX_FADEINOUTEXPANDOS,
	MSK1_TVSTYLE_EX_MULTISELECT,
	MSK1_TVSTYLE_EX_NOINDENTSTATE,
	MSK1_TVSTYLE_EX_NOSINGLECOLLAPSE,
	MSK1_TVSTYLE_EX_PARTIALCHECKBOXES,
	MSK1_TVSTYLE_EX_RICHTOOLTIP
} MSK1_TVSTYLE_EX_FLAGS;

typedef enum MSK1_UDSTYLE_FLAGS
{
	MSK1_UDSTYLE_ALIGNLEFT,
	MSK1_UDSTYLE_ALIGNRIGHT,
	MSK1_UDSTYLE_ARROWKEYS,
	MSK1_UDSTYLE_AUTOBUDDY,
	MSK1_UDSTYLE_HORZ,
	MSK1_UDSTYLE_HOTTRACK,
	MSK1_UDSTYLE_NOTHOUSANDS,
	MSK1_UDSTYLE_SETBUDDYINT,
	MSK1_UDSTYLE_WRAP
} MSK1_UDSTYLE_FLAGS;

typedef enum MSK1_COMMAND_TYPE
{
	MSK1_COMMAND_DEFAULT,
	MSK1_COMMAND_CREATE
} MSK1_COMMANDTYPE;

typedef enum MSK1_MESSAGE_TYPE
{
	MSK1_MESSAGE_PRECREATE = 0x8001,
} MSK1_MESSAGETYPE;

typedef enum MSK1_EVENT_TYPE
{
	MSK1_EVENT_CHANGED	 = 0x8002,
	MSK1_EVENT_DRAG		 = 0x8003
};

typedef enum MSK1_WINDOW_TYPE
{
	MSK1_WINDOW_TYPE_PANE,
	MSK1_WINDOW_TYPE_TOOL,
	MSK1_WINDOW_TYPE_DIALOG,
	MSK1_WINDOW_TYPE_MDI,
	MSK1_WINDOW_TYPE_TEXT,
	MSK1_WINDOW_TYPE_TAB,
	MSK1_WINDOW_TYPE_STATUSBAR,
	MSK1_WINDOW_TYPE_TOOLBAR,
	MSK1_WINDOW_TYPE_BUTTON
} MSK1_WINDOW_TYPE;

typedef enum MSK1_WINDOWPLACEMENT_FLAGS
{
	MSK1_WINDOWPLACEMENT_NONE,
	MSK1_WINDOWPLACEMENT_DOCK_LEFT,
	MSK1_WINDOWPLACEMENT_DOCK_RIGHT,
	MSK1_WINDOWPLACEMENT_DOCK_TOP,
	MSK1_WINDOWPLACEMENT_DOCK_BOTTOM,
	MSK1_WINDOWPLACEMENT_DOCK_FILL,
	MSK1_WINDOWPLACEMENT_DOCK_FLOAT,
	MSK1_WINDOWPLACEMENT_ANCHOR_LEFT,
	MSK1_WINDOWPLACEMENT_ANCHOR_RIGHT,
	MSK1_WINDOWPLACEMENT_ANCHOR_TOP,
	MSK1_WINDOWPLACEMENT_ANCHOR_BOTTOM
} MSK1_WINDOWPLACEMENT_FLAGS;

typedef enum MSK1_ANCHOR_OPTION
{
	MSK1_ANCHOR_OPTION_DEFAULT,
	MSK1_ANCHOR_OPTION_CHAINED
};

typedef enum MSK1_MESSAGELOOP_FLAG
{
	MSK1_MESSAGELOOP_IDLEPROCESS,
	MSK1_MESSAGELOOP_PREPROCESS,
	MSK1_MESSAGELOOP_EXITPROCESS,
	MSK1_MESSAGELOOP_POSTPROCESS
} MSK1_MESSAGELOOP_FLAG;

typedef enum MSK1_PROPERTY_KEY
{
	MSK1_PROPERTY_BACKGROUND,
	MSK1_PROPERTY_MARGIN
};

typedef enum MSK1_FULLSCREEN_OPTIONS
{
	MSK1_FULLSCREEN_STANDARD,
	MSK1_FULLSCREEN_ABSOLUTE,
	MSK1_FULLSCREEN_CLIENTONLY_STANDARD,
	MSK1_FULLSCREEN_CLIENTONLY_ABSOLUTE
};

typedef enum MSK1_TOOLWINDOW_STYLE
{
	MSK1_TOOLWINDOW_STYLE_DEFAULT
};

typedef enum MSK1_MENUBAR_STYLE
{
	MSK1_MENUBAR_STYLE_DEFAULT
};

typedef enum MSK1_APPLICATION_PROPERTIES
{
	MSK1_APPLICATION_SYSMENU,
	MSK1_APPLICATION_LEGACY_GRAPHICS,
	MSK1_APPLICATION_ACCERATED_GRAPHICS
};

typedef struct MSK1_MARGIN_U {
	UINT32 left;
	UINT32 top;
	UINT32 right;
	UINT32 bottom;
} MSK1_MARGIN_U;

typedef struct MSK1_SIZE_U {
	UINT32 width;
	UINT32 height;
} MSK1_SIZE_U;

typedef struct MSK1_POINT_U {
	UINT32 x;
	UINT32 y;
} MSK1_POINT_U;

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf0") IMSK1Framework  : 
	public IUnknown
{
	__checkReturn STDMETHOD(Initialize)(
		__in IMSK1Application* pApplication
		) PURE;

	__checkReturn STDMETHOD(SetValue)(
		__in MSK1_PROPERTY_KEY key, 
		__in DWORD value
		) PURE;

	__checkReturn STDMETHOD_(int, Run)(void) PURE;

	__checkReturn STDMETHOD(Destroy)(void) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf1") IMSK1Application  : 
	public IUnknown
{
	__checkReturn STDMETHOD(OnCreateCommand)(
		__in UINT cmdId,
		__in MSK1_COMMAND_TYPE cmdType,
		__inout IMSK1CommandHandler** ppCommandHandler
		) PURE;

	__checkReturn STDMETHOD(OnDestroyCommand)(void) PURE;

	__checkReturn STDMETHOD_(int, OnMessageLoop)(
		__in MSK1_MESSAGELOOP_FLAG flag,
		__inout LPMSG msg
		) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf2") IMSK1CommandHandler  : 
	public IUnknown
{
	__checkReturn STDMETHOD(OnProcessMessage)(
		__in UINT msg,
		__in WPARAM wParam,
		__in LPARAM lParam,
		__in IMSK1Window* pWnd
		) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf3") IMSK1Window  : 
	public IUnknown
{
	__checkReturn STDMETHOD(CreateStatusBar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_SBARSTYLE_FLAGS sbarStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1StatusBarCtrl** ppStatusbarCtrl
		) PURE;
	
	__checkReturn STDMETHOD(CreateScrollBar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_SBSTYLE_FLAGS sbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ScrollBarCtrl** ppScrollbarCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateProgressBar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_PBSTYLE_FLAGS pbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ProgressBarCtrl** ppProgressBarCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateReBar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_RBSTYLE_FLAGS rbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ReBarCtrl** ppReBarCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateToolBar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_TBSTYLE_FLAGS tbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ToolBarCtrl** ppToolBarCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateTextBox)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_ESTYLE_FLAGS eStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1TextBoxCtrl** ppTextBoxCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateListBox)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_LBSTYLE_FLAGS lbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ListBoxCtrl** ppListBoxCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateComboBox)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_CBSTYLE_FLAGS cbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ComboBoxCtrl** ppComboBoxCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateRichTextBox)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_RESTYLE_FLAGS reStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1RichTextBoxCtrl** ppRichTextBoxCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateTabView)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_RESTYLE_FLAGS reStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1TabViewCtrl** ppTabViewCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateTreeView)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_TVSTYLE_FLAGS tvStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1TreeViewCtrl** ppTreeViewCtrl
		) PURE;

	__checkReturn STDMETHOD(CreatePropertySheetDialog)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__inout IMSK1PropertySheetDialog** ppPropertySheetDialog
		) PURE;

	__checkReturn STDMETHOD(CreateTaskDialog)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__inout IMSK1TaskDialog** ppTaskDialog
		) PURE;

	__checkReturn STDMETHOD(CreateDateTimePicker)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_DTSTYLE_FLAGS dtStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1DateTimePickerCtrl** ppDateTimePickerCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateHeader)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_HDSTYLE_FLAGS hdStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1HeaderCtrl** ppHeaderCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateAnimation)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_ANISTYLE_FLAGS aniStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1AnimationCtrl** ppAnimationCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateUpDown)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_UDSTYLE_FLAGS udStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1UpDownCtrl** ppUpDownCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateButton)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_BTNSTYLE_FLAGS btnStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ButtonCtrl** ppButtonCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateMonthCalendar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,	
		__in MSK1_MCSTYLE_FLAGS mcStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1MonthCalendarCtrl** ppMonthCalendarCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateToolTip)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_TTSTYLE_FLAGS ttStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ToolTipCtrl** ppToolTipCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateHotKey)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__inout IMSK1HotKeyCtrl** ppHotKeyCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateImageList)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,	
		__inout IMSK1ImageListCtrl** ppImageListCtrl
		) PURE;

	__checkReturn STDMETHOD(CreatePager)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,	
		__in MSK1_PGSTYLE_FLAGS pgrStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1PagerCtrl** ppPagerCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateStatic)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,	
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1StaticCtrl** ppStaticCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateSysLink)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__inout IMSK1SysLinkCtrl** ppSysLinkCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateTrackBar)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_TKBSTYLE_FLAGS tkbStyle,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1TrackBarCtrl** ppTrackBarCtrl
		) PURE;

	__checkReturn STDMETHOD(CreateToolWindow)(
		__in MSK1_POINT_U position,
		__in MSK1_SIZE_U size,
		__in MSK1_WINDOWPLACEMENT_FLAGS wpFlags,
		__inout IMSK1ToolWindow** ppToolWindowCtrl
		) PURE;

	__checkReturn STDMETHOD(SetMargin)(
		__in MSK1_MARGIN_U margin
		) PURE;

	__checkReturn STDMETHOD(SetBorder)(
		__in D2D1_COLOR_F color,
		__in LONG size
		) PURE;

	__checkReturn STDMETHOD_(FLOAT, PixeltoDipX)(
		__in int x
		) PURE;

	__checkReturn STDMETHOD_(FLOAT, PixeltoDipY)(
		__in int y
		) PURE;

	__checkReturn STDMETHOD_(HINSTANCE, GetModuleInstance(void)) PURE;

	__checkReturn STDMETHOD_(HWND, GetWindowHandle(void)) PURE;

	__checkReturn STDMETHOD(PlaceWindow)(
		__in UINT id,
		__in MSK1_WINDOWPLACEMENT_FLAGS dock
		) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf6") IMSK1StatusBarCtrl : 
	public virtual IMSK1Window
{
	///<comment> Retrieves the current widths of the horizontal and vertical borders of a status window. </comment>
	__checkReturn STDMETHOD_(BOOL, GetBorders(
		MSK1_STATUSBAR_BORDERSIZE_U borderSizes
		)) PURE;

	__checkReturn STDMETHOD_(HICON, GetIcon(
		UINT iPart
		)) PURE;

	__checkReturn STDMETHOD_(UINT, GetParts(
		UINT nParts,
		UINT* Parts
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetRect(
		UINT nPane,
		LPRECT lpRect
		)) PURE;

	__checkReturn STDMETHOD_(UINT, GetText(
		LPCTSTR lpszText, 
		UINT nPane,
		UINT* pType = NULL
		)) PURE;

	__checkReturn STDMETHOD_(UINT, GetTextLength(
		UINT nPane,
		UINT* pType = NULL
		)) PURE;

	__checkReturn STDMETHOD_(LPCTSTR, GetTipText(
		UINT nPane
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, IsSimple(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetBkColor(
		COLORREF cr,
		BOOL bRedraw = FALSE
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetIcon(
		UINT nPane, 
		HICON hIcon
		)) PURE;

	__checkReturn STDMETHOD_(void, SetMinHeight(
		UINT nHeight
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetParts(
		UINT nParts, 
		UINT* pWidths
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetSimple(
		BOOL bSimple = TRUE
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetText(
		LPCTSTR lpszText, 
		UINT nPane, 
		UINT nType,
		COLORREF bgColor = CLR_DEFAULT
		)) PURE;

	__checkReturn STDMETHOD_(void, SetTipText(
		int nPane, 
		LPCTSTR pszTipText 
		)) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf7") IMSK1ScrollBarCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf8") IMSK1ProgressBarCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fcf9") IMSK1ReBarCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd00") IMSK1ToolBarCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd01") IMSK1TextBoxCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd02") IMSK1ListBoxCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd03") IMSK1ComboBoxCtrl : 
	public virtual IMSK1Window
{
	__checkReturn STDMETHOD_(int, AddItemData(
		__in LPARAM data
		)) PURE;

	__checkReturn STDMETHOD_(int, AddString(
		__in LPCTSTR lpsz
		)) PURE;

	__checkReturn STDMETHOD_(int, DeleteString(
		__in  int index
		)) PURE;

	__checkReturn STDMETHOD_(int, Dir(
		__in MSK1_CBDDL_ATTR attrs,
		__in LPCTSTR lpszFileSpec
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, Enable(
		__in BOOL bEnable
		)) PURE;

	__checkReturn STDMETHOD_(int, FindItemData(
		__in int nIndexStart,
		__in LPARAM data
		)) PURE;

	__checkReturn STDMETHOD_(int, FindString(
		__in int nIndexStart,
		__in LPCTSTR lpszFind
		)) PURE;

	__checkReturn STDMETHOD_(int, FindStringExact(
		__in int nIndexStart,
		__in LPCTSTR lpszFind
		)) PURE;

	__checkReturn STDMETHOD_(int, GetCount(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetCueBannerText(
		__in LPWSTR lpwText,
		__in int cchText
		)) PURE;

	__checkReturn STDMETHOD_(int, GetCurSel(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetDroppedControlRect(
		__inout RECT* lprc
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetDroppedState(
		)) PURE;

	__checkReturn STDMETHOD_(UINT, GetExtendedUI(
		)) PURE;

	__checkReturn STDMETHOD_(LRESULT, GetItemData(
		__in int nIndex
		)) PURE;

	__checkReturn STDMETHOD_(int, GetItemHeight(
		)) PURE;

	__checkReturn STDMETHOD_(int, GetLBText(
		__in int nIndex,
		__in LPCTSTR lpszBuffer
		)) PURE;

	__checkReturn STDMETHOD_(int, GetLBTextLen(
		__in int nIndex
		)) PURE;

	__checkReturn STDMETHOD_(int, GetMinVisible(
		)) PURE;

	__checkReturn STDMETHOD_(int, GetText(
		 __in LPTSTR lpch,
		 __in int cchMax
		)) PURE;

	__checkReturn STDMETHOD_(int, GetTextLength(
		)) PURE;

	__checkReturn STDMETHOD_(int, InsertItemData(
		  __in int nIndex,
		  __in LPARAM data
		)) PURE;

	__checkReturn STDMETHOD_(int, InsertString(
		  __in int nIndex,
		  __in LPCSTR lpsz
		)) PURE;

	__checkReturn STDMETHOD_(int, LimitText(
		  __in int cchMax
		)) PURE;

	__checkReturn STDMETHOD_(int, ResetContent(
		)) PURE;

	__checkReturn STDMETHOD_(int, SelectItemData(
		__in int nIndexStart,
		__in LPARAM data
		)) PURE;

	__checkReturn STDMETHOD_(int, SelectString(
		__in int nIndexStart,
		__in LPCTSTR lpszFind
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetCueBannerText(
		__in LPCWSTR lpcwText
		)) PURE;

	__checkReturn STDMETHOD_(int, SetCurSel(
		__in int nIndex
		)) PURE;

	__checkReturn STDMETHOD_(int, SetExtendedUI(
		__in UINT nFlags
		)) PURE;

	__checkReturn STDMETHOD_(int, SetItemData(
		__in int nIndex,
		__in LPARAM data
		)) PURE;

	__checkReturn STDMETHOD_(int, SetItemHeight(
		__in int nIndex,
		__in int cyItem
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetMinVisible(
		__in  int nMinVisible
		)) PURE;

	__checkReturn STDMETHOD_(int, SetText(
		__in LPTSTR lpsz
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, ShowDropdown(
		__in BOOL bShow
		)) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd04") IMSK1RichTextBoxCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd05") IMSK1TabViewCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd06") IMSK1TreeViewCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd07") IMSK1PropertySheetDialog : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd08") IMSK1TaskDialog : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd09") IMSK1DateTimePickerCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd10") IMSK1HeaderCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd10") IMSK1AnimationCtrl : 
	public virtual IMSK1Window
{
	__checkReturn STDMETHOD_(BOOL, Close(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, IsPlaying(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, Open(
		__in LPTSTR lpszName
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, Play(
		__in UINT wFrom,
		__in UINT wTo,
		__in UINT cRepeat
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, Seek(
		__in UINT wFrame
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, Stop(
		)) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd11") IMSK1UpDownCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd12") IMSK1ButtonCtrl : 
	public virtual IMSK1Window
{
	__checkReturn STDMETHOD_(BOOL, Enable(
		__in BOOL bEnable
		)) PURE;

	__checkReturn STDMETHOD_(LRESULT, GetCheck(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetIdealSize(
		__in MSK1_SIZE_U size
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetImageList(
		__inout PBUTTON_IMAGELIST pImageList
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetNote(
		__in LPCWSTR psz,
		__in int lengthOfNote
		)) PURE;

	__checkReturn STDMETHOD_(WCHAR, GetNoteLength(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetSplitInfo(
		__inout BUTTON_SPLITINFO *pInfo
		)) PURE;

	__checkReturn STDMETHOD_(LRESULT, GetState(
		)) PURE;

	__checkReturn STDMETHOD_(int, GetText(
		__in LPTSTR lpch,
		__in int cchMax
		)) PURE;

	__checkReturn STDMETHOD_(int, GetTextLength(
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, GetTextMargin(
		__in MSK1_MARGIN_U margin
		)) PURE;

	__checkReturn STDMETHOD_(LRESULT, SetCheck(
		__in MSK1_BTNSETCHECK_STATE btnCheckState
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetDropDownState(
		__in BOOL bDropDown
		)) PURE;

	__checkReturn STDMETHOD_(LRESULT, SetElevationRequiredState(
		__in BOOL bRequired
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetImageList(
		__in  PBUTTON_IMAGELIST pImageList
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetNote(
		__in PCWSTR psz
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetSplitInfo(
		__in BUTTON_SPLITINFO *pInfo
		)) PURE;
	
	__checkReturn STDMETHOD_(BOOL, SetState(
		__in BOOL state
		)) PURE;

	__checkReturn STDMETHOD_(int, SetText(
		__in LPTSTR lpsz
		)) PURE;

	__checkReturn STDMETHOD_(LRESULT, SetStyle(
		__in MSK1_BTNSTYLE_FLAGS btnStyle,
		__in BOOL bRedraw
		)) PURE;

	__checkReturn STDMETHOD_(BOOL, SetTextMargin(
		__in MSK1_MARGIN_U margin
		)) PURE;
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd12") IMSK1MonthCalendarCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd13") IMSK1ToolTipCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd14") IMSK1HotKeyCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd15") IMSK1ImageListCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd16") IMSK1PagerCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd17") IMSK1StaticCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd18") IMSK1SysLinkCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd18") IMSK1TrackBarCtrl : 
	public virtual IMSK1Window
{
};

MSK_DECLARE_INTERFACE("d7eaa557-f4a0-41e1-ad0a-58b10e58fd19") IMSK1ToolWindow : 
	public virtual IMSK1Window
{
};

#ifdef __cplusplus
extern "C"
{
#endif

	__declspec(dllexport) HRESULT WINAPI MSK1Create(
		__inout IMSK1Framework** pFramework
		);

#ifdef __cplusplus
}
#endif

#ifdef MSK1_USE_C_DEFINITIONS
#endif

DEFINE_GUID(IID_IMSK1Framework,			0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf0);
DEFINE_GUID(IID_IMSK1Application,		0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf1);
DEFINE_GUID(IID_IMSK1CommandHandler,	0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf2);
DEFINE_GUID(IID_IMSK1Window,			0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf3);
DEFINE_GUID(IID_IMSK1ToolWindow,		0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf4);
DEFINE_GUID(IID_IMSK1MenuBarControl,	0xd7eaa557,0xf4a0,0x41e1,0xad,0x0a,0x58,0xb1,0x0e,0x58,0xfc,0xf5);

namespace MSK1 {
	FORCEINLINE 
		MSK1_SIZE_U SizeU(
		UINT32 width, 
		UINT32 height
		) 
	{
		MSK1_SIZE_U size = {width, height};
		return size;
	}

	FORCEINLINE 
		MSK1_POINT_U PointU(
		UINT32 x,
		UINT32 y
		) 
	{
		MSK1_POINT_U pt = {x, y};
		return pt;
	}

	FORCEINLINE 
		MSK1_MARGIN_U MarginU(
		UINT32 left, 
		UINT32 top, 
		UINT32 right, 
		UINT32 bottom
		)
	{
		MSK1_MARGIN_U margin = {left, top, right, bottom};
		return margin;
	}
}

#endif // #ifndef _MSK1_H_