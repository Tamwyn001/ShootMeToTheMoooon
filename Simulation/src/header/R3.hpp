struct R3 {
    double x, y, z;

    R3 (double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    R3 operator+ (const R3& other) const {
        return R3(this->x + other.x, this->y + other.y, this->z + other.z);
    };
    R3 operator- (const R3& other) const {
        return R3(this->x - other.x, this->y - other.y, this->z - other.z);
    };
    R3 operator* (const R3& other) const {
        return R3(this->x * other.x, this->y * other.y, this->z * other.z);
    };

    R3 operator* (const double& other) const {
        return R3(this->x * other, this->y * other, this->z * other);
    };
    R3 operator/ (const double& other) const {
        return R3(this->x / other, this->y / other, this->z / other);
    };

    R3 operator+= (const R3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    };
};

double scpr (R3 a, R3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
};

R3 vcpr (R3 a, R3 b) {
    return R3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
};

double pnorm (int p, R3 a) {
    return pow(pow(a.x, p) + pow(a.y, p) + pow(a.z, p), 1.0 / p);
};