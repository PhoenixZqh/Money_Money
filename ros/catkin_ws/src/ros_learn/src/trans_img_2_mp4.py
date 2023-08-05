import cv2
import os


def images_to_video(input_folder, output_video):
    image_files = [
        f for f in os.listdir(input_folder)
        if os.path.isfile(os.path.join(input_folder, f))
    ]
    image_files.sort()  # 确保图像按照排序顺序转换为视频

    frame_width, frame_height = 0, 0
    video_writer = None

    for image_file in image_files:
        image_path = os.path.join(input_folder, image_file)
        image = cv2.imread(image_path)

        if frame_width == 0 or frame_height == 0:
            frame_height, frame_width = image.shape[:2]
            video_writer = cv2.VideoWriter(output_video,
                                           cv2.VideoWriter_fourcc(*'mp4v'), 10,
                                           (frame_width, frame_height))

        video_writer.write(image)

    video_writer.release()


# 调用函数进行转换
input_folder = '/home/zqh/DATA/pic/'
output_video = '/home/zqh/DATA/gps.mp4'
images_to_video(input_folder, output_video)
