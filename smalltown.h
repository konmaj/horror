// Konrad Majewski, Marcin Wawerka
#ifndef SMALLTOWN_H_
#define SMALLTOWN_H_

#include "citizen.h"
#include "monster.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

template<typename M, typename U, U t0, U t1, typename... C>
class SmallTown {
	private:
		M monster_;
		U time_;
		std::tuple<C...> citizens_;
		size_t aliveCounter;
		
		static constexpr U fibonacci(size_t n) {
			U a = 1, b = 1;
			for (size_t i = 0; i < n; i++) {
				U c = a + b;
				a = b;
				b = c;
			}
			return a;
		}
		
		static constexpr size_t calcLimit() {
			size_t n = 0;
			while (fibonacci(n) <= t1) {
				n++;
			}
			return n;
		}
		
		template<size_t N, U... FibNums>
		static constexpr typename 
		std::enable_if_t<(N == sizeof...(FibNums)), std::array<U, N>> makeArray() {
			return std::array<U, N>{{FibNums...}};
		}

		template <size_t N, U... FibNums>
		static constexpr typename 
		std::enable_if_t<(N != sizeof...(FibNums)), std::array<U, N>> makeArray() {
			return makeArray<N, FibNums..., fibonacci(sizeof...(FibNums))>();
		}
		
		static const std::array<U, calcLimit()>& fibonacciNumbers() {
			static const std::array<U, calcLimit()> fibArray = makeArray<calcLimit()>();
			return fibArray;
		}

		template<size_t i = 0>
		typename std::enable_if_t<(i < sizeof...(C)), int> countAliveCitizens() {
			if (std::get<i>(citizens_).getHealth() != 0) {
				return 1 + countAliveCitizens<i + 1>();
			}
			else {
				return countAliveCitizens<i + 1>();
			}
		}

		template<size_t i = 0>
		typename std::enable_if_t<(i == sizeof...(C)), int> countAliveCitizens() {
			return 0;
		}


		template<size_t i = 0>
		typename std::enable_if_t<(i < sizeof...(C)), void> attackCitizens() {
			attack(monster_, std::get<i>(citizens_));
			attackCitizens<i + 1>();
		}

		template<size_t i = 0>
		typename std::enable_if_t<(i == sizeof...(C)), void> attackCitizens() {}

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
			else if (fibonacciNumbers().size() > 0 && std::binary_search(fibonacciNumbers().begin(), fibonacciNumbers().end(), time_)) {
				attackCitizens();
				aliveCounter = countAliveCitizens();
			}
			time_ = (time_ + timeStep) % (t1 + 1);
		}
};

#endif //SMALLTOWN_H_
