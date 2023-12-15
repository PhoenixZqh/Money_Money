#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream> // Make sure this line is included

using namespace std;
int main(int argc, char **argv)
{
    string dir = "/home/data-jinshan/pic_no3/";    // 标定图片所在文件夹
    ofstream fout(dir + "calibration_result.txt"); // 输出结果保存在此文本文件下
    // 依次读取每一幅图片，从中提取角点
    cout << "开始提取角点……" << endl;
    int image_nums = 0;     // 图片数量
    cv::Size image_size;    // 图片尺寸
    int points_per_row = 6; // 每行的内点数
    int points_per_col = 6; // 每列的内点数
    cv::Size corner_size = cv::Size(
        points_per_row, points_per_col);  // 标定板每行每列角点个数，共10*7个角点
    vector<cv::Point2f> points_per_image; // 缓存每幅图检测到的角点
    vector<vector<cv::Point2f>>
        points_all_images;  // 用一个二维数组保存检测到的所有角点
    string image_file_name; // 声明一个文件名的字符串

    int index = 0;

    while (1) // 逐行读取，将行读入字符串
    {
        ++index;

        // 读入图片
        std::string path = dir + std::to_string(index) + ".png";
        std::cout << path << std::endl;
        cv::Mat image_raw = cv::imread(path);
        if (image_raw.empty()) break;
        image_nums++;
        if (image_nums == 1)
        {
            // cout<<"channels = "<<image_raw.channels()<<endl;
            // cout<<image_raw.type()<<endl;  //CV_8UC3
            image_size.width = image_raw.cols;  // 图像的宽对应着列数
            image_size.height = image_raw.rows; // 图像的高对应着行数
            cout << "image_size.width = " << image_size.width << endl;
            cout << "image_size.height = " << image_size.height << endl;
        }
        // 角点检测
        cv::Mat image_gray; // 存储灰度图的矩阵
        cv::cvtColor(image_raw, image_gray,
                     cv::COLOR_BGR2GRAY); // 将BGR图转化为灰度图
        // cout<<"image_gray.type() = "<<image_gray.type()<<endl;  //CV_8UC1
        // step1 提取角点
        bool success = cv::findChessboardCorners(image_gray, corner_size, points_per_image);
        // bool success = cv::findChessboardCorners(image_gray, corner_size, points_per_image, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);

        if (!success)
        {
            cout << "can not find the corners " << endl;
            // exit(1);
        }
        else
        {
            // 亚像素精确化（两种方法）
            // step2 亚像素角点
            cv::find4QuadCornerSubpix(image_gray, points_per_image, cv::Size(5, 5));
            // cornerSubPix(image_gray,points_per_image,Size(5,5));
            points_all_images.push_back(points_per_image); // 保存亚像素角点
            // 在图中画出角点位置
            // step3 角点可视化
            cv::drawChessboardCorners(image_raw, corner_size, points_per_image,
                                      success); // 将角点连线
            cv::imshow("Camera calibration", image_raw);
            cv::waitKey(0); // 等待按键输入
        }
    }
    cv::destroyAllWindows();
    // 输出图像数目
    int image_sum_nums = points_all_images.size();
    cout << "image_sum_nums = " << image_sum_nums << endl;

    // 开始相机标定
    cv::Size block_size(50, 50);                            // 每个小方格实际大小, 只会影响最后求解的平移向量t
    cv::Mat camera_K(3, 3, CV_32FC1, cv::Scalar::all(0));   // 内参矩阵3*3
    cv::Mat distCoeffs(1, 5, CV_32FC1, cv::Scalar::all(0)); // 畸变矩阵1*5
    vector<cv::Mat> rotationMat;                            // 旋转矩阵
    vector<cv::Mat> translationMat;                         // 平移矩阵
    // 初始化角点三维坐标,从左到右,从上到下!!!
    vector<cv::Point3f> points3D_per_image;
    for (int i = 0; i < corner_size.height; i++)
    {
        for (int j = 0; j < corner_size.width; j++)
        {
            points3D_per_image.push_back(
                cv::Point3f(block_size.width * j, block_size.height * i, 0));
        }
    }
    vector<vector<cv::Point3f>> points3D_all_images(
        image_nums, points3D_per_image); // 保存所有图像角点的三维坐标, z=0

    int point_counts = corner_size.area(); // 每张图片上角点个数
    //! 标定
    /**
   * points3D_all_images: 真实三维坐标
   * points_all_images: 提取的角点
   * image_size: 图像尺寸
   * camera_K : 内参矩阵K
   * distCoeffs: 畸变参数
   * rotationMat: 每个图片的旋转向量
   * translationMat: 每个图片的平移向量
   * */
    // step4 标定
    cv::calibrateCamera(points3D_all_images, points_all_images, image_size, camera_K, distCoeffs, rotationMat, translationMat, 0);

    // step5 对标定结果进行评价
    double total_err = 0.0;               // 所有图像平均误差总和
    double err = 0.0;                     // 每幅图像的平均误差
    vector<cv::Point2f> points_reproject; // 重投影点
    cout << "\n\t每幅图像的标定误差:\n";
    fout << "每幅图像的标定误差：\n";
    for (int i = 0; i < image_nums; i++)
    {
        vector<cv::Point3f> points3D_per_image = points3D_all_images[i];
        // 通过之前标定得到的相机内外参，对三维点进行重投影
        cv::projectPoints(points3D_per_image, rotationMat[i], translationMat[i], camera_K, distCoeffs, points_reproject);
        // 计算两者之间的误差
        vector<cv::Point2f> detect_points =
            points_all_images[i]; // 提取到的图像角点
        cv::Mat detect_points_Mat =
            cv::Mat(1, detect_points.size(),
                    CV_32FC2); // 变为1*70的矩阵,2通道保存提取角点的像素坐标
        cv::Mat points_reproject_Mat = cv::Mat(
            1, points_reproject.size(), CV_32FC2); // 2通道保存投影角点的像素坐标
        for (int j = 0; j < detect_points.size(); j++)
        {
            detect_points_Mat.at<cv::Vec2f>(0, j) =
                cv::Vec2f(detect_points[j].x, detect_points[j].y);
            points_reproject_Mat.at<cv::Vec2f>(0, j) =
                cv::Vec2f(points_reproject[j].x, points_reproject[j].y);
        }
        err = cv::norm(points_reproject_Mat, detect_points_Mat, cv::NormTypes::NORM_L2);
        total_err += err /= point_counts;
        cout << "第" << i + 1 << "幅图像的平均误差为： " << err << "像素" << endl;
        fout << "第" << i + 1 << "幅图像的平均误差为： " << err << "像素" << endl;
    }
    cout << "总体平均误差为： " << total_err / image_nums << "像素" << endl;
    fout << "总体平均误差为： " << total_err / image_nums << "像素" << endl;
    cout << "评价完成！" << endl;

    // 将标定结果写入txt文件
    cv::Mat rotate_Mat =
        cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0)); // 保存旋转矩阵
    cout << "\n相机内参数矩阵:" << endl;
    cout << camera_K << endl
         << endl;
    fout << "\n相机内参数矩阵:" << endl;
    fout << camera_K << endl
         << endl;
    cout << "畸变系数：\n";
    cout << distCoeffs << endl
         << endl
         << endl;
    fout << "畸变系数：\n";
    fout << distCoeffs << endl
         << endl
         << endl;
    for (int i = 0; i < image_nums; i++)
    {
        cv::Rodrigues(rotationMat[i],
                      rotate_Mat); // 将旋转向量通过罗德里格斯公式转换为旋转矩阵
        fout << "第" << i + 1 << "幅图像的旋转矩阵为：" << endl;
        fout << rotate_Mat << endl;
        fout << "第" << i + 1 << "幅图像的平移向量为：" << endl;
        fout << translationMat[i] << endl
             << endl;
    }
    fout << endl;
    fout.close();

    return 0;
}
