#include <gst/gst.h>

int main(int argc, char* argv[])
{
    // Initialize GStreamer
    gst_init(&argc, &argv);

    // Create a GStreamer element factory for the nvh264dec plugin
    GstElementFactory* factory = gst_element_factory_find("nvh264dec");

    if (factory) {
        g_print("Plugin 'nvh264dec' is available.\n");
        gst_object_unref(factory);
    } else {
        g_print("Plugin 'nvh264dec' is NOT available.\n");
    }

    // Cleanup GStreamer
    gst_deinit();

    return 0;
}
