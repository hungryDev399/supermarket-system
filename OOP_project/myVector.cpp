#include "pch.h"

struct Vector3 {
	float x, y, z;
	int* memoryBlock = nullptr;
	Vector3 ():x(0.0f), y(0.0f) , z(0.0f) { memoryBlock = new int[5]; }
	Vector3(float scalar) :x(scalar), y(scalar), z(scalar) {
		memoryBlock = new int[5];
	}
	Vector3 (float x, float y, float z): x(x), y(y), z(z){ memoryBlock = new int[5]; }

	Vector3(const Vector3& other) = delete; /* {
		std::cout << "Copied"<<std::endl;
		x = other.x;
		y = other.y;
		z = other.z;

	}*/



	Vector3(Vector3&& other): x(other.x), y(other.y), z(other.z) {
		std::cout << "Moved" << std::endl;
		memoryBlock = other.memoryBlock;
		other.memoryBlock = nullptr;
	}

	~Vector3() {
		std::cout << "Destoryed" << std::endl;
		
		//::operator delete(memoryBlock, sizeof(int));
		delete[] memoryBlock;
	}

	Vector3& operator=(Vector3& other) {
		std::cout << "Copied" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		memoryBlock = other.memoryBlock;
		other.memoryBlock = nullptr;
		return *this;
	}
	Vector3& operator=(Vector3&& other) {
		std::cout << "Moved" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3& operator=(const Vector3& other) {
		std::cout << "Copied" << std::endl;
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
			delete[] memoryBlock;
			memoryBlock = new int[5];
			std::memcpy(memoryBlock, other.memoryBlock, 5 * sizeof(int));
		}
		return *this;
	}



};


template <typename T>
class Vector {
private:
	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
	
	void reAlloca(size_t new_capacity) {
		if (m_capacity != new_capacity) {
			//create a new block of memory
			T* new_block = (T*)::operator new( new_capacity * sizeof(T) );

			if (m_size > new_capacity)
				m_size = new_capacity;
			// move the data
			std::move(m_data, m_data + std::min(m_size, new_capacity), new_block);
			
			for (int i = 0; i < m_size; i++) {
				m_data[i].~T();
			}

			//delete[] m_data;
			::operator delete( m_data, m_capacity * sizeof(T) );
			m_data = nullptr;
			m_data = new_block;
			m_capacity = new_capacity;
			m_size = std::min(new_capacity, m_size);
		}
		

	}

public:

	Vector() {
		reAlloca(3);
	}

	~Vector() {
		for (int i = 0; i < m_size; i++) {
			m_data[i].~T();
		}
		::operator delete(m_data, m_capacity * sizeof(T));
	}

	void pushback(const T& value) {
		// Check if we need to reallocate
		if (m_size >= m_capacity)
			reAlloca(m_capacity + m_capacity / 2);

		//adding the value
		m_data[m_size] = value;
		m_size++;
	}
	void pushback(T&& value) {
		// Check if we need to reallocate
		if (m_size >= m_capacity)
			reAlloca(m_capacity + m_capacity / 2);

		//adding the value
		m_data[m_size] = std::move(value);
		//new (&newData[i]) T(std::move(m_Data[i]));
		m_size++;
	}

	template<typename... Args>
	T& emplaceBack(Args&&... args) {
		if (m_size >= m_capacity)
			reAlloca(m_capacity + m_capacity / 2);
		new(&m_data[m_size]) T(std::forward<Args>(args)...);
		//data[m_size] = T(std::forward<Args>(args)...);
		return m_data[m_size++];
	}

	void reserve(size_t new_size) {
		reAlloca(new_size);
	}

	size_t size() const { return m_size;  }

	void PopBack() {
		if (m_size > 0) {
			m_size--;
			m_data[m_size].~T();
		}

	}

	void clear() {
		for (int i = 0; i < m_size; i++) {
			m_data[i].~T();
		}
		m_size = 0;
	}

	void insert(unsigned short int index) {
		if (index >= m_size) 
			std::cout << "Warning! You are trying to access an invalid index" << std::endl;
		
		m_size++;
		if (m_size > m_capacity) {
			reAlloca(m_capacity + m_capacity / 2);
		}

		
	}

	const T& operator[](size_t index) const {
		if (index >= m_size) {
			//assert
			std::cout << "Warning! You are trying to access an invalid index"<<std::endl;
		}

		return m_data[index];
	}

	T& operator[](size_t index){
		return m_data[index];
	}


};

template <typename T>
void printVector(const Vector<T>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i]<<'\n';
	std::cout << std::endl;

}

template <>
void printVector(const Vector<Vector3>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i].x<<", " << vector[i].y << ", " << vector[i].z  << '\n';
	std::cout << std::endl;

}


int mainvector() {
	
		Vector<Vector3> vector;
		vector.reserve(3);

		vector.pushback(Vector3(1.0f));
		vector.emplaceBack(4.0f, 5.0f, 6.0f);
		vector.emplaceBack(7, 8, 9);
		printVector(vector);
		vector.PopBack();
		printVector(vector);
		vector.clear();
		printVector(vector);

	
	std::cin.get();
	return 0;
}