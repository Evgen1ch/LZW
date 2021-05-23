#pragma once
#include <chrono>
#include <iostream>

class LzwTimer
{
public:
	/*LzwTimer() {
		m_start = std::chrono::high_resolution_clock::now();
	}
	~LzwTimer() {
		m_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = m_end - m_start;
		std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
	}*/
	void start() {
		m_start = std::chrono::high_resolution_clock::now();
		std::cout << "Start..." << std::endl;
	}
	void end() {
		m_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = m_end - m_start;
		std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> m_start;
	std::chrono::time_point<std::chrono::steady_clock> m_end;
};


