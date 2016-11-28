// Konrad Majewski, Marcin Wawerka
#ifndef SMALLTOWN_H_
#define SMALLTOWN_H_

#include "citizen.h"
#include "monster.h"

#include <iostream>
#include <utility>

namespace {
	// TODO Fibonacci numbers class
	/*template<typename U, U limit>
	class FibonacciNumbers {

	};*/
}

template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
	private:
		M monster_;
		U time_;
		std::tuple<C...> citizens_;
		size_t aliveCounter;

		template<size_t i>
		void countAliveCitizens() {
			if (i > 0) {
				if (std::get<i - 1>(citizens_).getHealth > 0) {
					aliveCounter++;
				}
				countAliveCitizens<i - 1>();
			}
		}

		template<size_t i>
		void attackCitizens() {
			if (i > 0) {
				attack(monster_, std::get<i - 1>(citizens_));
				attackCitizens<i - 1>();
			}
		}

  	public:
		SmallTown(const M& monster, const C&... citizens)
				: monster_(monster), time_(t0), citizens_(citizens...) {
			static_assert(0 <= t0 && t0 <= t1, "INCORRECT TIME VALUES");

			countAliveCitizens<sizeof...(C)>();
		}

		std::tuple<std::string, decltype(monster_.getHealth()), size_t> getStatus() {
			return {typeid(monster_).name(), monster_.getHealth(), aliveCounter};
		}

		void tick(U timeStep) {
			if (monster_.getHealth() == 0) {
				if (aliveCounter == 0) {
					std::cout << "DRAW\n";
				}
				else {
					std::cout << "CITIZENS WON\n";
				}
			}
			else if (aliveCounter == 0) {
				std::cout << "MONSTER WON\n";
			}
			else if (time_ == 0) {	// TODO: Fibonacci numbers
				attackCitizens<sizeof...(C)>();
			}
			time_ = (time_ + timeStep) % t1;
		}
};

#endif //SMALLTOWN_H_
