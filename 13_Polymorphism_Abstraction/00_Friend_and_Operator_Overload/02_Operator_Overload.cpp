/**************************************************************
 * Nạp chồng toán tử (Operator Overloading)
 **************************************************************
 * - Cho phép định nghĩa lại cách hoạt động của toán tử với class tự định nghĩa.
 * - Toán tử có thể nạp chồng: +, -, *, /, ==, !=, <, >, <<, [], (), v.v.
 * - Không thể nạp chồng: ::, ., .*, ?:, sizeof, typeid
 * - Hai kiểu nạp chồng:
 *  - Dùng member function (thường cho toán tử gán, toán tử 1 ngôi).
 *  - Dùng non-member (friend) cho toán tử 2 ngôi, toán tử <<, >>.
 * - Lưu ý:
 *  - Nên giữ đúng ý nghĩa bản chất của toán tử.
 *  - Nếu cần phép gán = thì nên bổ sung copy assignment operator.
 * * Quiz:
 * 1. Toán tử nào không thể nạp chồng?
 * 2. So sánh operator overload dạng member và non-member.
 **************************************************************/

#if 1
#include <iostream>
#include <cmath>

class Vector3D {
    double x, y, z;

public:
    Vector3D(double x=0, double y=0, double z=0)
        : x(x), y(y), z(z) {}

    // MEMBER: +=
    Vector3D& operator+=(const Vector3D& v) {
        std::cout << "NHay vao ham nap chong toan tu += \n";
        x += 2*v.x;
        y += 2*v.y;
        z += 2*v.z;
        return *this;
    }

    // MEMBER: unary -
    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }

    // NON-MEMBER: +
    friend Vector3D operator+(const Vector3D& a, const Vector3D& b) {
        std::cout << "Nhay vao hàm nap chồng toán tử + friend \n";
        return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    // NON-MEMBER: ==
    friend bool operator==(const Vector3D& a, const Vector3D& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    // NON-MEMBER: <<
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return os;
    }
};

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);

    // Test operator+
    Vector3D v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;

    // Test operator+=
    v1 += v2;
    std::cout << "v1 sau khi += v2 = " << v1 << std::endl;

    // Test unary operator -
    Vector3D v4 = -v1;
    std::cout << "-v1 = " << v4 << std::endl;

    // Test operator==
    if (v1 == v3) {
        std::cout << "v1 == v3" << std::endl;
    } else {
        std::cout << "v1 != v3" << std::endl;
    }

    return 0;
}

#endif

