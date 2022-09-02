#include <stdio.h>
#include <wayland-client.h>

int main (int argc, char *argv[]) {
    /**
    wl_display_connect is the most common way for clients to establish a Wayland connection. The signature is:

        struct wl_display *wl_display_connect(const char *name);

    The "name" argument is the name of the Wayland display, which is typically "wayland-0". You can swap the NULL for this in our test client and try for yourself — it's likely to work. This corresponds to the name of a Unix socket in $XDG_RUNTIME_DIR. NULL is preferred, however, in which case libwayland will:

    1. If $WAYLAND_DISPLAY is set, attempt to connect to $XDG_RUNTIME_DIR/$WAYLAND_DISPLAY
    2. Attempt to connect to $XDG_RUNTIME_DIR/wayland-0
    3.Fail :(
    */
    struct wl_display *display = wl_display_connect (NULL);
    if (!display) {
        fprintf (stderr, "Failed to connect to Wayland display.\n");
        return 1;
    }
    fprintf (stderr, "Connection established!\n");

    wl_display_disconnect (display);
    return 0;
}