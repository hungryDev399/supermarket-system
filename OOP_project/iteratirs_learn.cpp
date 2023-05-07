#include "pch.h"
#include <unordered_map>

class String {
public:
	String();
	String(const char* string) {
		//printf("Created\n");
		m_size = strlen(string);
		m_Data = new char[m_size+1];
		memcpy(m_Data, string, m_size+1);
	}

	String(const String& other) {
		//printf("Copied\n");
		m_size = other.m_size;
		m_Data = new char[m_size];
		memcpy(m_Data, other.m_Data, m_size);
	}

	String(String&& other) noexcept {
		//printf("moved\n");
		m_size = other.m_size;
		m_Data = other.m_Data;
		other.m_Data = nullptr;
		other.m_size = 0;
	}

	~String() {
		delete m_Data;
		//printf("Destroyed\n");
	}

	void Print() {
		for (uint32_t i = 0; i < m_size;i++) {
			printf("%c", m_Data[i]);
		}
		printf("%c", '\n');
	}

	friend std::ostream& operator<<(std::ostream& os, const String& str);

private:
	char* m_Data;
	uint32_t m_size;

};

std::ostream& operator<<(std::ostream& os, const String& str) {
	os << str.m_Data;
	return os;
}

int mainit() {

	String str = "Mohamed";
	std::cout << str << std::endl;



#if 0
	std::vector<int> vals = {1,2,3,4,5};

	for (int val : vals)
		std::cout << val << std::endl;

	std::cout << std::endl;

	for (std::vector<int>::iterator it = vals.begin();
		it != vals.end(); ++it) std::cout << *it << std::endl;
#endif

	/*using strIntMap = std::unordered_map<std::string, int>;
	strIntMap map;
	map["C++03"] = 2003;
	map["C++14"] = 2014;

	for (strIntMap::const_iterator it = map.begin();
		it != map.end(); it++) {
		auto& key = it->first;
		auto& value = it->second;

		std::cout << key << " = " << value << std::endl;
	}

	std::cout << std::endl;

	for (auto [k, v] : map)
		std::cout << k << " = " << v << std::endl;*/


	return 0;
}