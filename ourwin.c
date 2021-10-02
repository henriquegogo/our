/* OUR by Henrique Gogó <henriquegogo@gmail.com>, 2021.
 * MIT License */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    Display *dpy = XOpenDisplay(NULL);
    Window root, win, *wins;
    unsigned int nwins;

    XSelectInput(dpy, root = XDefaultRootWindow(dpy), SubstructureNotifyMask);
    XQueryTree(dpy, XDefaultRootWindow(dpy), &win, &win, &wins, &nwins);

    char *win_name = malloc(1024 * sizeof(char));
    if (!isatty(fileno(stdin))) {
        fgets(win_name, 1024 * sizeof(char), stdin);
    }
 
    for (int i = nwins - 1; i > 0; i--) {
        Window win = wins[i];
        XWindowAttributes wattr;
        XGetWindowAttributes(dpy, win, &wattr);

        if (!wattr.override_redirect && wattr.map_state == IsViewable) {
            char value[1024];
            XTextProperty text;
            XGetWMName(dpy, win, &text);
            sprintf(value, "%s", text.value);
            printf("%s\n", value);

            if (!strncmp(win_name, value, text.nitems)) {
                printf("%s : %s", win_name, value);
                XRaiseWindow(dpy, win);
                XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
            }
        }
    }
    
    free(win_name);
    XFree(wins);
    XCloseDisplay(dpy);

    return 0;
}
