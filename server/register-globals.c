#include <stdio.h>
#include <wayland-server.h>

struct my_state {
    struct wl_list client_outputs;
};
struct my_output {
    struct wl_resource resource;
    struct my_state state;
};

static void wl_output_handle_resource_destroy (struct wl_resource *resource) {
    struct my_output *client_output = wl_resource_get_user_data (resource);

    // TODO: Clean up resource
    //remove_to_list (client_output->state->client_outputs, client_output);
}

static void wl_output_handle_release (
    struct wl_client *client,
    struct wl_resource *resource
) {
    wl_resource_destroy (resource);
}

static const struct wl_output_interface wl_output_implementation = {
    .release = wl_output_handle_release
};

static void wl_output_handle_bind (
    struct wl_client *client,
    void *data,
    uint32_t version,
    uint32_t id
) {
    struct my_state *state = data;

    struct my_output *client_output = calloc (1, sizeof (struct client_output));

    struct wl_resource *resource = wl_resource_create (
        client,
        &wl_output_implementation,
        wl_output_interface.version,
        id
    );

    wl_resource_set_implementation (
        resource,
        &wl_output_implementation,
        client_output,
        wl_output_handle_resource_destroy
    );

    client_output->resource = resource;
    client_output->state = state;

    wl_output_send_geometry (
        resource,
        0,
        0,
        1920,
        1080,
        WL_OUTPUT_SUBPIXEL_UNKNOWN,
        "Foobar, Inc",
        "Fany Monitor 9001 4K HD 120 FPS Noscope",
        WL_OUTPUT_TRANSFORM_NORMAL
    );

    add_to_list (state->client_outputs, client_output);
}

int main (int argc, char *argv[]) {
    struct wl_display *display = wl_display_create ();
    struct my_state state = { ... };
    // ...
    wl_global_create (wl_display, &wl_output_interface, 1, &state, wl_output_handle_bind);
    // ...
}