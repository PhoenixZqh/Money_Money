#!/bin/bash

while true; do
      ffmpeg -framerate 30 -pattern_type glob -i '/home/zqh/Pictures/*.jpg' -c:v h264_nvenc -preset fast -pix_fmt yuv420p -b:v 3000k -minrate 3000k -maxrate 3000k -bufsize 6000k -g 50 -c:a aac -b:a 128k -f rtsp rtsp://10.88.105.194:8554/room1

  done

