/* See LICENSE file for copyright and license details. */
#define ICONSPACING 5 /* space (pixels) between icon and title */
#define ICONSIZE (bh - 4) /* or adaptively preserve 2 pixels each side */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IosevkaNerdFont:size=14" };

/* systray */ 
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int systrayiconsize = 16; /* systray icon size in px */

/* colors */ 
#include "colors/tokyo.h"

static const char *colors[][3]      = {
/*                 fg          bg          border   */
  [SchemeNorm]   = { col_normfg, col_normbg, col_normborder },
  [SchemeSel]    = { col_selfg,  col_selbg,  col_selborder  },
  [SchemeTag]    = { col_gray,   col_normbg, col_normbg },
  [SchemeTag1]   = { col_red,    col_normbg, col_normbg },
  [SchemeTag2]   = { col_orange, col_normbg, col_normbg },
  [SchemeTag3]   = { col_yellow, col_normbg, col_normbg },
  [SchemeTag4]   = { col_green,  col_normbg, col_normbg },
  [SchemeTag5]   = { col_cyan,   col_normbg, col_normbg },
  [SchemeLayout] = { col_cyan,   col_normbg, col_normbg }
};
 
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "-t", "spterm", "--class", "spterm", "--config-file", "/home/giuseppe/.config/alacritty/alacritty-scratchpad.toml", NULL };
const char *spcmd2[] = {"alacritty", "-t", "spcalc", "--class", "spcalc", "--config-file", "/home/giuseppe/.config/alacritty/alacritty-scratchpad.toml", "-e", "python", NULL };
const char *spcmd3[] = {"alacritty", "-t", "spfile", "--class", "spfile", "--config-file", "/home/giuseppe/.config/alacritty/alacritty-scratchpad.toml", "-e", "nnn", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",    spcmd1},
	{"spcalc",    spcmd2},
	{"spfile",    spcmd3},
};

static const char *const autostart[] = {
  "/usr/bin/lxpolkit", NULL,
  "nm-applet", NULL,
  "slstatus", NULL,
  "picom", "--animations", NULL,
  "pipewire", NULL,
  "pipewire-pulse", NULL,
  "wireplumber", NULL,
  "sh", "-c", "feh --bg-fill ~/.wallpapers/street-tn.png", NULL,
  "nextcloud", "--isvfsenabled", "1", "--background", NULL,
  "brightnessctl", "set", "50%", NULL,
  "flameshot", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "www", ">_", "</>", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title       	tags mask     isfloating,   isterminal,   noswallow,  monitor */
	{ "firefox",    NULL,       NULL,       	1 << 0,       0,            0,            0,          -1 },
	{ "Alacritty",  NULL,       NULL,       	1 << 1,       0,            1,            0,          -1 },
	{ NULL,         NULL,       "Event Tester",  	0,        0,            0,            1,          -1 }, /* xev */
	{ "Nextcloud",	NULL,       NULL,         0,            1,            0,            0,          -1 },
	{ "pavucontrol",NULL,       NULL,         0,            1,            0,            0,          -1 },
	{ NULL,         "spterm",   NULL,         SPTAG(0),     1,            1,            1,          -1 },
	{ NULL,         "spcalc",   NULL,         SPTAG(1),     1,            1,            0,          -1 },
	{ NULL,         "spfile",   NULL,         SPTAG(2),     1,            1,            0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.7; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",    tile },    /* first entry is default */
	{ "><>",    NULL },    /* no layout function means floating behavior */
	{ "[M]",    monocle },
	{ "|M|",    centeredmaster },
	{ ">M>",    centeredfloatingmaster },
	{ NULL,     NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* programs */
static const char *launchercmd[] = { "rofi", "-show", "drun", "-no-config", "-no-lazy-grab", "-modi", "drun", "-theme", "/home/giuseppe/.config/rofi/config.rasi", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *filecmd[]  = { "pcmanfm-qt", NULL };
static const char *browsercmd[]  = { "firefox", NULL };

/* volume commands */ 
static const char *up_vol[]   = { "wpctl", "set-volume", "-l", "1.2", "@DEFAULT_AUDIO_SINK@", "10%+", NULL };
static const char *down_vol[] = { "wpctl", "set-volume", "-l", "1.2", "@DEFAULT_AUDIO_SINK@", "10%-", NULL };
static const char *mute_vol[] = { "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };

/* brightness commands */
static const char *brighter[] = { "brightnessctl", "set", "10%+", NULL };
static const char *dimmer[]   = { "brightnessctl", "set", "10%-", NULL };

/* brightness commands */
static const char *fullscreenshot_cl[] = { "flameshot", "full", "--clipboard", NULL };
static const char *fullscreenshot_save[] = { "flameshot", "-p", "$HOME/Pictures/Screenshots/", NULL };
static const char *screenshot_gui[]   = { "flameshot", "gui", NULL };

static const Keychord *keychords[] = {
  /* Keys                                                   function               argument */
  &((Keychord){1, {{ MODKEY,XK_r }},                        spawn,              	{.v = launchercmd} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_Return }},         spawn,              	{.v = termcmd} }),
	&((Keychord){1, {{ MODKEY,XK_b }},                        spawn,              	{.v = browsercmd} }),
	&((Keychord){1, {{ MODKEY,XK_e}},                         spawn,              	{.v = filecmd} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_b }},              togglebar,           {0} }),
	&((Keychord){1, {{ MODKEY,XK_j }},                        focusstack,         	{.i = +1 } }),
	&((Keychord){1, {{ MODKEY,XK_k }},                        focusstack,         	{.i = -1 } }),
	&((Keychord){1, {{ MODKEY,XK_s }},                        incnmaster,         	{.i = +1 } }),
	&((Keychord){1, {{ MODKEY,XK_d }},                        incnmaster,         	{.i = -1 } }),
	&((Keychord){1, {{ MODKEY,XK_h }},                        setmfact,           	{.f = -0.05} }),
	&((Keychord){1, {{ MODKEY,XK_l }},                        setmfact,           	{.f = +0.05} }),
	&((Keychord){1, {{ MODKEY,XK_Return }},                   zoom,               	{0} }),
	&((Keychord){1, {{ MODKEY,XK_Tab }},                      view,               	{0} }),
	&((Keychord){1, {{ MODKEY,XK_w }},                        killclient,         	{0} }),

  /* scratchpads */
	&((Keychord){2, {{ MODKEY,XK_v }, {0, XK_1}},             togglescratch,      	{ .ui = 0 } }),
	&((Keychord){2, {{ MODKEY,XK_v }, {0, XK_2}},             togglescratch,      	{ .ui = 1 } }),
	&((Keychord){2, {{ MODKEY,XK_v }, {0, XK_3}},             togglescratch,      	{ .ui = 2 } }),

	/* layouts managements */
	&((Keychord){1, {{ MODKEY,XK_t }},                        setlayout,          	{.v = &layouts[0]} }),
	&((Keychord){1, {{ MODKEY,XK_y }},                        setlayout,          	{.v = &layouts[1]} }),
	&((Keychord){1, {{ MODKEY,XK_u }},                        setlayout,          	{.v = &layouts[2]} }),
	&((Keychord){1, {{ MODKEY,XK_i }},                        setlayout,          	{.v = &layouts[3]} }),
	&((Keychord){1, {{ MODKEY,XK_o }},                        setlayout,            {.v = &layouts[4]} }),
	&((Keychord){1, {{ MODKEY,XK_p }}, 		 	                  cyclelayout,    	    {.i = +1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_p }}, 		          cyclelayout,    	    {.i = -1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_m }},              togglefakefullscreen, {0} }),
	&((Keychord){1, {{ MODKEY,XK_space }},                    setlayout,          	{0} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_space }},          togglefloating,     	{0} }),
	&((Keychord){1, {{ MODKEY,XK_0 }},                        view,                 {.ui = ~0 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_0 }},              tag,                	{.ui = ~0 } }),
	&((Keychord){1, {{ MODKEY,XK_comma }},                    focusmon,           	{.i = -1 } }),
	&((Keychord){1, {{ MODKEY,XK_period }},                   focusmon,           	{.i = +1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_comma }},          tagmon,             	{.i = -1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_period }},         tagmon,             	{.i = +1 } }),

	/* Media controls */
  &((Keychord){1, {{ 0,XF86XK_AudioMute }},                 spawn,                {.v = mute_vol } }),
  &((Keychord){1, {{ 0,XF86XK_AudioLowerVolume }},          spawn,                {.v = down_vol } }),
  &((Keychord){1, {{ 0,XF86XK_AudioRaiseVolume }},          spawn,             	  {.v = up_vol } }),
  &((Keychord){1, {{ 0,XF86XK_MonBrightnessDown }},         spawn,                {.v = dimmer } }),
  &((Keychord){1, {{ 0,XF86XK_MonBrightnessUp }},           spawn,                {.v = brighter } }),

  /* screenshot */
  &((Keychord){2, {{ 0,XK_Print }, {0, XK_f}},              spawn,              	{.v = fullscreenshot_cl } }),
  &((Keychord){2, {{ 0,XK_Print }, {0, XK_c}},     	        spawn,                {.v = fullscreenshot_save } }),
  &((Keychord){2, {{ 0,XK_Print }, {0, XK_v}},     	        spawn,                {.v = screenshot_gui } }),

  /* tag key */
	TAGKEYS(XK_1,                                           	          	          0)
	TAGKEYS(XK_2,                                           	          	          1)
	TAGKEYS(XK_3,                                           	          	          2)
	TAGKEYS(XK_4,                                           	          	          3)
	TAGKEYS(XK_5,                                           	          	          4)

  /* dwm exit */
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_q }},             quit,               	  {1} }),
	&((Keychord){1, {{ MODKEY|ShiftMask|ControlMask,XK_q }}, quit,               	  {0} }),
  &((Keychord){1, {{ MODKEY,XK_Escape }},                  spawn,                 SHCMD("$HOME/.config/rofi/powermenu.sh")}), // exit dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

