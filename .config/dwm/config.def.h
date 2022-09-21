/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx       = 2;        /* border pixel of windows */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int gappih         = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv         = 15;       /* vert inner gap between windows */
static const unsigned int gappoh         = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 15;       /* vert outer gap between windows and screen edge */
static const int smartgaps               = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;     /* 0 means no systray */
static const int swallowfloating         = 0;        /* 1 means swallow floating windows by default */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const int vertpad                 = 10;       /* vertical padding of bar */
static const int sidepad                 = 10;       /* horizontal padding of bar */
static const double activeopacity        = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity      = 0.85f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity            = True;     /* Starts with opacity on any unfocused windows */
static const int user_bh                 = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]               = { "Iosevka Nerd Font:size=12" };
static const char dmenufont[]            = "Iosevka Nerd Font:size=12";


static const unsigned int baralphaNorm    = 0x80;
static const unsigned int baralphaSel     = 0xf0;
static const unsigned int borderalpha     = OPAQUE;

/* colors */
/* gruvbox */
static char gb_beige[]    = "#d4be98";
static char gb_red[]      = "#ea6962";
static char gb_orange[]   = "#e78a4e";
static char gb_green[]    = "#a9b665";
static char gb_blue[]     = "#7daea3";
static char gb_purple[]   = "#d3869b";
static char gb_aqua[]     = "#89b482";
static char gb_darkgrey[] = "#282828";

static const char *colors[][3]      = {
	/*fg         bg             border   */
	{ gb_red,    gb_darkgrey,   gb_darkgrey },   /* SchemeNorm gruvbox */
	{ gb_red,    gb_blue,       gb_red   },   /* SchemeSel gruvbox */
	{ gb_aqua,   gb_darkgrey,   gb_darkgrey },   /* SchemeHid gruvbox */
};
static const unsigned int alphas[][3]      = {
	/*fg        bg             border     */
	{ OPAQUE,   baralphaNorm,  borderalpha  },	/* SchemeNorm gruvbox */
	{ OPAQUE,   baralphaSel,   borderalpha  },	/* SchemeSel gruvbox */
	{ OPAQUE,   baralphaNorm,  borderalpha  },	/* SchemeHid gruvbox */
};

static const char *const autostart[] = {
	"sh", "-c", "sxhkd -c $HOME/.config/sxhkd/sxhkdrc", NULL,
	"sh", "-c", "feh --bg-fill $HOME/wallpapers/future-town.jpg", NULL,
	"picom", NULL,
	"status_helper", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title           tags mask     switchtotag    isfloating   isterminal  noswallow    monitor */
	{ "Gimp",       NULL,       NULL,           0,            0,             1,           0,           0,          -1 },
	{ "librewolf",  NULL,       NULL,           0,            0,             0,           0,           0,          -1 },
	{ "St",         NULL,       NULL,           0,            0,             0,           1,           0,          -1 },
	{ NULL,         NULL,       "Event Tester", 0,            0,             0,           0,           1,          -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
	/* modifier                     key                function        argument */
	{ ControlMask|Mod1Mask,         XK_BackSpace,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        layoutscroll,   {.ui = +1} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* helper function for view() */
void
viewex(const Arg *arg)
{
	view(&((Arg) {.ui = 1 << arg->ui}));
}

/* helper function for setlayout() */
void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) {.v = &layouts[arg->ui]}));
}

/* helper function for toggleview() */
void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) {.ui = 1 << arg->ui}));
}

/* helper function for tag() */
void
tagex(const Arg *arg)
{
	tag(&((Arg) {.ui = 1 << arg->ui}));
}

/* helper function for toggletag() */
void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) {.ui = 1 << arg->ui}));
}

/* helper function to view all tags */
void
viewalltags(const Arg *arg)
{
	view(&((Arg) {.ui = ~0}));
}

/* helper function to view last tag */
void
viewlasttag(const Arg *arg)
{
	view(&((Arg) {0}));
}

/* helper function to copy client to all tags */
void
tagall(const Arg *arg)
{
	tag(&((Arg) {.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "togglebar",		togglebar },
	{ "focusstackvis",	focusstackvis },
	{ "focusstackhid",	focusstackhid },
	{ "incnmaster",		incnmaster },
	{ "setmfact",		setmfact },
	{ "pushdown",		pushdown },
	{ "pushup",			pushup },
	{ "zoom",			zoom },
	{ "view",			viewex },
	{ "viewalltags",    viewalltags },
	{ "viewlasttag",	viewlasttag },
	{ "toggleopacity",	toggleopacity },
	{ "killclient",		killclient },
	{ "setlayout", 		setlayoutex },
	{ "cyclelayouts",	layoutscroll },
	{ "fullscreen",		setfullscreen },
	{ "togglefloating",	togglefloating },
	{ "focusmon",		focusmon },
	{ "tagmon",			tagmon },
	{ "show",			show },
	{ "showall",		showall },
	{ "hide",			hide },
	{ "incgaps",		incrgaps },
	{ "togglegaps",		togglegaps },
	{ "defaultgaps",	defaultgaps },
	{ "toggletag",		toggleviewex },
	{ "movetotag",		tagex },
	{ "copytoall",		tagall },
	{ "copytotag",		toggletagex },
	{ "cycleschemes",	schemeCycle },
	{ "quit",			quit },
};
