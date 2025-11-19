#pragma once
#include <utility>
#include <iostream>



namespace Aqua {

class Log {
public:
	Log(const char* name) {
		logName = name;

		if (AquaLogger == NULL) 
			AquaLogger = new Log("Aqua");
		else 
			AquaLogger->Error("Aqua log already initialized! Use Log::<Logger>() to retrieve it!");

		if (GameLogger == NULL)
			GameLogger = new Log(name);
		else 
			AquaLogger->Error("Game log already initialized! Use Log::<Logger>() to retrieve it!");
	}

	~Log() {
		this->Warn("Destroying log: ", logName);
	}

	template <typename... Args> 
	void Info(Args&&... args) {
		if (logLevel > LogLevel::INFO) { return; }
		log_impl("\033[94m[", logName, " INFO]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Warn(Args&&... args) {
		if (logLevel > LogLevel::WARN) { return; }
		log_impl("\033[93m[", logName, " WARN]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Error(Args&&... args) {
		if (logLevel > LogLevel::ERROR) { return; }
		log_impl("\033[41m\033[97m[", logName, " ERROR]: ", std::forward<Args>(args)...);
	}

	template <typename... Args> 
	void Debug(Args&&... args) {
		if (logLevel > LogLevel::DEBUG) { return; }
		log_impl("\033[97m[", logName, " DEBUG]: ", std::forward<Args>(args)...);
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

	static Log* AquaLog() {
		return AquaLogger;
	}

	static Log* GameLog() {
		return GameLogger;
	}

private:
	const char* logName = "Logger";
	
	static Log* AquaLogger;
	static Log* GameLogger;

	LogLevel logLevel = DEBUG;

	void log_impl() {
		std::cout << "\033[0m"<< std::endl;
	}

	template <typename T, typename... Args>
	void log_impl(T&& first_arg, Args&&... remaining_args) {

		std::cout << std::forward<T>(first_arg);
		log_impl(std::forward<Args>(remaining_args)...);
	}
};

static Log* AquaLogger;
static Log* GameLogger;

static Log* AquaLog();
static Log* GameLog();
}
