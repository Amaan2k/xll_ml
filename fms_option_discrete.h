// fms_option_discrete.h - Discrete distribution for option pricing
#pragma once
#include <cmath>
#include <valarray>
#include "fms_option.h"

namespace fms::option::discrete {
	template<class F = double, class S = double>
	class model : public option::base<F, S> {
		std::valarray<F> xi, pi; // P(X = x_i) = p_i

		void normalize()
		{
			pi /= pi.sum(); // pi.sum() == 1
			F Ex = (xi * pi).sum(); // mean
			xi -= Ex; // mean 0
			xi /= std::sqrt((xi * xi * pi).sum()); // variance 1
		}
	public:
		model(std::size_t n, const F* x, const F* p)
			: xi(x, n), pi(p, n)
		{
			normalize();
		}

		std::valarray<F> get_xi() const
		{
			return xi;
		}

		// kappa(s) = log E[exp(s X)] = log sum p_i exp(s x_i)
		S _cgf(S s) const override
		{
			return std::log((pi * std::exp(s * xi)).sum());
		}

		// E[exp(s X - kappa(s)) 1(X <= x) ]
		//   = sum_{x_i <= x} exp(s x_i - kappa(s)) pi_i
		F _cdf(F x, S s) const override
		{
			S kappa = _cgf(s);
			F result = 0;
			for (std::size_t i = 0; i < xi.size(); ++i) {
				if (xi[i] <= x) {
					result += std::exp(s * xi[i] - kappa) * pi[i];
				}
			}
			return result;
		}
	};
} // namespace fms::option::discrete
