#include <glib.h>
#include <gst/app/gstappsrc.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

gboolean need_data_callback(GstElement* appsrc, guint unused, gpointer user_data)
{
    VideoCapture* cap = static_cast<VideoCapture*>(user_data);
    Mat frame;
    if (cap->read(frame)) {
        GstBuffer* buffer;
        guint size;
        GstFlowReturn ret;
        GstMapInfo map;

        // Allocate buffer
        size = frame.cols * frame.rows * frame.channels();
        buffer = gst_buffer_new_allocate(NULL, size, NULL);
        gst_buffer_map(buffer, &map, GST_MAP_WRITE);
        memcpy(map.data, frame.data, size);
        gst_buffer_unmap(buffer, &map);

        // Push buffer to appsrc
        g_signal_emit_by_name(appsrc, "push-buffer", buffer, &ret);
        gst_buffer_unref(buffer);

        if (ret != GST_FLOW_OK) {
            g_print("Pushing buffer failed!\n");
            return FALSE;
        }
    } else {
        g_print("Failed to read frame from VideoCapture!\n");
        return FALSE;
    }
    return TRUE;
}

int main(int argc, char** argv)
{
    gst_init(&argc, &argv);
    GMainLoop* loop = g_main_loop_new(NULL, FALSE);

    // Initialize RTSP server
    GstRTSPServer* server = gst_rtsp_server_new();
    gst_rtsp_server_set_service(server, "8554"); // RTSP server port

    GstRTSPMountPoints* mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory* factory = gst_rtsp_media_factory_new();

    // Set up video capture
    // VideoCapture cap("rtsp://your_rtsp_stream_url");
    VideoCapture cap("/home/zqh/test.mp4");

    if (!cap.isOpened()) {
        cout << "Failed to open RTSP stream!" << endl;
        return -1;
    }

    factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory,
        "( appsrc name=mysrc ! videoconvert ! video/x-raw,format=I420 ! x264enc ! rtph264pay name=pay0 pt=96 )");

    // Configure appsrc caps
    GstElement* appsrc = gst_bin_get_by_name_recurse_up(GST_BIN(factory), "mysrc");
    GstCaps* caps = gst_caps_new_simple("video/x-raw",
        "format", G_TYPE_STRING, "I420",
        "width", G_TYPE_INT, 640,
        "height", G_TYPE_INT, 480,
        "framerate", GST_TYPE_FRACTION, 30, 1,
        NULL);
    gst_app_src_set_caps(GST_APP_SRC(appsrc), caps);

    // Set appsrc callbacks
    g_signal_connect(appsrc, "need-data", G_CALLBACK(need_data_callback), &cap);
    gst_object_unref(appsrc);

    // Mount RTSP media factory
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);
    g_object_unref(mounts);

    // Attach server to main context
    gst_rtsp_server_attach(server, NULL);

    cout << "RTSP server ready at rtsp://127.0.0.1:8554/test" << endl;
    g_main_loop_run(loop);

    // Clean up
    g_main_loop_unref(loop);
    gst_element_set_state(GST_ELEMENT(server), GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(server));

    return 0;
}
