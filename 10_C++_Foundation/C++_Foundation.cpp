/* Compile C files
   gcc -o <execution_file_name> <List_Of_C_Files> -I <Include_Path>
*/

/* Compile CPP files
   g++ -o <execution_file_name> <List_Of_CPP_Files> -I <Include_Path>
*/

/* stdio.h for C and iostream for C++
*/

#if 0

#include <iostream>

int main(void)
{
    int a;

    std::cout << "Mời bạn nhập 1 số nguyên bất kỳ: " << std::endl;
    std::cin >> a;
    std::cout << "Số bạn vừa nhập là: " << a << std::endl;
    return 0;
}   
#endif

/* Chuỗi (string)
1. Chuỗi trong C:
   - Bản chất: mảng các ký tự `char[]` kết thúc bằng ký tự null '\0'.
   - Không tự quản lý bộ nhớ.
   - Kích thước cố định tại thời điểm khai báo (hoặc phải malloc/realloc).
   - Các hàm thao tác chuỗi (strcpy, strcat, strlen, ...) không an toàn
     nếu lập trình viên không tự kiểm soát boundary.

   -> Lỗi thường gặp:
      + Buffer overflow
      + Quên '\0'
      + Memory leak
      + Undefined behavior

2. Chuỗi trong C++ (std::string):
   - Bản chất: một class quản lý buffer char động bên trong.
   - Tự động cấp phát / giải phóng bộ nhớ.
   - Biết rõ kích thước chuỗi (size()).
   - Luôn đảm bảo chuỗi hợp lệ.
   - Nhiều hàm tiện ích: string đi kèm với nhiều hàm hữu ích như size(), length(), find(), substr(),...
          giúp thao tác với chuỗi dễ dàng hơn rất nhiều.
 */

#if 0
#include <stdio.h>
#include <string.h>
/*
 * Nối chuỗi trong C:
 * - Phải tự tính kích thước buffer
 * - Compiler sẽ không phát hiện được lỗi trường hợp kich thước không đủ
 * */
int main() {
    char a[20] = "Hello ";  
    char b[] = "World";

    // Lập trình viên phải đảm bảo a đủ lớn
    strcat(a, b);

    printf("Result: %s\n", a);
    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
/* Nối chuỗi trong C++:
 * - std::string tự quản lý bộ nhớ
 * - operator +
 * */
int main() {
    std::string a = "Hello ";
    std::string b = "World";

    a += b;

    std::cout << "Result: " << a << std::endl;
    return 0;
}
#endif

#if 0
/*
 * Copy và Replace trong C:
 *  - Phải đảm bảo dest đủ lớn
 *  - Replace dễ làm hỏng chuỗi
 *
 */

#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello World";
    char dest[20];

    // Copy
    strcpy(dest, src);

    // Replace 'World' -> 'C'
    char* pos = strstr(dest, "World");
    if (pos != NULL) {
        strcpy(pos, "C");
    }

    printf("Result: %s\n", dest);
    return 0;
}
#endif

#if 0
/*
 * Copy và Replace trong C++:
 * - Copy đơn giản bằng operator =
 *
 */

#include <iostream>
#include <string>

int main() {
    std::string src = "Hello World";

    // Copy
    std::string dest = src;

    // Replace
    dest.replace(dest.find("World"), 5, "C++");

    std::cout << "Result: " << dest << std::endl;
    return 0;
}

#endif

/* Tham chiếu (References)
    - Tham chiếu là một tên gọi khác (alias) cho một biến đã tồn tại. Một khi tham chiếu được khởi tạo, 
      nó không thể được gán lại để tham chiếu đến một biến khác.
    - So sánh với con trỏ:
        + An toàn hơn: Tham chiếu không thể là NULL (không trỏ tới gì cả), trong khi con trỏ có thể.
          Điều này giúp bạn tránh được các lỗi "dereferencing NULL pointer".
        + Cú pháp đơn giản hơn: Bạn sử dụng tham chiếu như một biến thông thường, không cần dùng các 
          toán tử * và & như khi làm việc với con trỏ.
    - Ứng dụng: Truyền tham số vào hàm bằng tham chiếu:
        + Đây là ứng dụng phổ biến nhất của tham chiếu. Khi bạn truyền một biến vào hàm bằng tham chiếu, 
          hàm sẽ làm việc trực tiếp trên biến gốc chứ không phải bản sao của nó. Điều này giúp thay đổi 
          giá trị của biến gốc từ bên trong hàm và cũng hiệu quả hơn về bộ nhớ khi truyền các đối tượng lớn.
*/

#if 0
#include <iostream>

// Truyền tham số bằng giá trị (tạo ra một bản sao)
void func_by_value(int x) {
    x = x + 10;
}

// Truyền tham số bằng tham chiếu (làm việc trên biến gốc)
void func_by_reference(int& x) {
    x = x + 10;
}

int main() {
    int a = 5;
    int b = 5;

    func_by_value(a);
    std::cout << "Gia tri cua 'a' sau khi truyen bang gia tri: " << a << std::endl; // Vẫn là 5

    func_by_reference(b);
    std::cout << "Gia tri cua 'b' sau khi truyen bang tham chieu: " << b << std::endl; // Là 15

    return 0;
}
#endif

/* Từ khóa auto (C++11):
    - auto không phải là kiểu dữ liệu. 
        -> Nó là placeholder để compiler suy luận kiểu tại compile-time
    - Từ khóa auto cho phép trình biên dịch tự động suy ra kiểu dữ liệu của biến dựa trên giá trị khởi tạo của nó.
      Điều này giúp mã nguồn ngắn gọn và dễ đọc hơn, đặc biệt khi làm việc với các kiểu dữ liệu phức tạp.
    - auto bắt buộc phải có giá trị khởi tạo
      Compiler suy luận kiểu từ biểu thức bên phải
    - Ví dụ:
        auto x = 10; // trình biên dịch hiểu x là int
        auto pi = 3.14; // trình biên dịch hiểu pi là double
        auto name = "Dev Linux"; // trình biên dịch hiểu name là const char*
*/

#if 1

#include <iostream>
#include <type_traits>

/*
 * Dùng static_assert và decltype để kiểm tra kiểu của 1 biên
 * Nêu sai kiểu thì biên dịch lỗi và text sẽ được hiển thị trong compile phase. 
 */
#define CHECK_TYPE(expr, type) \
    static_assert(std::is_same<decltype(expr), type>::value, "Type mismatch: " #expr)

#define CHECK_CONST(expr) \
    static_assert(std::is_const<std::remove_reference<decltype(expr)>::type>::value, "Not const")

#define CHECK_REF(expr) \
    static_assert(std::is_reference<decltype(expr)>::value, "Not reference")

int foo()
{
    return 100;
}

int main()
{
    std::cout << "===== LEVEL 1: BASIC TYPES =====" << std::endl;
    {
        auto a = 10;
        auto b = 3.14;
        auto c = 'c';

        CHECK_TYPE(a, int);
        CHECK_TYPE(b, double);
        CHECK_TYPE(c, char);
    }

    std::cout << "===== LEVEL 2: POINTER =====" << std::endl;
    {
        int x = 10;
        auto p = &x;

        CHECK_TYPE(p, int*);
    }

    std::cout << "===== LEVEL 3: CONST =====" << std::endl;
    {
        const int cx = 20;

        auto a = cx;          // const removed
        a++;
        const auto b = cx;    // const kept
        // b++;
        CHECK_TYPE(a, int);
        CHECK_TYPE(b, const int);

        CHECK_CONST(b);
    }

    std::cout << "===== LEVEL 4: REFERENCE =====" << std::endl;
    {
        int x = 10;
        int& r = x;

        auto a = r;      // reference removed
        a = 100;
        std::cout << "Gia tri cua x (reference removed)= " << x << std::endl;

        auto& b = r;     // reference kept
        b = 30;
        std::cout << "Gia tri cua x (reference kept) x = " << x << std::endl;

        CHECK_TYPE(a, int);
        CHECK_TYPE(b, int&);

        CHECK_REF(b);
    }

    std::cout << "===== LEVEL 5: ARRAY =====" << std::endl;
    {
        int arr[3] = {1, 2, 3};

        auto a = arr;      // decay to pointer
        auto& b = arr;     // reference to array

        CHECK_TYPE(a, int*);
        CHECK_TYPE(b, int (&)[3]);
    }

    std::cout << "===== LEVEL 6: FUNCTION RETURN =====" << std::endl;
    {
        auto x = foo();

        CHECK_TYPE(x, int);
    }

    std::cout << "===== LEVEL 7: EXPRESSION =====" << std::endl;
    {
        auto x = 10 + 3.5;   // int + double -> double

        CHECK_TYPE(x, double);
    }

    std::cout << "All type checks passed successfully." << std::endl;
    return 0;
}

#endif

/* For Loop
* Vòng lặp dựa trên phạm vi giúp mã nguồn ngắn gọn, dễ đọc và ít
* xảy ra lỗi hơn so với vòng lặp for truyền thống.
* Các biến thể quan trọng:
* - Duyệt bằng bản sao (Access by Copy)
* - Duyệt bằng tham chiếu (Access by Reference - &)
* - Duyệt bằng tham chiếu hằng (Access by const Reference - const &)
*/

#if 0
#include <iostream>

int main()
{
    int arr[3] = {1, 2, 3};

    std::cout << "Initial array:\n";
    for (int x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    // (1) auto  -> COPY
    std::cout << "[1] for (auto x : arr)  // copy\n";
    for (auto x : arr)
    {
        x *= 10;   // modify copy only
    }

    std::cout << "After auto x loop:\n";
    for (int x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    // (2) auto& -> MODIFY ORIGINAL
    std::cout << "[2] for (auto& x : arr)  // reference\n";
    for (auto& x : arr)
    {
        x *= 10;   // modify original
    }

    std::cout << "After auto& x loop:\n";
    for (int x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    // (3) const auto& -> READ ONLY
    std::cout << "[3] for (const auto& x : arr)  // read only\n";
    for (const auto& x : arr)
    {
        std::cout << x << " ";
        // x *= 10; 
    }
    std::cout << "\n";

    return 0;
}
#endif 

/* Hàm nạp chồng (Function Overloading)
    - Hàm nạp chồng là khả năng của C++ cho phép chúng ta định nghĩa nhiều hàm cùng tên nhưng có tham số khác nhau
      (về số lượng, kiểu dữ liệu, hoặc cả hai). Trình biên dịch sẽ tự động chọn hàm phù hợp dựa trên các tham 
      số được truyền vào khi hàm được gọi.
*/

#if 0
#include <iostream>

// Hàm nạp chồng với tham số kiểu int
int add(int a, int b) {
    return a + b;
}

// Hàm nạp chồng với tham số kiểu double
double add(double a, double b) {
    return a + b;
}

// Hàm nạp chồng với 3 tham số: 2 kiểu int, 1 float
float add(int a, int b, float c) {
    return a + b + c;
}

int main() {
    // Gọi hàm add với tham số int, trình biên dịch chọn hàm add(int, int)
    std::cout << "Tong so nguyen: " << add(5, 10) << std::endl;

    // Gọi hàm add với tham số double, trình biên dịch chọn hàm add(double, double)
    std::cout << "Tong so thuc: " << add(5.5, 10.2) << std::endl;

    // Gọi hàm add với 3 tham số, trình biên dịch chọn hàm add(int, int, float)
    std::cout << "Tong so thuc: " << add(1, 2, 5.5) << std::endl;

    return 0;
}
#endif

/*
* Namespace
* để nhóm các thực thể (như lớp, hàm, biến) lại với nhau dưới một cái tên. Mục đích chính là để
* tránh xung đột tên
*/

#if 0
#include <iostream>

/* Namespace đơn */
namespace A
{
    int value = 10;

    int add(int x)
    {
        return x + value;
    }
}

/* Namespace lồng nhau */
namespace B
{
    int value = 100;

    namespace C
    {
        int value = 1000;

        int add(int x)
        {
            return x + value;
        }
    }
}

/* Namespace khác nhưng trùng tên hàm */
namespace D
{
    int add(int x)
    {
        return x + 1;
    }
}

int main()
{
    std::cout << "===== BASIC NAMESPACE =====\n";
    std::cout << "A::add(5) = " << A::add(5) << std::endl;

    std::cout << "\n===== NESTED NAMESPACE =====\n";
    std::cout << "B::C::add(5) = " << B::C::add(5) << std::endl;

    std::cout << "\n===== USING NAMESPACE (LOCAL) =====\n";
    {
        using namespace A;
        std::cout << "add(5) = " << add(5) << std::endl;
    }

    std::cout << "\n===== USING 2 NAMESPACES (LOCAL) =====\n";
    {
        using namespace A;
        using namespace D;

        // add(5);   // ambiguous -> compiler error

        std::cout << "A::add(5) = " << A::add(5) << std::endl;
        std::cout << "D::add(5) = " << D::add(5) << std::endl;
    }

    std::cout << "\n===== USING NAMESPACE (GLOBAL STYLE) =====\n";
    using namespace B::C;
    std::cout << "add(5) = " << add(5) << std::endl;

    return 0;
}
#endif


/*
* Template là cơ chế của C++ cho phép viết mã tổng quát (generic code), trong đó kiểu dữ liệu được tham số hóa.
* Trình biên dịch sẽ tạo ra mã cụ thể (instantiation) khi template được sử dụng với một kiểu dữ liệu xác định.
* - Ví dụ:  Không dùng template, ta thường phải viết các hàm giống nhau cho từng kiểu:
*  + int max_int(int a, int b);
*  + float max_float(float a, float b);
*  + double max_double(double a, double b);
*  ---> Lặp code 
*   Cú pháp: template <typename T>
*/

#if 0
#include <iostream>
using namespace std;

/*
 * Generic function template
 * T must support operator >
 */
template <typename T>
T my_max(T a, T b)
{
    return (a > b) ? a : b;
}

int main()
{
    int a = 10, b = 20;
    float x = 3.14f, y = 2.71f;
    char c1 = 'A', c2 = 'Z';

    cout << "Max int: " << my_max<int>(a, b) << endl;
    cout << "Max float: " << my_max<float>(x, y) << endl;
    cout << "Max char: " << my_max<char>(c1, c2) << endl;

    return 0;
}

#endif