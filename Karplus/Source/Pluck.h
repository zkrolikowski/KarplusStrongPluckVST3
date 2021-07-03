/******************************************************************************/
/*!
\file   KarpusSynth.h
\author Zack Krolikowksi
\date   6/28/2021
*/
/******************************************************************************/

#pragma once

#include "AllPass.h"
#include "LowPass.h"

static constexpr double PI = 3.141592653589793238462643;

template<typename T>
class Pluck
{
public:
	Pluck(T R) : D(0),
		L(0),
		delta(0),
		a(0),
		r(0),
		R_L(0),
		lowPass(0),
		allPass(0),
		sampleRate(R)
	{
		delay.push(0);
	}

	void StartNote(T f, T decay)
	{
		D = sampleRate / f;
		L = std::floor(D - 0.5f);
		delta = (D - 0.5f) - L;
		a = static_cast<T>((std::sin(PI * f / sampleRate * (1 - delta))) / (std::sin(PI * f / sampleRate * (1 + delta))));
		r = decay;
		R_L = std::pow(r, L);
		
		lowPass.SetCutoff(r);
		lowPass.Clear();

		allPass.SetPivot(a);
		allPass.Clear();

		delay = std::queue<T>();
			
		for (int i = 0; i < L; ++i)
			delay.push(0);

	}
	
	T operator()(T x)
	{
		T y_l = delay.front();
		delay.pop();

		T y = x + (y_l * R_L);
		y = lowPass(y);
		y = allPass(y);

		delay.push(y);
		return y;

	}

private:
	T D, L, delta, a, r, R_L, sampleRate;
	LowPass<T> lowPass;
	AllPass<T> allPass;
	std::queue<T> delay;
};
