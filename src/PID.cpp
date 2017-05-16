#include "PID.h"
#include <sys/time.h>
#include <iostream>
/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp2, double Ki2, double Kd2) {
	Kp = Kp2;
	Ki = Ki2;
	Kd = Kd2;

	d_error = 0;
	p_error = 0;
	i_error = 0;
}

void PID::UpdateError(double cte) {
	// struct timeval tp;
	// gettimeofday(&tp, NULL);
	// long int current_t = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	p_error = cte;
	i_error += cte;
	d_error = (cte - prev_cte);
	prev_cte = cte;

}

double PID::TotalError() {
	return Kp * p_error + Kd * d_error + Ki * i_error;

}

