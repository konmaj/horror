// Konrad Majewski, Marcin Wawerka
#ifndef SMALLTOWN_H_
#define SMALLTOWN_H_

#include "citizen.h"
#include "monster.h"

#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

// TODO Fibonacci numbers class

template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
	private:
		M monster_;
		U time_;
		std::tuple<C...> citizens_;
		size_t aliveCounter;

		template<size_t i = 0>
		typename std::enable_if_t<i < sizeof...(C), int> countAliveCitizens() {
			if (std::get<i>(citizens_).getHealth() != 0) {
				return 1 + countAliveCitizens<i + 1>();
			}
			else {
				return countAliveCitizens<i + 1>();
			}
		}

		template<size_t i = 0>
		typename std::enable_if_t<i == sizeof...(C), int> countAliveCitizens() {
			return 0;
		}


		template<size_t i = 0>
		typename std::enable_if_t<i < sizeof...(C), void> attackCitizens() {
			attack(monster_, std::get<i>(citizens_));
			attackCitizens<i + 1>();
		}

		template<size_t i = 0>
		typename std::enable_if_t<i == sizeof...(C), void> attackCitizens() {}

  	public:
		SmallTown(const M &monster, const C&... citizens)
				: monster_(monster), time_(t0), citizens_(citizens...) {
			static_assert(0 <= t0 && t0 <= t1, "INCORRECT TIME VALUES");

			aliveCounter = countAliveCitizens();
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
				attackCitizens();
				aliveCounter = countAliveCitizens();
			}
			time_ = (time_ + timeStep) % t1;
		}
};

#endif //SMALLTOWN_H_
