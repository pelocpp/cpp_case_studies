#include <chrono>  
#include <string>
#include <iostream>
#include <random>  
#include <thread>   
#include <mutex>  
#include <condition_variable>

#include "Logger.h"

const int NumPhilosophers = 5;         // number of dining philosophers
const int MinSleepingMSecs = 10;       // sleeping between 1 and ...
const int MaxSleepingMSecs = 30;       // ... 3 seconds
const int SimulationDuration = 3000;   // total time of simulation (milliseonds)

enum class PhilosopherState { None, Thinking, Eating, Hungry };

class Table {
private:
	bool m_forks[NumPhilosophers];

	std::mutex m_mtx;   // mutex for critical section
	std::condition_variable m_cv;

public:
	Table();

	// pubic interface
	void DemandForks(int seat);
	void ReleaseForks(int seat);

	// test interface
	std::string forksToString();

	// index operator
	bool& operator[] (int index);
};

Table::Table() {
	for (size_t i = 0; i < NumPhilosophers; i++) {
		m_forks[i] = false;
	}
}

bool& Table::operator[] (int index) {
	int seat = index % 5;
	return m_forks[seat];
}

void Table::DemandForks(int seat) {
	Logger::log({ "demand forks at seat " , std::to_string(seat)});

	std::unique_lock<std::mutex> lock(m_mtx);
	m_cv.wait(lock, [&] {return (*this)[seat] == false && (*this)[seat + 1] == false; });

	// now we own the lock, take the corresponding forks 
	(*this)[seat] = true;
	(*this)[seat + 1] = true;

	Logger::log({ "got forks at seat " , std::to_string(seat) });

	// create current display string of forks thread-safe
	std::string forksDisplay = forksToString();

	// unlock mutex manually, so that other philosophers have access to the table
	lock.unlock();

	// output latest forks display string - not necessary within critical section
	Logger::logAbs({ forksDisplay });
}

void Table::ReleaseForks(int seat) {
	Logger::log({ "release forks at seat ", std::to_string(seat) });

	std::unique_lock<std::mutex> lock(m_mtx);

	// now we own the lock, release the corresponding forks 
	(*this)[seat] = false;
	(*this)[seat + 1] = false;

	Logger::log({ "released forks at seat " , std::to_string(seat) });

	// create current display string of forks thread-safe
	std::string forksDisplay = forksToString();

	// unlock mutex manually, so that other philosophers have access to the table
	lock.unlock();

	// wakeup other waiting  philosophers
    // (manual unlock is done before - thus avoiding waking up threads in vain) 
	m_cv.notify_all();

	// output latest forks display string - not necessary within critical section
	Logger::logAbs({ forksDisplay });
}

std::string Table::forksToString() {
	std::string sforks("");
	for (size_t i = 0; i < NumPhilosophers; i++) {
		sforks.append(m_forks[i] ? "X" : "_");
	}
	return sforks;
}

// ============================================================

class Philosopher {

private:
	// dining philosophers utilities
	Table& m_table;
	int m_seat;
	PhilosopherState m_state;

	// random utilities
	static std::random_device device;
	static std::mt19937 generator;
	static std::uniform_int_distribution<int> distribution;

	// threading utils
	std::thread m_thread;
	bool m_running;

public:
	Philosopher(Table& table, int seat);

	void Start();
	void Detach();
	void Run();
	void Stop();

private:
	void Thinking();
	void Hungry();
	void Eating();
	void EatingDone();
};

// initialize static class members
std::random_device Philosopher::device;
std::mt19937 Philosopher::generator(Philosopher::device());
std::uniform_int_distribution<int> Philosopher::distribution(MinSleepingMSecs, MaxSleepingMSecs);  

Philosopher::Philosopher(Table& table, int seat) : m_table(table), m_seat(seat) {
	m_state = PhilosopherState::None;
	m_running = false;
}

void Philosopher::Start() {
	m_running = true;
	m_thread = std::thread([this] { Run(); });
}

void Philosopher::Stop() {
	m_running = false;
}

void Philosopher::Detach() {
	m_thread.detach();
}

void Philosopher::Thinking() {
	Logger::log({ "thinking at seat " , std::to_string(m_seat) });
	m_state = PhilosopherState::Thinking;
	int milliSecondsSleeping = distribution(generator);
	std::this_thread::sleep_for(std::chrono::milliseconds(milliSecondsSleeping));
}

void Philosopher::Hungry() {
	Logger::log({ "hungry at seat " , std::to_string(m_seat) });
	m_state = PhilosopherState::Hungry;
	m_table.DemandForks(m_seat);
}

 void Philosopher::Eating() {
	 Logger::log({ "eating at seat " , std::to_string(m_seat) });
	 m_state = PhilosopherState::Eating;
	 int milliSecondsEating = distribution(generator);
	 std::this_thread::sleep_for(std::chrono::milliseconds(milliSecondsEating));
 }

void Philosopher::EatingDone() {
	Logger::log({ "eating done at seat " , std::to_string(m_seat) });
	m_table.ReleaseForks(m_seat);
}

void Philosopher::Run() {

	std::thread::id philosopherThreadId = std::this_thread::get_id();
	Logger::logAbs({ "philosopher enters room"  });

	while (m_running) {
		Thinking();
		Hungry();
		Eating();
		EatingDone();
	}

	Logger::logAbs({ "philosopher at seat " , std::to_string(m_seat), " quits." });
	m_state = PhilosopherState::None;
}

// ============================================================

void testDiningPhilosophers() {

	Logger::enableLogging(false);

	std::thread::id mainThreadId = std::this_thread::get_id();
	size_t mainTid = Logger::readableTID(mainThreadId);
	Logger::log({ 
		"Dining Philosophers Simulation [TID=",
		std::to_string(Logger::readableTID(mainThreadId)),
		"]" });

	Table table;

	Logger::logAbs({ table.forksToString() });

	Philosopher p1(table, 0);
	Philosopher p2(table, 1);
	Philosopher p3(table, 2);
	Philosopher p4(table, 3);
	Philosopher p5(table, 4);

	p1.Start();
	p2.Start();
	p3.Start();
	p4.Start();
	p5.Start();

	p1.Detach();
	p2.Detach();
	p3.Detach();
	p4.Detach();
	p5.Detach();

	// set duration time of this simulation
	std::this_thread::sleep_for(std::chrono::milliseconds(SimulationDuration));

	// terminate simulation
	p1.Stop();
	p2.Stop();
	p3.Stop();
	p4.Stop();
	p5.Stop();

	std::this_thread::sleep_for(std::chrono::milliseconds(NumPhilosophers * MaxSleepingMSecs));
	Logger::logAbs({ "Done." });
}

int main()
{
	testDiningPhilosophers();
	return 0;
}

// ============================================================

//
//https://gist.github.com/anuragsoni/ea8af6637fa50ba90854
//
//https://mariusbancila.ro/blog/2017/01/16/dining-philosophers-in-cpp11/
//
//http://peterloos.de/index.php/m-multithreading/m-multithreading-class-thread/15-a-mt-dining-philosophers
//
//https://en.cppreference.com/w/cpp/thread/condition_variable/wait
//
//http://www.cplusplus.com/reference/condition_variable/condition_variable/wait/
//
//https://en.cppreference.com/w/cpp/thread/condition_variable
//
