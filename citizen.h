// Konrad Majewski, Marcin Wawerka
#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <cassert>
#include <type_traits>
#include <algorithm>

template <typename T, T minAge, T maxAge, bool isArmed,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Citizen{
	private:
		T health;
		T age;
		T attackPower = 0;
		
	public:
		T getHealth() const{
			return health;
		}
		
		T getAge() const{
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
		T getAttackPower() const{
			return attackPower;
		}
		
		void takeDamage(T damage) {
			health -= std::min(damage, health);
		}
}; 

template<typename T>
using Teenager = Citizen<T, static_cast<T>(11), static_cast<T>(17), false>;

template<typename T>
using Adult = Citizen<T, static_cast<T>(18), static_cast<T>(100), false>;

template<typename T>
using Sheriff = Citizen<T, static_cast<T>(18), static_cast<T>(100), true>;

#endif //CITIZEN_H_
