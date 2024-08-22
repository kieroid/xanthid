/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

/* standard gcc libs */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* x11 libs */
#include <X11/Xlib.h>
#include <X11/keysym.h>

/* config */
/* #include "config.h" */

#define MAX(A, B)		((A) > (B) ? (A) : (B))
#define MIN(A, B)		((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)	((A) <= (X) && (X) <= (B))

static void die(const char *fmt, ...);
static void *ecalloc(size_t nmemb, size_t size);

/* standard funcs */
void
die(const char *fmt, ...)
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


void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size)))
		die("calloc:");
	return p;
}

int main(int argc, char *argv[])
{
	if (argc == 2 && !strcmp("-v", argv[1]))
		die("xanthid-%s", VER);
	Display * dpy;
	XWindowAttributes attr;
	XButtonEvent start;
	XEvent ev;

	if(!(dpy = XOpenDisplay(0x0))) return 1;

	XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F1")), Mod1Mask,
		DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);

	XGrabButton(dpy, 1, Mod1Mask, DefaultRootWindow(dpy), True,
		ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 3, Mod1Mask, DefaultRootWindow(dpy), True,
		ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

	start.subwindow = None;
	for(;;)
	{
		XNextEvent(dpy, &ev);

		if(ev.type == KeyPress && ev.xkey.subwindow != None)
			XRaiseWindow(dpy, ev.xkey.subwindow);
		else if(ev.type == ButtonPress && ev.xbutton.subwindow != None)
		{
			XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
			start = ev.xbutton;
		}
		else if(ev.type == MotionNotify && start.subwindow != None)
		{
			int xdiff = ev.xbutton.x_root - start.x_root;
			int ydiff = ev.xbutton.y_root - start.y_root;
			XMoveResizeWindow(dpy, start.subwindow,
			attr.x + (start.button==1 ? xdiff : 0),
			attr.y + (start.button==1 ? ydiff : 0),
			MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
			MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
		}
		else if(ev.type == ButtonRelease)
		{
			start.subwindow = None;
		}
	}
}


