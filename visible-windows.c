/* XeleTools by Henrique Gogó <henriquegogo@gmail.com>, 2021.
 * MIT License */

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    Display *dpy = XOpenDisplay(NULL);
    Window root, win, *wins;
    unsigned int nwins;

    XSelectInput(dpy, root = XDefaultRootWindow(dpy), SubstructureNotifyMask);
    XQueryTree(dpy, XDefaultRootWindow(dpy), &win, &win, &wins, &nwins);

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

            char *passed_name = malloc(1024 * sizeof(char));
            for (int arg_i = 1; arg_i < argc; arg_i++) {
                strcat(passed_name, argv[arg_i]);
                strcat(passed_name, " ");
            }

            if (argc > 1 && !strncmp(passed_name, value, text.nitems)) {
                XRaiseWindow(dpy, win);
                XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
            }

            free(passed_name);
        }
    }

    XFree(wins);
    XCloseDisplay(dpy);

    return 0;
}
