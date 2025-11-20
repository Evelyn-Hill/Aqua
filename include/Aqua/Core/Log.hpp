#pragma once
#include <utility>
#include <iostream>

namespace Aqua {

class Log {
public:
	Log(const char* name) {
		m_LogName = name;
	}

	~Log() {
		this->Warn("Destroying log: ", m_LogName);
	}

	template <typename... Args> 
	void Info(Args&&... args) {
		if (m_LogLevel > LogLevel::INFO) { return; }
		log_impl("\033[94m[", m_LogName, " INFO]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Warn(Args&&... args) {
		if (m_LogLevel > LogLevel::WARN) { return; }
		log_impl("\033[93m[", m_LogName, " WARN]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Error(Args&&... args) {
		if (m_LogLevel > LogLevel::ERROR) { return; }
		log_impl("\033[41m\033[97m[", m_LogName, " ERROR]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Debug(Args&&... args) {
		if (m_LogLevel > LogLevel::DBG) { return; }
		log_impl("\033[97m[", m_LogName, " DEBUG]: ", std::forward<Args>(args)...);
	}
		
	enum class LogLevel {
		DBG,
		INFO,
		WARN,
		ERROR,
		NONE
	};

	void SetLogLevel(LogLevel level) {
		m_LogLevel = level;
	};

	static Log* AquaLog() {
		return AquaLogger;
	}

	static Log* GameLog() {
		return GameLogger;
	}

private:
	const char* m_LogName = "Logger";
	
	static Log* AquaLogger;
	static Log* GameLogger;

	LogLevel m_LogLevel = LogLevel::DBG;

	void log_impl() {
		std::cout << "\033[0m"<< std::endl;
	}

	template <typename T, typename... Args>
	void log_impl(T&& first_arg, Args&&... remaining_args) {
		std::cout << std::forward<T>(first_arg);
		log_impl(std::forward<Args>(remaining_args)...);
	}
};

}
