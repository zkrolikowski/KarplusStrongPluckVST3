/******************************************************************************/
/*!
\file   KarpusSynth.h
\author Zack Krolikowksi
\date   6/28/2021
*/
/******************************************************************************/

#pragma once

template <typename T>
class AllPass
{
public:
	AllPass(T a) : a(a), x1(0), y1(0) {}

	T operator()(T x)
	{
		T y = a * (x - y1) + x1;
		x1 = x;
		y1 = y;
		return y;
	}

	void SetPivot(T newPivot)
	{
		a = newPivot;
	}

	void Clear()
	{
		x1 = 0;
		y1 = 0;
	}

private:
	T a;
	T x1;
	T y1;
};

