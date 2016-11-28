// Konrad Majewski, Marcin Wawerka
#ifndef MONSTER_H_
#define MONSTER_H_

#include <typeinfo>
#include <algorithm>
#include <type_traits>
#include "citizen.h"

enum monst {
	mummy = 1,
	vampire = 2,
	zombie = 3
};

template <typename T, enum monst,
	typename = typename std::enable_if_t<std::is_arithmetic<T>::value, T>>
class Monster{
	private:
		T health;
		T attackPower;
		
	public:
		
		using valueType = T;
		
		T getHealth() const{
			return health;
		}
		
		T getAttackPower() const {
			return attackPower;
		}
		
		Monster (T health_, T attackPower_) 
				: health(health_), attackPower(attackPower_){}
		
		void takeDamage(T damage) {
			health -= std::min(damage, health);
		}
}; 

template<typename T>
using Mummy = Monster<T, mummy>;

template<typename T>
using Zombie = Monster<T, zombie>;

template<typename T>
using Vampire = Monster<T, vampire>;

template<typename M, typename U>
void attack(const M &monster, U &victim) {
	victim.takeDamage(monster.getAttackPower());
};

template<typename M, typename U, 
	typename = typename std::enable_if_t
	<std::is_same<U, Sheriff<typename U::valueType>>::value>>
void attack(M &monster, U &victim) {
	victim.takeDamage(monster.getAttackPower());
	monster.takeDamage(victim.getAttackPower());
};
#endif //MONSTER_H_
