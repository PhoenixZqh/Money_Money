#include <iostream>
#include <cmath>

using namespace std;

#define M_PI 3.1415926

float CalculateBearing(const float &lat1, const float &lon1, const float &lat2, const float &lon2)
{
    float phi1 = lat1 * M_PI / 180.0;
    float phi2 = lat2 * M_PI / 180.0;
    float deltaLambda = (lon2 - lon1) * M_PI / 180.0;

    float y = sin(deltaLambda) * cos(phi2);
    float x = cos(phi1) * sin(phi2) - sin(phi1) * cos(phi2) * cos(deltaLambda);
    float theta = atan2(y, x);

    float bearingEast = fmod((90.0 - theta * 180.0 / M_PI + 360.0), 360.0);
    float rad_brearing = bearingEast * M_PI / 180.f;
    return rad_brearing;
    // if (theta < 0)
    // {
    //     theta += 2 * M_PI;
    // }

    return rad_brearing;
}

int main()
{
    float theta = CalculateBearing(33.942565, 113.902320, 33.94259918, 113.90066744);
    cout << theta << endl;

    return 0;
}