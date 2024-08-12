/* See LICENSE file for copyright and license details. */
#define ICONSPACING 5 /* space (pixels) between icon and title */
#define ICONSIZE (bh - 4) /* or adaptively preserve 2 pixels each side */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systrayiconsize = 16; /* systray icon size in px */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IosevkaNerdFont:size=14" };

/* colors */
static const char normbordercolor[]       = "#3B4252";
static const char normbgcolor[]           = "#2E3440";
static const char normfgcolor[]           = "#D8DEE9";
static const char selbordercolor[]        = "#434C5E";
static const char selbgcolor[]            = "#434C5E";
static const char selfgcolor[]            = "#ECEFF4";

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
};

static const char *const autostart[] = {
  "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
  "nm-applet", NULL,
  "dunst", NULL,
  "flameshot", NULL,
  "picom", "--config", "/home/giuseppe/.config/picom/picom.conf", NULL,
  "pipewire", NULL,
  "pipewire-pulse", NULL,
  "wireplumber", NULL,
  "sh", "-c", "feh --randomize --bg-fill ~/.wallpapers/*", NULL,
  "nextcloud", "--background", "--isvfsenabled", "1", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "www", ">_", "</>", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title       tags mask     isfloating   monitor */
	{ "firefox",    NULL,       NULL,       1 << 0,       0,           -1 },
	{ "Alacritty",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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

/* commands */
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/* volume commands */ 
static const char *up_vol[]   = { "wpctl", "set-volume", "-l", "1.2", "@DEFAULT_AUDIO_SINK@", "10%+", NULL };
static const char *down_vol[] = { "wpctl", "set-volume", "-l", "1.2", "@DEFAULT_AUDIO_SINK@", "10%-", NULL };
static const char *mute_vol[] = { "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };

/* brightness */
static const char *brighter[] = { "brightnessctl", "set", "10%+", NULL };
static const char *dimmer[]   = { "brightnessctl", "set", "10%-", NULL };

/* brightness */
static const char *fullscreenshot_cl[] = { "flameshot", "full", "--clipboard", NULL };
static const char *fullscreenshot_save[] = { "flameshot", "-p", "$HOME/Pictures/Screenshots/", NULL };
static const char *screenshot_gui[]   = { "flameshot", "gui", NULL };

static const Keychord *keychords[] = {
   /* Keys                                     function               argument */
	&((Keychord){1, {{ MODKEY,XK_r }},                       spawn,              	  {.v = launchercmd } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_Return }},        spawn,              	  {.v = termcmd } }),
	&((Keychord){1, {{ MODKEY,XK_b }},                       spawn,              	  SHCMD("xdg-open https://") }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_b }},             togglebar,             {0} }),
	&((Keychord){1, {{ MODKEY,XK_j }},                       focusstack,         	  {.i = +1 } }),
	&((Keychord){1, {{ MODKEY,XK_k }},                       focusstack,         	  {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,XK_i }},                       incnmaster,         	  {.i = +1 } }),
	&((Keychord){1, {{ MODKEY,XK_d }},                       incnmaster,         	  {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,XK_h }},                       setmfact,           	  {.f = -0.05} }),
	&((Keychord){1, {{ MODKEY,XK_l }},                       setmfact,           	  {.f = +0.05} }),
	&((Keychord){1, {{ MODKEY,XK_Return }},                  zoom,               	  {0} }),
	&((Keychord){1, {{ MODKEY,XK_Tab }},                     view,               	  {0} }),
	&((Keychord){1, {{ MODKEY,XK_w }},                       killclient,         	  {0} }),
	&((Keychord){1, {{ MODKEY,XK_t }},                       setlayout,          	  {.v = &layouts[0]} }),
	&((Keychord){1, {{ MODKEY,XK_f }},                       setlayout,          	  {.v = &layouts[1]} }),
	&((Keychord){1, {{ MODKEY,XK_m }},                       setlayout,          	  {.v = &layouts[2]} }),
	&((Keychord){1, {{ MODKEY,XK_u }},                       setlayout,          	  {.v = &layouts[3]} }),
	&((Keychord){1, {{ MODKEY,XK_o }},                       setlayout,             {.v = &layouts[4]} }),
	&((Keychord){1, {{ MODKEY|ControlMask,XK_c }}, 		       cyclelayout,    		    {.i = +1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask|ControlMask,XK_c }}, cyclelayout,    		    {.i = -1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_m }},             togglefakefullscreen,	{0} }),
	&((Keychord){1, {{ MODKEY,XK_space }},                   setlayout,          	  {0} }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_space }},         togglefloating,     	  {0} }),
	&((Keychord){1, {{ MODKEY,XK_0 }},                       view,                  {.ui = ~0 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_0 }},             tag,                	  {.ui = ~0 } }),
	&((Keychord){1, {{ MODKEY,XK_comma }},                   focusmon,           	  {.i = -1 } }),
	&((Keychord){1, {{ MODKEY,XK_period }},                  focusmon,           	  {.i = +1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_comma }},         tagmon,             	  {.i = -1 } }),
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_period }},        tagmon,             	  {.i = +1 } }),
  &((Keychord){1, {{ 0,XF86XK_AudioMute }},                spawn,                 {.v = mute_vol } }),
  &((Keychord){1, {{ 0,XF86XK_AudioLowerVolume }},         spawn,                 {.v = down_vol } }),
  &((Keychord){1, {{ 0,XF86XK_AudioRaiseVolume }},         spawn,             	  {.v = up_vol } }),
  &((Keychord){1, {{ 0,XF86XK_MonBrightnessDown }},        spawn,                 {.v = dimmer } }),
  &((Keychord){1, {{ 0,XF86XK_MonBrightnessUp }},          spawn,                 {.v = brighter } }),
  &((Keychord){1, {{ 0,XK_Print }},     	    	           spawn,              	  {.v = fullscreenshot_cl } }),
  &((Keychord){1, {{ MODKEY,XK_Print }},     	             spawn,                 {.v = fullscreenshot_save } }),
  &((Keychord){1, {{ MODKEY|ShiftMask,XK_Print }},     	   spawn,                 {.v = screenshot_gui } }),
	TAGKEYS(XK_1,                                           	          0)
	TAGKEYS(XK_2,                                           	          1)
	TAGKEYS(XK_3,                                           	          2)
	TAGKEYS(XK_4,                                           	          3)
	TAGKEYS(XK_5,                                           	          4)
	&((Keychord){1, {{ MODKEY|ShiftMask,XK_q }},             quit,               	  {1} }),
	&((Keychord){1, {{ MODKEY|ShiftMask|ControlMask,XK_q }}, quit,               	  {0} }),
  &((Keychord){1, {{ MODKEY,XK_Escape }},                  spawn,                SHCMD("$HOME/.config/rofi/powermenu.sh")}), // exit d)wm
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
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

