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
		
	public:
		
		const std::type_info& valueType = typeid(T);
		
		T getHealth() const{
			return health;
		}
		
		T getAttackPower() const {
			return attackPower;
		}
		
		Monster (T health, T attackPower) {
			this->health = health;
			this->attackPower = attackPower;
		}
		
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
void attack(M &monster, U &victim) {
	victim.takeDamage(monster.getAttackPower());
};

template<typename M, typename T>
void attack(M &monster, Sheriff<T> &victim) {
	victim.takeDamage(monster.getAttackPower());
	monster.takeDamage(victim.getAttackPower());
};
#endif //MONSTER_H_
