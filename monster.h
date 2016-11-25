// Konrad Majewski, Marcin Wawerka
#ifndef MONSTER_H_
#define MONSTER_H_

#include <typeinfo>
#include "citizen.h"

enum monst {
	mummy = 1,
	vampire = 2,
	zombie = 3
};

template <typename T, enum monst,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Monster{
	private:
		T health;
		T attackPower;
		
		T min (T a, T b) {
			return a < b ? a : b;
		}
		
	public:
		
		const std::type_info& valueType = typeid(T);
		
		T getHealth() {
			return health;
		}
		
		T getAttackPower() {
			return attackPower;
		}
		
		Monster (T health, T attackPower) {
			this->health = health;
			this->attackPower = attackPower;
		}
		
		void takeDamage(T damage) {
			health -= min(damage, health);
		}
}; 

template<typename T>
using Mummy = Monster<T, mummy>;

template<typename T>
using Zombie = Monster<T, zombie>;

template<typename T>
using Vampire = Monster<T, vampire>;

template<typename M, typename U>
void attack(M monster, U victim) {
	victim->takeDamage(monster->getAttackPower());
};
#endif //MONSTER_H_
