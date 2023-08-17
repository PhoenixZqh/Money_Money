#!/usr/bin/env python3

import cv2
import gi

gi.require_version('Gst', '1.0')
gi.require_version('GstRtspServer', '1.0')
from gi.repository import Gst, GstRtspServer, GObject


class SensorFactory(GstRtspServer.RTSPMediaFactory):
    def __init__(self, **properties):
        super(SensorFactory, self).__init__(**properties)
        self.cap = cv2.VideoCapture("rtsp://admin:kuangping108@192.168.1.64/h264/ch1/main/av_stream")
        self.number_frames = 0
        self.fps = 1
        self.duration = 1 / self.fps * Gst.SECOND  # duration of a frame in nanoseconds
        self.launch_string = 'appsrc name=source is-live=true block=true format=GST_FORMAT_TIME ' \
                             'caps=video/x-raw,format=BGR,width=960,height=540,framerate={}/1 ' \
                             '! videoconvert ! video/x-raw,format=I420 ' \
                             '! x264enc speed-preset=ultrafast tune=zerolatency ' \
                             '! rtph264pay config-interval=1 name=pay0 pt=96'.format(self.fps)

    def on_need_data(self, src, lenght):#3840/4 2160/4
        if self.cap.isOpened():
            ret, frame = self.cap.read()
            if ret:
                if self.number_frames % 25 == 0:
                    # 缩放到原来的四分之一
                    frame  = cv2.resize(frame, (960,540),interpolation=cv2.INTER_AREA)
                    data = frame.tostring()
                
                else:
                    data=''

                buf = Gst.Buffer.new_allocate(None, len(data), None)
                buf.fill(0, data)
                self.duration = 1 / 25 * Gst.SECOND
                buf.duration = self.duration
                timestamp = self.number_frames * self.duration
                buf.pts = buf.dts = int(timestamp)
                buf.offset = timestamp
                self.number_frames += 1
                retval = src.emit('push-buffer', buf)
                if (self.number_frames-1) % 25 == 0:
                    print('pushed buffer, frame {}, duration {} ns, durations {} s'.format(self.number_frames,
                                                                                           self.duration,
                                                                                           self.duration / Gst.SECOND))
                if retval != Gst.FlowReturn.OK:
                    print(retval)

    def do_create_element(self, url):
        return Gst.parse_launch(self.launch_string)

    def do_configure(self, rtsp_media):
        self.number_frames = 0
        appsrc = rtsp_media.get_element().get_child_by_name('source')
        appsrc.connect('need-data', self.on_need_data)


class GstServer(GstRtspServer.RTSPServer):
    def __init__(self, **properties):
        super(GstServer, self).__init__(**properties)
        self.factory = SensorFactory()
        self.factory.set_shared(True)
        self.get_mount_points().add_factory("/test", self.factory)
        self.attach(None)


GObject.threads_init()
Gst.init(None)

server = GstServer()
print("Running as - rtsp://127.0.0.1:8554/test")

loop = GObject.MainLoop()
loop.run()
