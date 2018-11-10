// ThreadsPractice.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <string>
#include <vector>
#include <locale>
#include <random>
#include <mutex>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::chrono::milliseconds;
using std::thread;
using std::lock_guard;
using std::mutex;

mutex outputLock;

int getRandomUpTo(int maxValue)
{
	thread_local std::random_device rD;
	thread_local std::mt19937_64 *rNG = nullptr;
	if (!rNG) rNG = new std::mt19937_64(rD());
	std::uniform_int_distribution<int> distribution(0, maxValue);
	return distribution(*rNG);
}

void executeThread(int threadID)
{
	lock_guard<mutex> lock(outputLock);
	int timeToSleep = getRandomUpTo(2500);
	std::this_thread::sleep_for(milliseconds(timeToSleep));
	cout << "Поток с ID " << threadID << " находился во 'сне' в течение " << timeToSleep << "мс; реальный ID потока: " << std::this_thread::get_id() << endl;
}

int main()
{
	setlocale(LC_CTYPE, "RU");
	cout << "Поток main, реальный ID: " << std::this_thread::get_id() << endl;
	thread leThread0(executeThread, 0), leThread1(executeThread, 1), leThread2(executeThread, 2),
	leThread3(executeThread, 3), leThread4(executeThread, 4);
	leThread0.join(); leThread1.join(); leThread2.join(); leThread3.join(); leThread4.join();
	return 0;
}
