import cv2
import os


def video_to_frames(video_path, output_folder):
    # 创建输出文件夹
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 打开视频文件
    cap = cv2.VideoCapture(video_path)

    frame_count = 0

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        # 构造输出文件名
        output_file = os.path.join(output_folder,
                                   f"frame_{frame_count:04d}.jpg")

        # 保存当前帧为图片
        cv2.imwrite(output_file, frame)

        frame_count += 1

    cap.release()
    cv2.destroyAllWindows()


# 输入视频文件路径和输出文件夹路径
input_video_path = "/home/zqh/Downloads/homezqh/home.mp4"
output_folder_path = "/home/zqh/Downloads/homezqh"

video_to_frames(input_video_path, output_folder_path)
print("转换完成！")
