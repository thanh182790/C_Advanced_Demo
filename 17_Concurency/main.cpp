/*

================================================================================
I: GIỚI THIỆU VỀ PROCESSES (TIẾN TRÌNH) VÀ THREADS (LUỒNG)
================================================================================

1. PROCESS (Tiến trình):
   * Định nghĩa: Là một chương trình đang được thực thi.
   * Đặc điểm:
     * Mỗi Process có **không gian địa chỉ riêng** (vùng nhớ riêng, stack, heap riêng).
     * Process **cô lập** với các Process khác, giao tiếp chủ yếu qua IPC (Inter-Process Communication -
       Giao tiếp giữa các tiến trình).
     * Là đơn vị cấp phát tài nguyên cơ bản của hệ điều hành.
   * Chi phí: Tạo và chuyển đổi giữa các Process (Context Switching) tốn kém hơn so với Thread.

2. THREAD (Luồng):
   * Định nghĩa: Là một đơn vị thực thi nằm trong một Process.
   * Đặc điểm:
     * Các Thread trong cùng một Process **chia sẻ không gian địa chỉ** (chia sẻ heap và code segment,
       mỗi Thread có stack và thanh ghi riêng).
     * Chia sẻ bộ nhớ giúp giao tiếp và đồng bộ hóa nhanh chóng, nhưng dẫn đến nguy cơ **Race Condition**.
     * Là đơn vị lập lịch cơ bản của CPU.
   * Chi phí: Tạo và chuyển đổi giữa các Thread nhanh hơn nhiều so với Process.

3. Concurrency (Đồng thời) vs. Parallelism (Song song):
   * Concurrency: Xử lý nhiều việc *cùng lúc* (có thể xen kẽ trên một lõi CPU).
      - Task A chạy 1 lúc đên task B rôi lại nghỉ back lại task A.
      - Có thể chạy chỉ với 1 CPU core
   * Parallelism: Xử lý nhiều việc *thực sự đồng thời* (trên nhiều lõi CPU). C++ <thread> giúp đạt được cả hai.
      - Bắt buộc phải có đa nhân (Multi-core) hoặc đa CPU.
*/

#if 0
#include <iostream>
#include <unistd.h> // Bao gom ham getpid()

void print_pid_posix()
{
    // getpid() tra ve kieu pid_t, thuong la int
    pid_t current_pid = getpid(); 
    std::cout << "PID cua Process hien tai (Linux): " << current_pid << std::endl;
}

int main()
{
    std::cout << "--- Demo In PID tren Linux ---" << std::endl;
    print_pid_posix();

    std::cout << "Nhan Enter de ket thuc chuong trinh..." << std::endl;
    std::cin.get();

    return 0;
}
#endif

/*
//================================================================================
// II: TẠO THREAD VỚI NORMAL FUNCTION AND FUNCTION OBJECT (FUNCTOR)
//================================================================================

/*
1. Cách tạo Thread trong C++:
   * Sử dụng class **std::thread**.
   * Hàm khởi tạo của std::thread nhận đối số đầu tiên là hàm (hoặc đối tượng gọi được - Callable object) và
   * các đối số còn lại là đối số cho hàm đó.

2. Function Object (Functor):
   * Là một class có nạp chồng (overloading) toán tử gọi hàm **operator()()**.
   * Ưu điểm: Cho phép lưu trữ trạng thái (data members) bên trong đối tượng, điều mà hàm thường không làm được.

3. Quản lý Thread:
   * **std::thread::join()**: Chờ luồng kết thúc trước khi tiếp tục. (Bắt buộc)
   * **std::thread::detach()**: Tách luồng khỏi luồng gọi, cho phép nó chạy độc lập. (Bắt buộc phải gọi một trong hai)
*/

#if 0

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

// Functor Demo
class Worker
{
private:
    int id;

public:
    Worker(int i) : id(i) {}

    // overloading operator() de tao thanh mot Callable object
    void operator()()
    {
        for (int i = 0; i < 3; ++i)
        {
            cout << "Thread ID " << id << ": Lap " << i + 1 << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
};

void NormalFunction(int id, int loopCnt)
{
    for (int i = 0; i < loopCnt; ++i)
    {
        cout << "NormalFunction Thread ID " << id << ": Lap " << i + 1 << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    while (1)
    {
        /* code */
    }
    
}

int main()
{
    cout << "--- Demo 2.1: Tao Thread voi Functor ---" << endl;

    // Tao 2 Thread su dung cung Functor class nhung trang thai (ID) khac nhau
    Worker worker1(101);
    Worker worker2(202);

    thread t1(NormalFunction, 404, 5); // Truyen vao Normal Function
    thread t2(worker1);                // Truyen vao Functor
    thread t3(Worker(303));            // Tao Functor tam thoi va truyen vao

    // Luu y: Functor duoc truyen vao theo gia tri (copy), neu muon truyen tham chieu
    // can su dung std::ref(worker_object).

    t1.join(); // Doi t1 ket thuc  ---> block cho ddeen khi thread t1 ket thuc 
    t2.join(); // Doi t2 ket thuc   
    t3.join(); // Doi t3 ket thuc

    cout << "--- Tat ca Thread da ket thuc ---" << endl;

    return 0;
}

#endif

/*
//================================================================================
// III: DEMO VÒNG LẶP VÔ HẠN VÀ DETACH THREAD (BACKGROUND TASK)
//================================================================================
*/

#if 0

#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h> // Bao gom ham getpid()

void print_pid_posix() {
    // getpid() tra ve kieu pid_t, thuong la int
    pid_t current_pid = getpid();
    std::cout << "PID cua Process hien tai (Linux): " << current_pid << std::endl;
}

void timed_loop_forever(int id) {
    std::cout << "Worker " << id << ": Bat dau Task vong lap vo han." << std::endl;
    print_pid_posix();
    int count = 0;

    // Vong lap vo han
    while (true) {
        // --- 1. Thuc hien Cong viec Dinh ky ---
        std::cout << "Worker " << id << ": Dang xu ly cong viec lan thu " << count << std::endl;
        count++;

        // --- 2. Chu dong nhuong CPU (Sleep) ---
        // Thoi gian Sleep quan trong de dat tan suat Task mong muon
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    // Luu y: Do la while(true), doan code nay khong bao gio duoc thuc thi.
}

int main() {
    std::cout << "--- Demo A (Loop Forever): Chan Bang Thoi Gian ---" << std::endl;

    // Tao va Detach thread de no chay ngam trong khi main tiep tuc
    std::thread t1(timed_loop_forever, 1);
    t1.detach();

    std::cout << "Main: Task 1 da duoc khoi dong va detach. Main se cho 15s truoc khi ket thuc." << std::endl;

    // Giu Main thread song de Task background co thoi gian chay
    std::this_thread::sleep_for(std::chrono::seconds(15));

    std::cout << "Main: Ket thuc. Cac detached thread se ket thuc khi Process dong." << std::endl;
    
    return 0;
}

#endif

/*
//================================================================================
// IV: TẠO THREAD VỚI MEMBER FUNCTIONS CỦA CLASS
//================================================================================

/*
1. Truyền đối số cho hàm Thread:
   * Các đối số cho hàm được truyền trực tiếp vào hàm khởi tạo std::thread, sau đối số Callable object.
   * Các đối số được truyền theo **giá trị (by value)** theo mặc định.
   * Để truyền tham chiếu (by reference), phải sử dụng **std::ref()**.

2. Thread và Member Functions:
   * Để chạy một member function (hàm thành viên) trong một Thread, đối số đầu tiên
     phải là **con trỏ hoặc tham chiếu đến đối tượng** chứa hàm đó.
   * Cú pháp: `std::thread( &Class::member_function, &object, arg1, arg2, ... )`
     * `&Class::member_function`: Địa chỉ của hàm thành viên.
     * `&object`: Con trỏ đến đối tượng (hoặc `this` nếu gọi bên trong lớp).
*/

#if 0

#include <iostream>
#include <thread>
#include <chrono>
#include <functional> // Thu vien bat buoc cho std::ref

class Printer {
public:
    // Ham thanh vien don gian
    void print_message(int num) {
        std::cout << "Printer: Bat dau in " << num << " lan." << std::endl;
        for (int i = 0; i < num; ++i) {
            std::cout << "  > In lan " << i + 1 << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        std::cout << "Printer: Ket thuc in." << std::endl;
    }

    // Ham thanh vien voi doi so tham chieu
    void process_data(int& data_ref) {
        std::cout << "  > Data ban dau: " << data_ref << std::endl;
        data_ref += 100; // Thay doi gia tri truc tiep tai vung nho tham chieu
        std::cout << "  > Data sau khi xu ly: " << data_ref << std::endl;
    }
};

int main() {
    std::cout << "--- Demo 3.1: Tao Thread voi Member Function ---" << std::endl;
    Printer p;

    // --- CASE 1: Chay ham thanh vien print_message ---
    // Doi so dau tien la dia chi ham, doi so thu hai la dia chi doi tuong (&p)
    std::thread t1(&Printer::print_message, &p, 4); // truyen 4 lan in
    
    t1.join();
    std::cout << "--- T1 ket thuc ---" << std::endl;

    std::cout << "\n--- Demo 3.2: Truyen tham chieu vao Thread (std::ref) ---" << std::endl;
    int shared_data = 50;
    std::cout << "Main: Shared data truoc khi tao thread: " << shared_data << std::endl;

    // --- CASE 2: BAT BUOC dung std::ref(shared_data) de dam bao truyen tham chieu ---
    // Neu khong dung std::ref, C++ se copy gia tri 50 va moi thay doi ben trong thread
    // se khong anh huong den bien shared_data o Main.
    std::thread t2(&Printer::process_data, &p, std::ref(shared_data));

    t2.join();
    std::cout << "Main: Shared data sau khi thread ket thuc: " << shared_data << std::endl;
    // shared_data se thay doi thanh 150 neu dung std::ref

    return 0;
}

#endif

//=============================================================================
// V: KHÓA MUTEX VÀ BIẾN ĐIỀU KIỆN
//=============================================================================

/*
1. MUTEX (std::mutex):
   * Mục đích: Giải quyết vấn đề **Race Condition** khi nhiều Thread truy cập và thay đổi **Shared Resource (Tài nguyên chia sẻ)**.
   * Cơ chế: Đảm bảo tại một thời điểm chỉ có **một Thread duy nhất** được phép truy cập vào vùng code được bảo vệ (Critical Section).
   * Các hàm chính:
     * `lock()`: Khóa Mutex. Nếu Mutex đang bị khóa, Thread sẽ bị chặn.
     * `unlock()`: Mở khóa Mutex.

2. RAII Lock Guards:
   * Sử dụng **std::lock_guard** hoặc **std::unique_lock** là cách *nên* làm để quản lý Mutex.
   * RAII (Resource Acquisition Is Initialization): Mutex tự động khóa khi đối tượng lock_guard được tạo và
     tự unlock khi đối tượng bị hủy (khi ra khỏi scope), ngăn chặn lỗi quên unlock() và đảm bảo an toàn ngoại lệ.
   * `std::lock_guard`: Đơn giản, không thể unlock sớm.
   * `std::unique_lock`: Linh hoạt hơn, có thể unlock sớm, cho phép sử dụng với std::condition_variable.

3. CONDITION VARIABLE (std::condition_variable):
   * Mục đích: Cho phép các Thread **chờ** một điều kiện cụ thể xảy ra trước khi tiếp tục thực thi.
   * Thường được sử dụng để:
     * Thông báo giữa Consumer và Producer.
     * Thread chờ dữ liệu hoặc một sự kiện nào đó.
   * Các hàm chính:
     * `wait(unique_lock, condition)`: Chặn Thread và **mở khóa Mutex** (để Thread khác có thể thay đổi điều kiện). Thread sẽ được đánh thức khi nhận được thông báo *và* điều kiện là đúng.
     * `notify_one()`: Đánh thức một Thread đang chờ.
     * `notify_all()`: Đánh thức tất cả các Thread đang chờ.
*/

// Race Condition Example
#if 1
#include <iostream>
#include <thread>
#include <mutex>

#define ENBALE_MUTEX (1) // Thay doi thanh 1 de enabled mutex
#define LOOP_NUMBER (1000000)

int shared_counter = 0;

#if ENBALE_MUTEX
std::mutex mtx;

void safe_increment() {
    for (int i = 0; i < LOOP_NUMBER; ++i) {
        mtx.lock(); // lock mutex
        shared_counter++;
        mtx.unlock(); // unlock mutex
    }
}
#else
void unsafe_increment() {
    for (int i = 0; i < LOOP_NUMBER; ++i) {
        shared_counter++; // Không có mutex bảo vệ
    }
}
#endif

int main() {

#if ENBALE_MUTEX
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);
    std::thread t3(safe_increment);
    std::thread t4(safe_increment);
#else
    std::thread t1(unsafe_increment);
    std::thread t2(unsafe_increment);
    std::thread t3(unsafe_increment);
    std::thread t4(unsafe_increment);
#endif

    std::cout << "Main: Dang cho cac thread ket thuc..." << std::endl;
    t1.join();
    t2.join();
    t3.join();
    t4.join();

#if ENBALE_MUTEX
    std::cout << "Ket qua (dung mutex): " << shared_counter 
              << " (Expected: " << 4 * LOOP_NUMBER << ")" << std::endl;
#else
    std::cout << "Ket qua (khong dung mutex): " << shared_counter 
              << " (Expected: " << 4 * LOOP_NUMBER << ")" << std::endl;
#endif

    return 0;
}
#endif

/* Lệnh C++ đơn giản như `shared_counter++` không phải là một thao tác nguyên tử (atomic operation).
Nó bao gồm ba bước:
1. Đọc giá trị hiện tại của `shared_counter` từ bộ nhớ.
2. Tăng giá trị đó lên 1.
3. Ghi giá trị mới trở lại bộ nhớ.

|   Các Bước                | Luồng 1    | Luồng 2    |
|---------------------------|------------|------------|
| 1. Read shared_counter    | 100        |            |
| 1. Read shared_counter    |            | 100        |
|                           |            |            |
| 2. Increment              | 101        |            |
| 2. Increment              |            | 101        |
|                           |            |            |
| 3. Write shared_counter   | 101        |            |
| 3. Write shared_counter   |            | 101        |
*/

// condition_variable Example
#if 1
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex counter_mutex;

// Bien cho Condition Variable
std::vector<int> data_queue;
std::condition_variable cv;
std::mutex cv_mutex;
bool is_data_ready = false;

bool Check_Data_Ready()
{
    return is_data_ready;
}

// Producer
void producer()
{
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Gia dinh qua trinh tao du lieu mat 1s

    // Tao du lieu
    int data = 42;
    std::cout << "Producer: Tao du lieu: " << data << std::endl;

    {
        std::unique_lock<std::mutex> lock(cv_mutex);
        data_queue.push_back(data);
        is_data_ready = true;
    } // Mutex mo khoa tai day

    // Thong bao cho tat ca cac thread dang cho
    cv.notify_all();
    std::cout << "Producer: Da thong bao. " << std::endl;
}

// Consumer
void consumer(int id)
{
    std::cout << "Consumer " << id << ": Dang cho du lieu." << std::endl;
    std::unique_lock<std::mutex> lock(cv_mutex);

    // Ham wait() se tu dong:
    // 1. Kiem tra dieu kien (is_data_ready)
    // 2. Neu sai, unlock mutex va cho tin hieu
    // 3. Khi duoc thong bao, lock lai mutex va kiem tra dieu kien lai
    cv.wait(lock, Check_Data_Ready);

    // Khi thoat khoi wait(), chung ta co data_ready = true va mutex dang bi khoa boi 'lock'
    int data = data_queue.back();
    data_queue.pop_back();

    std::cout << "Consumer " << id << ": Da nhan du lieu: " << data << std::endl;

    // Mutex tu dong mo khoa khi 'lock' bi huy
}

int main()
{
    std::cout << "\n--- Demo 4.1: Condition Variable (Producer/Consumer) ---" << std::endl;

    std::thread p_thread(producer);

    // Tao 2 Consumer cung cho tin hieu
    std::thread c1_thread(consumer, 1);
    std::thread c2_thread(consumer, 2);

    p_thread.join();
    c1_thread.join();
    c2_thread.join();

    std::cout << "--- Tat ca Thread P/C da ket thuc ---" << std::endl;

    return 0;
}
#endif