#include <random>
#include <mutex>
#include <iostream>
#include <thread>

bool available = true;
int count = 0;
std::mutex m;


void room() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type>dist6(1, 10);

    bool active = true;

    bool first = true;
    while (active) {

        int ran = dist6(rng);
        if (ran == 1) {
            m.lock();
            if (count == 10) {
                active = false;
                m.unlock();
                break;
            }
            if (available) {
                available = false;
                m.unlock();
                if (first) {
                    first = false;
                    count++;
                }
                m.lock();
                available = true;
                m.unlock();
            }
            else
                m.unlock();
        }
    }
}

int main(int argc, char* argv[]) {

    std::thread first(room);
    std::thread second(room);
    std::thread third(room);
    std::thread four(room);
    std::thread five(room);
    std::thread six(room);
    std::thread seven(room);
    std::thread eight(room);
    std::thread nine(room);
    std::thread ten(room);

    first.join();
    second.join();
    third.join();
    four.join();
    five.join();
    six.join();
    seven.join();
    eight.join();
    nine.join();
    ten.join();

    std::cout << "done";

}