#pragma once
#include <utility>
#include <iostream>

namespace Aqua {
class Log {
public:
	Log() {}

	~Log() {
		this->Warn("Destroying log: ", gameName);
	}

	static void InitLog(const char* gameName) {
		aqLog = new Log();
		aqLog->gameName = "Aqua";

		gameLog = new Log();
		gameLog->gameName = gameName;
	}

	template <typename... Args> 
	void Info(Args&&... args) {
		if (logLevel > LogLevel::INFO) { return; }
		log_impl("\033[94m[", gameName, " INFO]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Warn(Args&&... args) {
		if (logLevel > LogLevel::WARN) { return; }
		log_impl("\033[93m[", gameName, " WARN]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Error(Args&&... args) {
		if (logLevel > LogLevel::ERROR) { return; }
		log_impl("\033[41m\033[97m[", gameName, " ERROR]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Debug(Args&&... args) {
		if (logLevel > LogLevel::DEBUG) { return; }
		log_impl("\033[97m[", gameName, " DEBUG]: ", std::forward<Args>(args)...);
	}
	
	static Log* AquaLog() {
		return aqLog;
	}

	static Log* GameLog() {
		return gameLog;
	}
	
	enum LogLevel {
		DEBUG,
		INFO,
		WARN,
		ERROR,
		NONE
	};

	void SetLogLevel(LogLevel level) {
		logLevel = level;
	};

private:
	const char* gameName = "Logger";
		
	LogLevel logLevel = DEBUG;

	static Log* aqLog;
	static Log* gameLog;

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
