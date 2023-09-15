#pragma once


// 错误码
#define ALG_ERR_NONE 0						// 无错误
#define ALG_ERR_BASE 0X10000				// 标志位 65536
#define ALG_ERR_MAT ALG_ERR_BASE + 1		// 无效的图像数据 65537
#define ALG_ERR_INIT ALG_ERR_BASE + 2		// 主算法初始化接口失败: Init 65538
#define ALG_ERR_NONE_POINT ALG_ERR_BASE + 3 // 未执行初始化函数InitSetup
#define ALG_VIDEO_STOP ALG_ERR_BASE + 4		// 视频停止处理

typedef struct _StruInitParams
{
	int gpu_id;			   // 启用gpu id:0 默认当前第一块gpu,1为第二块gpu
	int net_width; 
	int net_height;
	float confThreshold; // 检测阈值  值越小越灵敏，越大误捡率越少
	float nmsThreshold;
	char *weightFile;	   // 训练的检测模型weights格式文件，存储权重信息
	_StruInitParams()
	{
		gpu_id = 0;
		net_width = 640;
		net_height = 640;
		confThreshold = 0.5;
		nmsThreshold = 0.4;
		weightFile = nullptr;
	}
} StruInitParams;

typedef struct _StruDetectInfo // 检测目标
{
	int x;
	int y;
	int width;
	int height;
	int label;
	float confidance;
	_StruDetectInfo()
	{
		x = y = width = height = label = 0;
		confidance = 0.f;
	}
	_StruDetectInfo(int x, int y, int w, int h, int l, float c)
	{
		x = x;
		y = y;
		width = w;
		height = h;
		label = l;
		confidance = c;
	}
} StruDetectInfo;
