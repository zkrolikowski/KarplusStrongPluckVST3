/******************************************************************************/
/*!
\file   LowPass.h
\author Zack Krolikowksi
\date   6/28/2021
*/
/******************************************************************************/

#pragma once

template <typename T>
class LowPass
{
public:
	LowPass(T a1) : a1(a1), x1(0) {}

	T operator()(T x)
	{
		T out = static_cast<T>(0.5 * x + 0.5 * a1 * x1);

		x1 = x;

		return out;
	}

	void SetCutoff(T newCutoff)
	{
		a1 = newCutoff;
	}

	void Clear()
	{
		x1 = 0;
	}

private:
	T a1;
	T x1;
};
