#pragma once

/*
	///
   <* \__/
	\___/
	 _|
	Jack Hunt
*/

class Singleton {
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}

private:
	Singleton() {}
	Singleton(Singleton const&);
	void operator=(Singleton const&);

public:
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};