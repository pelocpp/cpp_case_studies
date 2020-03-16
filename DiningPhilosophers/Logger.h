#pragma once

#include <map>
#include <string>
#include <iostream>
#include <mutex>

class Logger
{
public:
	Logger() = default;

private:
	static bool m_loggingEnabled;
	static std::ostream& m_os;
	static bool m_logActive;

	static std::size_t nextIndex;
	static std::mutex mutexIds;
	static std::map<std::thread::id, std::size_t> mapIds;

	// locking utils
	static std::mutex m_mutexOutput;

public:
	static void enableLogging(bool enable) {
		m_loggingEnabled = enable;
	}

	static bool isLoggingEnabled() {
		return m_loggingEnabled;
	}

	static void _log() { 
		m_os << " Endeeeeeeee "; 
		m_logActive = false;
	}  // 'initial' method

	template<typename T1, typename... Tn>
	static void _log(T1 arg, Tn... args) {

		if (!m_loggingEnabled)
			return;

		if (!m_logActive) {
			m_os << " Starttttttt ";
			m_logActive = true;
		}
		printHeader();
		print(arg);
		printTrailer();
		log(args...);
	}

	template<typename T3>
	static void log2(std::initializer_list<T3>&& list) {
		for (auto item : list) {
			m_os << item;
			m_os.put('\n'); 
		}
	}

	static void log(std::initializer_list<std::string>&& list) {

		if (!m_loggingEnabled)
			return;

		logInternal(std::move(list));
	}

	// log unconditionally
	static void logAbs(std::initializer_list<std::string>&& list) {
		logInternal(std::move(list));
	}

private:
	static void logInternal(std::initializer_list<std::string>&& list) {

		std::string s;
		for (auto item : list) {
			s.append(item);
		}

		std::thread::id currentThreadId = std::this_thread::get_id();
		size_t tid = readableTID(currentThreadId);

		std::string prefix = "[" + std::to_string(tid) + "]";
		const std::lock_guard<std::mutex> lock(m_mutexOutput);
		m_os << prefix << ": " << s;
		m_os.put('\n');
	}

public:
	// public helper methods
	static size_t readableTID(const std::thread::id id)
	{
		std::lock_guard<std::mutex> lock(mutexIds);
		if (mapIds.find(id) == mapIds.end()) {
			nextIndex++;
			mapIds[id] = nextIndex;
		}

		return mapIds[id];
	}

private:
	// private helper methods
	static void printHeader() {
		m_os << "Anfang: ";
	}

	static void printTrailer() {
		m_os << " Ende: ";
		m_os.put('\n');
	}

	static void print(int value) {
		m_os << value;
	}

	static void print(double value) {
		m_os << value;
	}

	static void print(std::string value) {
		m_os << value;
	}
};


