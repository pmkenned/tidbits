#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>


Display * dis;
int screen;
Window win;
GC gc;

void init_x();
void close_x();
void redraw();

int main() {
	XEvent event;
	KeySym key;
	char text[255];

	init_x();

	while(1) {	
		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
			redraw();
		}
		if (event.type==KeyPress&&
			XLookupString(&event.xkey,text,255,&key,0)==1) {
			if (text[0]=='q') {
				close_x();
			}
			printf("You pressed the %c key!\n",text[0]);
		}
		if (event.type==ButtonPress) {
			int x=event.xbutton.x,
			y=event.xbutton.y;
			strcpy(text,"X is FUN!");
			XSetForeground(dis,gc,rand()%event.xbutton.x%255);
			XDrawString(dis,win,gc,x,y, text, strlen(text));
		}
	}
	return 0;
}

void init_x() {
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);

	if(dis == NULL) {
	    fprintf(stderr,"error: cannot open window\n");
	    exit(1);
    }

	screen = DefaultScreen(dis);
	black = BlackPixel(dis,screen),	/* get color black */
	white = WhitePixel(dis, screen);  /* get color white */

	win = XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		200, 300, 5, black, white);

	XSetStandardProperties(dis,win,"My Window","HI!",None,NULL,0,NULL);

	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	gc=XCreateGC(dis, win, 0,0);        

	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);

	XClearWindow(dis, win);
	XMapRaised(dis, win);
}

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis, win);
	XCloseDisplay(dis);
	exit(1);
}

void redraw() {
	XClearWindow(dis, win);
}
