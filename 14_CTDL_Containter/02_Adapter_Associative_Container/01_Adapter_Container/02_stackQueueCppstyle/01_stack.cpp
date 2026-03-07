/*******************************************************************************
 * std::stack (Adapter Container)
 * * - Giới thiệu:
 * + Hoạt động theo cơ chế "Vào sau - Ra trước" (LIFO).
 * + Là một bộ chuyển đổi (Adapter), mặc định dựa trên `std::deque`.
 * + Khai báo: `std::stack<type> name;` hoặc `std::stack<type, container> name;`
 * * - Container nền (Sequence Container):
 * + Mặc định: **std::deque**.
 * + Có thể thay thế bằng: **std::vector** hoặc **std::list**.
 * * - Ưu điểm:
 * + Quản lý dữ liệu theo thứ tự ngược rất hiệu quả (như lịch sử trình duyệt, Undo).
 * + Giao diện đơn giản, ngăn chặn các thao tác truy cập sai quy tắc LIFO.
 * * - Nhược điểm:
 * + KHÔNG hỗ trợ truy cập ngẫu nhiên (không dùng được `[]` hoặc `at()`).
 * + KHÔNG hỗ trợ Iterators (không thể duyệt bằng vòng lặp for-each thông thường).
 * * - Các phương thức chính:
 * + push(value): Thêm phần tử vào đỉnh stack.
 * + pop(): Loại bỏ phần tử ở đỉnh stack (không trả về giá trị).
 * + top(): Truy cập phần tử ở đỉnh stack.
 * + size(): Trả về số lượng phần tử hiện có.
 * + empty(): Kiểm tra stack có rỗng hay không.
 *******************************************************************************/

#include <iostream>
#include <stack>
#include <string>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

bool check_integrity_cpp(const std::string &packet)
{
    std::stack<char> s;

    for (char c : packet)
    {
        if (c == '{' || c == '[' || c == '(')
        {
            s.push(c);
        }
        else if (c == '}' || c == ']' || c == ')')
        {
            if (s.empty())
                return false;

            char top = s.top();
            s.pop();

            if ((c == '}' && top != '{') ||
                (c == ']' && top != '[') ||
                (c == ')' && top != '('))
            {
                return false;
            }
        }
    }
    return s.empty();
}

int main()
{
    std::string p1 = "{\"temp\": 25, \"data\": [1, 2, 3]}";
    std::string p2 = "{\"temp\": 25, \"data\": [1, 2, 3}";

    std::cout << "--- C++ STACK PACKET CHECKER ---" << std::endl;

    std::cout << "Packet 1: " << p1.c_str() << ": " << (check_integrity_cpp(p1) ? GREEN "VALID" : RED "INVALID") << RESET << std::endl;
    std::cout << "Packet 2: " << p2.c_str() << ": " << (check_integrity_cpp(p2) ? GREEN "VALID" : RED "INVALID") << RESET << std::endl;

    return 0;
}
