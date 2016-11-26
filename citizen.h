// Konrad Majewski, Marcin Wawerka
#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <cassert>
#include <type_traits>

template <typename T, T minAge, T maxAge, bool isArmed,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Citizen{
	private:
		T health;
		T age;
		T attackPower = 0;
		
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
		
		template<typename Q = T, typename = typename std::enable_if<!isArmed, Q>::type>
		Citizen (T health, T age) {
			assert(age >= minAge && age <= maxAge);
			this->health = health;
			this->age = age;
		}
		
		template<typename Q = T, typename = typename std::enable_if<isArmed, Q>::type>
		Citizen (T health, T age, T attackPower) {
			assert(age >= minAge && age <= maxAge);
			this->health = health;
			this->age = age;
			this->attackPower = attackPower;
		}
		
		template<typename Q = T, typename = typename std::enable_if<isArmed, Q>::type>
		T getAttackPower() {
			return attackPower;
		}
		
		void takeDamage(T damage) {
			this->health -= min(damage, this->health);
		}
}; 

template<typename T>
using Teenager = Citizen<T, 11, 18, false>;

template<typename T>
using Adult = Citizen<T, 19, 100, false>;

template<typename T>
using Sheriff = Citizen<T, 19, 100, true>;

#endif //CITIZEN_H_
