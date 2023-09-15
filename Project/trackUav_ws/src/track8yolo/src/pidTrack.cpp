/***************************************************************************************************************************
* pidTrack.h
*
* Author:  Niwh
*
* Update Time: 2021.11.24
*
* Introduction:  单个方向的跟踪pid控制程序
*
*pid实现的cpp
***************************************************************************************************************************/
#include "pidTrack.h"

namespace pidTrack
{

    PidTrack::PidTrack(double kp, double kd, double ki) : kp_(kp), kd_(kd), ki_(ki)
    {
        gettimeofday(&t_last_, NULL);
        gettimeofday(&t_now_, NULL);
        memset(err_acmu_, 0, 10);
        count_err_acmu_ = 0;
        p_ori_ = 0.0;
    }

    PidTrack::~PidTrack(){;}

    void PidTrack::setPosOri(double pos)
    {
        p_ori_ = pos;
        p_last_ = pos;
        memset(err_acmu_, 0, 10);
        count_err_acmu_ = 0;
        gettimeofday(&t_last_, NULL);
        
    }

    double PidTrack::runPosTrack(double posNow)
    {
        gettimeofday(&t_now_, NULL);
        double Pd = (posNow - p_last_) / double(t_now_.tv_sec + t_now_.tv_usec * pow(10, -6) - (t_last_.tv_sec + t_last_.tv_usec * pow(10, -6)));
        t_last_ = t_now_;
        p_last_ = posNow;
        double Pp = posNow - p_ori_;
        if (count_err_acmu_ == 10)
            count_err_acmu_ = 0;
        err_acmu_[count_err_acmu_] = posNow - p_ori_;
        count_err_acmu_++;
        double Pi = std::accumulate(err_acmu_, err_acmu_ + 10, 0);
        return ki_ * Pi + kd_ * Pd + kp_ * Pp;
    }
}
