import rosbag
from cv_bridge import CvBridge
import cv2
import os
 
# 初始化cv_bridge
bridge = CvBridge()
 
# 指定ROS bag文件路径
bag_file = '/home/test_2023-04-17-17-12-46.bag'
 
# 指定用于保存图像的文件夹
image_folder = '/home/nhy_imgs'
if not os.path.exists(image_folder):
    os.makedirs(image_folder)
 
# 打开ROS bag文件
with rosbag.Bag(bag_file, 'r') as bag:
    for topic, msg, t in bag.read_messages():
        # 假设我们关注的图像话题是'/camera/image_raw'
        if topic == '/nhy/gimbal_camera':
            # 使用cv_bridge将图像从ROS格式转换为OpenCV格式
            image = bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            
            # 保存图像
            image_name = os.path.join(image_folder, f"image_{len(os.listdir(image_folder))}.jpg")
            cv2.imwrite(image_name, image)
            print(f"Image saved: {image_name}")