#include <stdio.h>
#include <wayland-server.h>

int main (int argc, char *argv[]) {
    struct wl_display *display = wl_display_create ();
    if (!display) {
        fprintf (stderr, "Unable to create Wayland display.\n");
        return 1;
    }

    /**
    Using `wl_display_add_socket_auto` will allow libwayland to decide
    the name for the display automatically, which defaults to wayland-0,
    or wayland-$n, depending on if any other Wayland compositors have
    sockets in $XDG_RUNTIME_DIR.
    */
    const char *socket = wl_display_add_socket_auto (display);
    if (!socket) {
        fprintf (stderr, "Unabel to add socket to Wayland display.\n");
        return 1;
    }

    fprintf (stderr, "Running Wayland display on %s\n", socket);
    wl_display_run (display);

    wl_display_destroy (display);
    return 0;
}