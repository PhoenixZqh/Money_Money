/***************************************************************************************************************************
* pidTrack.h
*
* Author:  Niwh
*
* Update Time: 2021.11.24
*
* Introduction:  单个方向的跟踪pid控制程序
***************************************************************************************************************************/

#ifndef _PIDTRACK_H_
#define _PIDTRACK_H_
#include <numeric>
#include <sys/time.h>
#include <string.h>
#include <math.h>
namespace pidTrack
{
    class PidTrack
    {
    public:
        PidTrack(double kp = 1.0, double kd = 0.0, double ki = 0.0);
        ~PidTrack();
        void setPosOri(double pos);
        double runPosTrack(double posNow);

        //方便更换
        double kp_;
        double kd_;
        double ki_;

    private:
        double p_ori_;
        double p_last_;
        double err_acmu_[10];
        int count_err_acmu_;
        timeval t_now_, t_last_;
    };
}

#endif