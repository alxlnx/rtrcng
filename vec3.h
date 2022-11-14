#pragma once
#include <iostream>
#include <cmath>

class vec3 {
    public:
    vec3() : e{0, 0, 0} 
    {
        // default const.
    }
    vec3(const double& e1, const double& e2, const double& e3) : e{ e1, e2, e3 } 
    {
        // via 3 values
    }

    vec3 operator-() 
    // No vec3& since we don't always want to modify the vector.
    // We also don't need const version since we always return a copy.
    {
        return vec3( -e[0], -e[1], -e[2] );
    }
    double& operator[](int i) {
        // Yeah, yeah, [] usually doesn't do range checking, that's what at() is for.
        // But I really want to save time debugging that thing. 
        if (i < 0 or i > 2) std::cerr << "vec3 operator[] : index " << i << " is out of bounds!\n";
        return e[i]; 
    }
    const double& operator[](int i) const {
        if (i < 0 or i > 2) std::cerr << "vec3 operator[] : index " << i << " is out of bounds!\n";
        return e[i];
    }

    vec3& operator+=(const vec3& arg) 
    {
        e[0] += arg[0];
        e[1] += arg[1];
        e[2] += arg[2];

        return *this;
    }

    vec3& operator-=(const vec3& arg) 
    {
        e[0] -= arg[0];
        e[1] -= arg[1];
        e[2] -= arg[2];

        return *this;
    }

    vec3& operator*=(const double& t) 
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    vec3& operator/=(const double& t) 
    {
        return *this *= (1 / t);
    }

    double length_squared() const 
    // Assuming vec3 is used solely in Cartesian coordinate system.
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    double length() const {
        return sqrt(length_squared());
    }

    private:
        double e[3]{};
};

// Some aliases, possibly evil.
using point3 = vec3;
using color  = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}