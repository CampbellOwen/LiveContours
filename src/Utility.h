#pragma once
#include <cmath>

class Utility {
    public:
        static double reverseInterpolate(double start, double end, double t)
        {
            if ((end-start) == 0) return 0;
            return std::abs((t - start) / (end - start));
        }

        static double interpolate(double start, double end, double t)
        {
            return start + ((end - start) * t);
        }

        static double centerValue(double tl, double tr, double br, double bl)
        {
            double tm = interpolate(tl, tr, 0.5);
            double bm = interpolate(bl, br, 0.5);
            return interpolate(bm, tm, 0.5);
        }
};

template <typename T>
struct vec2 {
    T x;
    T y;
};