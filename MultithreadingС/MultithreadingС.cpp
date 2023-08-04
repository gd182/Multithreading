#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <locale>
#include <mutex>
//#include "SimpleTimer.h"

using namespace std;

void Work() {
    int count = 10;
    for (int i = 0; i < count;i++) {
        cout << this_thread::get_id() <<"\tWork\t" << " " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void Work2(int a, int b) {
    cout << this_thread::get_id() << "\tWork2 start\t" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "a+b=" << a + b << endl;
    this_thread::sleep_for(chrono::milliseconds(4000));
}

void Work3(int &a, int b) {
    cout << this_thread::get_id() << "\tWork2 start\t" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    a += b;
    this_thread::sleep_for(chrono::milliseconds(4000));
}

int Work4(int a, int b) {
    cout << this_thread::get_id() << "\tWork2 start\t" << endl;
    this_thread::sleep_for(chrono::milliseconds(4000));
    return (a + b);
}

class MClass {
public:
    void Work() {
        int count = 10;
        for (int i = 0; i < count;i++) {
            cout << this_thread::get_id() << "\tWork\t" << " " << i << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }

    void Work2(int a, int b) {
        cout << this_thread::get_id() << "\tWork2 start\t" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "a+b=" << a + b << endl;
        this_thread::sleep_for(chrono::milliseconds(4000));
    }

    int Work4(int a, int b) {
        cout << this_thread::get_id() << "\tWork2 start\t" << endl;
        this_thread::sleep_for(chrono::milliseconds(4000));
        return (a + b);
    }
};

mutex mtx;
recursive_mutex rmtx; //позволяет несколько раз захватить (lock) unlock нужно делать столько же раз

void Print(char s) {
    //mtx.lock();   //возможность доступа только одним потоком
    //{
    lock_guard<mutex> lg(mtx); //автоматический unlock ( lock при создании). Можно ограничить видемость с помощью {}

    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            cout << s;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl;
    }
    //mtx.unlock();
    //}
}

void Print1(char s) {
for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            cout << s;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl;
    }
}

void F(int a) {
    rmtx.lock();
    cout <<" "<< a;
    this_thread::sleep_for(chrono::milliseconds(10));
    if (a <= 1) {
        cout << endl;
        rmtx.unlock();
        return;
    }
    a--;
    F(a);
    rmtx.unlock();
}

void Print3(char s) {
    //unique_lock<mutex> ul(mtx);//автоматический lock
    unique_lock<mutex> ul(mtx, defer_lock); //отключение автоматического lock
    this_thread::sleep_for(chrono::milliseconds(1000));

    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            cout << s;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl;
    }
    ul.unlock();
    this_thread::sleep_for(chrono::milliseconds(1000));
}

int main()
{
    /*//setlocate(LC_ALL,"ru");
    cout << "start"<<endl;
    int count = 5;
    
    //thread th(Work);
    //thread th(Work2, 2, 3);
    //th.detach(); //разрыв связи между потоками ( не ждем завершения)
    
    //int s = 2;
    //thread th3(Work3, ref(s), 3);
    int res;
    //auto f = [&res]() {res = Work4(2, 5);};
    //thread th4(f);
    //thread th4([&res]() {res = Work4(2, 5);}); //использование лямбда функции

    MClass mc;
    thread th4([&]() {res = mc.Work4(2, 5);});
    //thread th5([&]() { mc.Work();});
    thread th5(&MClass::Work,mc);
    thread th6(&MClass::Work2, mc,2,7);

    for (int i = 0; i < count;i++) {
        cout << this_thread::get_id() << "\tMain\t" << " " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
   // th3.join(); //дождаться поток
    //cout << s << endl;

    th4.join();
    th5.join();
    th6.join();
    cout << res << endl;*/




    /*thread t1(Print, 'c');
    thread t2(Print, 's');

    t1.join();
    t2.join();*/

    /*thread t1(F, 10);
    thread t2(F, 10);

    t1.join();
    t2.join();*/

    thread t1(Print, 'c');
    thread t2(Print, 's');

    t1.join();
    t2.join();


    _getch();
    return 0;
}