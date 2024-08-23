/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

/* standard gcc libs */
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* x11 libs */
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/extensions/Xinerama.h>
#include <X11/keysym.h>

/* config */
#include "config.h"

/* definitions */
#define MAX(A, B)			((A) > (B) ? (A) : (B))
#define MIN(A, B)			((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)	((A) <= (X) && (X) <= (B))

/* global vars */
Display *dpy;
Window root;

/* initial static functions */
static void die(const char *fmt, ...);
static void setup(void);

/* standard funcs */
void die(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	exit(1);
}

/* window manager functions */
void setup(void)
{
	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Failed to open display\\n");
		exit(1);
	}

	root = DefaultRootWindow(dpy);

	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F1")), MODKEY, root, True, GrabModeAsync, GrabModeAsync);
	XGrabButton(dpy, Button1, MODKEY, root, True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, Button3, MODKEY, root, True, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
}

int main(int argc, char *argv[])
{
	/* extra arguments/settings */
	if (argc == 2 && !strcmp("-v", argv[1]))
		die("xanthid-%s", VER);
	else if (argc != 1)
		die("usage: xanthid [-v]");
	
	/* setup */
	setup();
}