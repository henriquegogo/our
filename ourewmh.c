/* OUR by Henrique Gogó <henriquegogo@gmail.com>, 2021.
 * MIT License */

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdlib.h>

Display *dpy;
Window root;

Atom NET_ACTIVE_WINDOW, NET_CLIENT_LIST;

void InterceptEvents() {
    XEvent ev;
    XNextEvent(dpy, &ev);

    if (ev.type == MapNotify && !ev.xmap.override_redirect) {
        Window win = ev.xmap.window;
        XChangeProperty(dpy, root, NET_CLIENT_LIST, XA_WINDOW, 32, PropModeAppend, (unsigned char *) &(win), 1);
    } else if (ev.type == UnmapNotify) {
        //XDeleteProperty(dpy, root, NET_CLIENT_LIST);
    } else if (ev.type == FocusIn && ev.xfocus.window) {
        XChangeProperty(dpy, root, NET_ACTIVE_WINDOW, XA_WINDOW, 32, PropModeReplace,
                (unsigned char *) &(ev.xfocus.window), 1);
    } else if (ev.type == FocusOut) {
        XDeleteProperty(dpy, root, NET_ACTIVE_WINDOW);
    }
}

int main() {
    if (!(dpy = XOpenDisplay(NULL))) return 1;

    NET_ACTIVE_WINDOW = XInternAtom(dpy, "_NET_ACTIVE_WINDOW", False);
    NET_CLIENT_LIST = XInternAtom(dpy, "_NET_CLIENT_LIST", False);

    XSelectInput(dpy, root = XDefaultRootWindow(dpy), SubstructureNotifyMask|FocusChangeMask);
    XDeleteProperty(dpy, root, NET_CLIENT_LIST);
    XDeleteProperty(dpy, root, NET_ACTIVE_WINDOW);

    for(;;) InterceptEvents();
}
