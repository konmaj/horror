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

template <typename T, enum monst, typename = typename
	std::enable_if_t<std::is_arithmetic<T>::value, T>>
class Monster {
private:
	T health_;
	T attackPower_;
	
public:
	using valueType = T;

	T getHealth() const {
		return health_;
	}

	T getAttackPower() const {
		return attackPower_;
	}

	Monster (T health, T attackPower) 
			: health_(health), attackPower_(attackPower) {}
	
	void takeDamage(T damage) {
		health_ -= std::min(damage, health_);
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

template<typename M, typename U, typename = typename 
	std::enable_if_t<std::is_same<U, Sheriff<typename U::valueType>>::value>>
void attack(M &monster, U &victim) {
	victim.takeDamage(monster.getAttackPower());
	monster.takeDamage(victim.getAttackPower());
};

#endif //MONSTER_H_
