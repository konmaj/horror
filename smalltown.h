// Konrad Majewski, Marcin Wawerka
#ifndef SMALLTOWN_H_
#define SMALLTOWN_H_

#include "citizen.h"
#include "monster.h"

#include <iostream>
#include <string>
#include <tuple>

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
		int countAliveCitizens() {
			int counter = 0;
			if (i + 1 < sizeof...(C)) {
				counter = countAliveCitizens<std::min(i + 1, (sizeof...(C)) - 1)>();
			}
			if (std::get<i>(citizens_).getHealth() != 0) {
				counter++;
			}
			return counter;
		}

		template<size_t i>
		void attackCitizens() {
			attack(monster_, std::get<i>(citizens_));
			if (i + 1 < sizeof...(C)) {
				attackCitizens<std::min(i + 1, (sizeof...(C)) - 1)>();
			}
		}

  	public:
		SmallTown(const M &monster, const C&... citizens)
				: monster_(monster), time_(t0), citizens_(citizens...) {
			static_assert(0 <= t0 && t0 <= t1, "INCORRECT TIME VALUES");

			aliveCounter = countAliveCitizens<0>();
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
				attackCitizens<0>();
				aliveCounter = countAliveCitizens<0>();
			}
			time_ = (time_ + timeStep) % t1;
		}
};

#endif //SMALLTOWN_H_
