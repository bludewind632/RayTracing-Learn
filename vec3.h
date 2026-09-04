#ifndef VEC3_H
#define VEC3_H

constexpr double EPS = 1e-160;

class vec3
{
public:
    vec3() : vc{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : vc{e0, e1,e2} {}

    double& x() { return vc[0]; }
    double& y() { return vc[1]; }
    double& z() { return vc[2]; }
    const double& x() const { return vc[0]; }
    const double& y() const { return vc[1]; }
    const double& z() const { return vc[2]; }

    double& operator[] (int i) { return vc[i]; }
    const double& operator[] (int i) const { return vc[i]; }
    
    vec3 operator- () const { return vec3(-vc[0], -vc[1], -vc[2]); }

    vec3& operator+= (const vec3& other) {
        for (int i = 0; i < 3; i++)
            vc[i] += other[i];
        return *this;
    }

    vec3& operator-= (const vec3& other) {
        for (int i = 0; i < 3; i++)
            vc[i] -= other[i];
        return *this;
    }

    vec3& operator*= (double t) {
        for (int i = 0; i < 3; i++) 
            vc[i] *= t;
        return *this;
    }

    vec3& operator/= (double t) {
        for (int i = 0; i < 3; i++) 
            vc[i] /= t;
        return *this;
    }

    double length() const {
        return std::sqrt(length_square());
    }

    double length_square() const {
        return vc[0] * vc[0] + vc[1] * vc[1] + vc[2] * vc[2];
    }

    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }
    static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const {
        auto eps = 1e-8;
        return (std::fabs(vc[0]) < eps) && (std::fabs(vc[1]) < eps) && (std::fabs(vc[2]) < eps);
    }

    friend vec3 operator+ (const vec3& a, const vec3& b);
    friend vec3 operator- (const vec3& a, const vec3& b);
    friend vec3 operator* (const vec3& a, const vec3& b);
    friend vec3 operator* (const vec3& a, double t);
    friend vec3 operator* (double t, const vec3& a);
    friend vec3 operator/ (const vec3& a, double t);
    
    friend vec3 unit_vector(const vec3& a);
    friend vec3 random_unit_vector();
    friend vec3 random_on_hemisphere(const vec3& normal);
    friend double dot(const vec3& a, const vec3& b);
    friend vec3 cross(const vec3& a, const vec3& b);
    friend vec3 reflect(const vec3& r_in, const vec3& n);
    friend vec3 refract(const vec3& r_in, const vec3& n, double etai_over_etat);
private:
    double vc[3];
};

vec3 operator+ (const vec3& a, const vec3& b) {
    return vec3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}
vec3 operator- (const vec3& a, const vec3& b) {
    return vec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}
vec3 operator* (const vec3& a, const vec3& b) {
    return vec3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
}
vec3 operator* (const vec3& a, double t) {
    return vec3(a.x() * t, a.y() * t, a.z() * t);
}
vec3 operator* (double t, const vec3& a) {
    return vec3(a.x() * t, a.y() * t, a.z() * t);
}
vec3 operator/ (const vec3& a, double t) {
    return a * (1 / t);
}

vec3 unit_vector(const vec3& a) {
    return a / a.length();;
}

vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        double len_sq = p.length_square();
        if (len_sq > EPS && len_sq <= 1) {
            return p / sqrt(len_sq);
        }
    }
}

vec3 random_on_hemisphere(const vec3& normal) {
    auto on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    }
    else return -on_unit_sphere;
}

double dot(const vec3& a, const vec3& b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}
vec3 cross(const vec3& a, const vec3& b) {
    double e0 = a.y() * b.z() - b.y() * a.z();
    double e1 = b.x() * a.z() - a.x() * b.z();
    double e2 = a.x() * b.y() - b.x() * a.y();
    return vec3(e0, e1, e2);
}

// get the mirror reflect ray
vec3 reflect(const vec3& r_in, const vec3& n) {
    return r_in + 2 * (-dot(r_in, n)) * n;
}

vec3 refract(const vec3& r_in, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-r_in, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (r_in + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(fabs(1.0 - r_out_perp.length_square())) * n;
    return r_out_perp + r_out_parallel;
}

using point3 = vec3;

#endif // VEC3_H