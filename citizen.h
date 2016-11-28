// Konrad Majewski, Marcin Wawerka
#ifndef CITIZEN_H_
#define CITIZEN_H_

#include <assert.h>
#include <type_traits>
#include <algorithm>

template <typename T, int minAge, int maxAge, bool isArmed,
	typename = typename std::enable_if_t<std::is_arithmetic<T>::value, T>>
class Citizen{
	private:
	
		T health;
		T age;
		T attackPower = 0;
		
		void checkAge(T age) {
			assert(age >= minAge && age <= maxAge);
		}
		
	public:
	
		using valueType = T;
		
		T getHealth() const {
			return health;
		}
		
		T getAge() const {
			return age;
		}
		
		template<typename Q = T, typename = typename std::enable_if_t<!isArmed, Q>>
		Citizen (T health_, T age_) 
				: health(health_), age(age_) {
			checkAge(age);
		}
		
		template<typename Q = T, typename = typename std::enable_if_t<isArmed, Q>>
		Citizen (T health_, T age_, T attackPower_) 
				: health(health_), age(age_), attackPower(attackPower_) {
			checkAge(age);
		}
		
		template<typename Q = T, typename = typename std::enable_if_t<isArmed, Q>>
		T getAttackPower() const {
			return attackPower;
		}
		
		void takeDamage(T damage) {
			health -= std::min(damage, health);
		}
}; 

template<typename T>
using Teenager = Citizen<T, 11, 17, false>;

template<typename T>
using Adult = Citizen<T ,18, 100, false>;

template<typename T>
using Sheriff = Citizen<T, 18, 100, true>;

#endif //CITIZEN_H_
