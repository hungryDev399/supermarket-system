#include "pch.h"

class String {
public:
	String();
	String(const char* string) {
		printf("Created\n");
		m_size = strlen(string);
		m_Data = new char[m_size];
		memcpy(m_Data, string, m_size);
	}

	String(const String& other) {
		printf("Copied\n");
		m_size = other.m_size;
		m_Data = new char[m_size];
		memcpy(m_Data, other.m_Data, m_size);
	}

	String(String&& other) noexcept {
		printf("moved\n");
		m_size = other.m_size;
		m_Data = other.m_Data;
		other.m_Data = nullptr;
		other.m_size = 0;
	}

	~String() {
		delete m_Data;
		printf("Destroyed\n");
	}

	void Print() {
		for (uint32_t i = 0; i < m_size;i++) {
			printf("%c", m_Data[i]);
		}
		printf("%c", '\n');
	}

private:
	char* m_Data;
	uint32_t m_size;

};


class ENTITY {
public:
	ENTITY(String&& name):m_Name((String&&)name) {
		
	}
	ENTITY(const String& name) :m_Name(name) {

	}

	void printName() {
		m_Name.Print();
	}
private:
	String m_Name;
};

int mainlandr() {
	ENTITY entity("Moahemd");
	entity.printName();
	std::cin.get();
	return 0;
}