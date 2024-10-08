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
XWindowAttributes attr;
XButtonEvent start;

/* initial static functions */
static void die(const char *fmt, ...);
static void run(void);
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

void XMotionNotify(XEvent ev) {
	int xdiff = ev.xbutton.x_root - start.x_root;
	int ydiff = ev.xbutton.y_root - start.y_root;
	XMoveResizeWindow(dpy, start.subwindow,
	attr.x + (start.button==1 ? xdiff : 0),
	attr.y + (start.button==1 ? ydiff : 0),
	MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
	MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
}

void run(void) {
	XEvent ev;
	while (!XNextEvent(dpy, &ev)) {
		if (ev.type == KeyPress && ev.xkey.subwindow != None) {
			XRaiseWindow(dpy, ev.xkey.subwindow);
		} else if (ev.type == ButtonPress && ev.xbutton.subwindow != None) {
			XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
			start = ev.xbutton;
		} else if (ev.type == MotionNotify && start.subwindow != None) {
			XMotionNotify(ev);
		} else if (ev.type == ButtonRelease) {
			start.subwindow = None;
		}

		
	}
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

	/* run */
	run();
}
