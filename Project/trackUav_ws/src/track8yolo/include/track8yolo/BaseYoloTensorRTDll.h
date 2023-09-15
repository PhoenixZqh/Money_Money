#ifndef __YOLOV5_TENSORRT_H
#define __YOLOV5_TENSORRT_H

#include "DefGlobalVar.h"
#include "opencv2/opencv.hpp"
#include <vector>

class CYoloV5TensorRTClass
{
public:
	CYoloV5TensorRTClass();
	virtual ~CYoloV5TensorRTClass();

	// 初始化算法
	virtual int InitAlgoriParam(StruInitParams &param);

	// 算法检测跟踪
	virtual int MainProcFunc(cv::Mat matClrImg, std::vector<StruDetectInfo> &vecFeed);


private:
	CYoloV5TensorRTClass *m_pTreat;
};

#endif // #ifndef __DETECTOR_H
