// Konrad Majewski, Marcin Wawerka
#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <string>
#include <iostream>
#include <cassert>

template <typename T, T minAge, T maxAge,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Citizen{
	private:
		T health;
		T age;
		
		T min (T a, T b) {
			return a < b ? a : b;
		}
		
	public:
		T getHealth() {
			return health;
		}
		
		T getAge() {
			return age;
		}
		
		Citizen (T health, T age) {
			assert(age >= minAge && age <= maxAge);
			this->health = health;
			this->age = age;
		}
		
		void takeDamage(T damage) {
			this->health -= min(damage, this->health);
		}
}; 

template<typename T>
using Teenager = Citizen<T, 11, 18>;

template<typename T>
using Adult = Citizen<T, 19, 100>;

#endif //CITIZEN_H_
