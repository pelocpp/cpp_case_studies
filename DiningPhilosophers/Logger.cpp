#include <iostream>

#include "Logger.h"

bool Logger::m_loggingEnabled = false;
std::ostream& Logger::m_os = std::cout;
bool Logger::m_logActive = false;
std::mutex Logger::m_mutexOutput;

std::size_t Logger::nextIndex = 0;
std::mutex Logger::mutexIds;
std::map<std::thread::id, std::size_t> Logger::mapIds;

// ============================================================

void testLogger1();
void testLogger2();
void testLogger3();

// ============================================================

void testLogger1() {

	// Logger::log(1231, 3.5);
	Logger::enableLogging(true);
	// Logger::log(1, 2, 3);

	Logger::log({ std::string("12345"), std::string("45678"), std::string("12789") });
	Logger::log({ std::string("aa "), std::string("bb "), std::string("cc") });
}

void testLogger2() {

	// Logger::log(1231, 3.5);
	Logger::enableLogging(true);
	// Logger::log(1, 2, 3);

	Logger::log({ std::string("12345"), std::string("45678"), std::string("12789") });
	Logger::log({ std::string("aa "), std::string("bb "), std::string("cc") });

}

void stressLog() {
	for (size_t i = 0; i < 5; i++) {
		Logger::log({ std::to_string(i), "   45678", "  12789" });
	}
}

void testLogger3() {

	Logger::enableLogging(true);

	std::thread::id mainThreadId = std::this_thread::get_id();
	size_t mainTid = Logger::readableTID(mainThreadId);
	std::cout << "testLogger3 [TID=" << mainTid << "]" << std::endl;

	std::thread t1(stressLog);
	std::thread t2(stressLog);

	t1.join();
	t2.join();
}

int main_()
{
	testLogger1();
	testLogger2();
	testLogger3();
	return 0;
}