#include "ekf.hpp"

void ekf::get_jaccobian_f(){
  Eigen::MatrixXf jaccobian_f(16, 22);
  float t = ekf::get_delta();

  Eigen::MatrixXf s = ekf::state.state;
  Eigen::MatrixXf u = ekf::imu_output;

  //Eigen::MatrixXf b = ekf::bias;

  jaccobian_f << 1, 0, 0, t, 0, 0, 0.5*pow(t,2)*(2*s(8,0)*(-s(12,0) + u(2,0)) - 2*s(9,0)*(-s(11,0) + u(1,0))), 0.5*pow(t,2)*(2*s(8,0)*(-s(11,0) + u(1,0)) + 2*s(9,0)*(-s(12,0) + u(2,0))), 0.5*pow(t,2)*(2*s(6,0)*(-s(12,0) + u(2,0)) + 2*s(7,0)*(-s(11,0) + u(1,0)) - 4*s(8,0)*(-s(10,0) + u(0,0))), 0.5*pow(t,2)*(-2*s(6,0)*(-s(11,0) + u(1,0)) + 2*s(7,0)*(-s(12,0) + u(2,0)) - 4*s(9,0)*(-s(10,0) + u(0,0))), 0.5*pow(t,2)*(2*pow(s(8,0),2) + 2*pow(s(9,0),2) - 1), 0.5*pow(t,2)*(2*s(6,0)*s(9,0) - 2*s(7,0)*s(8,0)), 0.5*pow(t,2)*(-2*s(6,0)*s(8,0) - 2*s(7,0)*s(9,0)), 0, 0, 0, 0.5*pow(t,2)*(-2*pow(s(8,0),2) - 2*pow(s(9,0),2) + 1), 0.5*pow(t,2)*(-2*s(6,0)*s(9,0) + 2*s(7,0)*s(8,0)), 0.5*pow(t,2)*(2*s(6,0)*s(8,0) + 2*s(7,0)*s(9,0)), 0, 0, 0, //px
0, 1, 0, 0, t, 0, 0.5*pow(t,2)*(-2*s(7,0)*(-s(12,0) + u(2,0)) + 2*s(9,0)*(-s(10,0) + u(0,0))), 0.5*pow(t,2)*(-2*s(6,0)*(-s(12,0) + u(2,0)) - 4*s(7,0)*(-s(11,0) + u(1,0)) + 2*s(8,0)*(-s(10,0) + u(0,0))), 0.5*pow(t,2)*(2*s(7,0)*(-s(10,0) + u(0,0)) + 2*s(9,0)*(-s(12,0) + u(2,0))), 0.5*pow(t,2)*(2*s(6,0)*(-s(10,0) + u(0,0)) + 2*s(8,0)*(-s(12,0) + u(2,0)) - 4*s(9,0)*(-s(11,0) + u(1,0))), 0.5*pow(t,2)*(-2*s(6,0)*s(9,0) - 2*s(7,0)*s(8,0)), 0.5*pow(t,2)*(2*pow(s(7,0),2) + 2*pow(s(9,0),2) - 1), 0.5*pow(t,2)*(2*s(6,0)*s(7,0) - 2*s(8,0)*s(9,0)), 0, 0, 0, 0.5*pow(t,2)*(2*s(6,0)*s(9,0) + 2*s(7,0)*s(8,0)), 0.5*pow(t,2)*(-2*pow(s(7,0),2) - 2*pow(s(9,0),2) + 1), 0.5*pow(t,2)*(-2*s(6,0)*s(7,0) + 2*s(8,0)*s(9,0)), 0, 0, 0, //py
0, 0, 1, 0, 0, t, 0.5*pow(t,2)*(2*s(7,0)*(-s(11,0) + u(1,0)) - 2*s(8,0)*(-s(10,0) + u(0,0))), 0.5*pow(t,2)*(2*s(6,0)*(-s(11,0) + u(1,0)) - 4*s(7,0)*(-s(12,0) + u(2,0)) + 2*s(9,0)*(-s(10,0) + u(0,0))), 0.5*pow(t,2)*(-2*s(6,0)*(-s(10,0) + u(0,0)) - 4*s(8,0)*(-s(12,0) + u(2,0)) + 2*s(9,0)*(-s(11,0) + u(1,0))), 0.5*pow(t,2)*(2*s(7,0)*(-s(10,0) + u(0,0)) + 2*s(8,0)*(-s(11,0) + u(1,0))), 0.5*pow(t,2)*(2*s(6,0)*s(8,0) - 2*s(7,0)*s(9,0)), 0.5*pow(t,2)*(-2*s(6,0)*s(7,0) - 2*s(8,0)*s(9,0)), 0.5*pow(t,2)*(2*pow(s(7,0),2) + 2*pow(s(8,0),2) - 1), 0, 0, 0, 0.5*pow(t,2)*(-2*s(6,0)*s(8,0) + 2*s(7,0)*s(9,0)), 0.5*pow(t,2)*(2*s(6,0)*s(7,0) + 2*s(8,0)*s(9,0)), 0.5*pow(t,2)*(-2*pow(s(7,0),2) - 2*pow(s(8,0),2) + 1), 0, 0, 0, //px
0, 0, 0, 1, 0, 0, t*(2*s(8,0)*(-s(12,0) + u(2,0)) - 2*s(9,0)*(-s(11,0) + u(1,0))), t*(2*s(8,0)*(-s(11,0) + u(1,0)) + 2*s(9,0)*(-s(12,0) + u(2,0))), t*(2*s(6,0)*(-s(12,0) + u(2,0)) + 2*s(7,0)*(-s(11,0) + u(1,0)) - 4*s(8,0)*(-s(10,0) + u(0,0))), t*(-2*s(6,0)*(-s(11,0) + u(1,0)) + 2*s(7,0)*(-s(12,0) + u(2,0)) - 4*s(9,0)*(-s(10,0) + u(0,0))), t*(2*pow(s(8,0),2) + 2*pow(s(9,0),2) - 1), t*(2*s(6,0)*s(9,0) - 2*s(7,0)*s(8,0)), t*(-2*s(6,0)*s(8,0) - 2*s(7,0)*s(9,0)), 0, 0, 0, t*(-2*pow(s(8,0),2) - 2*pow(s(9,0),2) + 1), t*(-2*s(6,0)*s(9,0) + 2*s(7,0)*s(8,0)), t*(2*s(6,0)*s(8,0) + 2*s(7,0)*s(9,0)), 0, 0, 0, //vx
0, 0, 0, 0, 1, 0, t*(-2*s(7,0)*(-s(12,0) + u(2,0)) + 2*s(9,0)*(-s(10,0) + u(0,0))), t*(-2*s(6,0)*(-s(12,0) + u(2,0)) - 4*s(7,0)*(-s(11,0) + u(1,0)) + 2*s(8,0)*(-s(10,0) + u(0,0))), t*(2*s(7,0)*(-s(10,0) + u(0,0)) + 2*s(9,0)*(-s(12,0) + u(2,0))), t*(2*s(6,0)*(-s(10,0) + u(0,0)) + 2*s(8,0)*(-s(12,0) + u(2,0)) - 4*s(9,0)*(-s(11,0) + u(1,0))), t*(-2*s(6,0)*s(9,0) - 2*s(7,0)*s(8,0)), t*(2*pow(s(7,0),2) + 2*pow(s(9,0),2) - 1), t*(2*s(6,0)*s(7,0) - 2*s(8,0)*s(9,0)), 0, 0, 0, t*(2*s(6,0)*s(9,0) + 2*s(7,0)*s(8,0)), t*(-2*pow(s(7,0),2) - 2*pow(s(9,0),2) + 1), t*(-2*s(6,0)*s(7,0) + 2*s(8,0)*s(9,0)), 0, 0, 0, //vy
0, 0, 0, 0, 0, 1, t*(2*s(7,0)*(-s(11,0) + u(1,0)) - 2*s(8,0)*(-s(10,0) + u(0,0))), t*(2*s(6,0)*(-s(11,0) + u(1,0)) - 4*s(7,0)*(-s(12,0) + u(2,0)) + 2*s(9,0)*(-s(10,0) + u(0,0))), t*(-2*s(6,0)*(-s(10,0) + u(0,0)) - 4*s(8,0)*(-s(12,0) + u(2,0)) + 2*s(9,0)*(-s(11,0) + u(1,0))), t*(2*s(7,0)*(-s(10,0) + u(0,0)) + 2*s(8,0)*(-s(11,0) + u(1,0))), t*(2*s(6,0)*s(8,0) - 2*s(7,0)*s(9,0)), t*(-2*s(6,0)*s(7,0) - 2*s(8,0)*s(9,0)), t*(2*pow(s(7,0),2) + 2*pow(s(8,0),2) - 1), 0, 0, 0, t*(-2*s(6,0)*s(8,0) + 2*s(7,0)*s(9,0)), t*(2*s(6,0)*s(7,0) + 2*s(8,0)*s(9,0)), t*(-2*pow(s(7,0),2) - 2*pow(s(8,0),2) + 1), 0, 0, 0, //vz
0, 0, 0, 0, 0, 0, 1, -t*(-s(13,0) + u(3,0)), -t*(-s(14,0) + u(4,0)), -t*(-s(15,0) + u(5,0)), 0, 0, 0, s(7,0)*t, s(8,0)*t, s(9,0)*t, 0, 0, 0, -s(7,0)*t, -s(8,0)*t, -s(9,0)*t,//quartanion
0, 0, 0, 0, 0, 0, t*(-s(13,0) + u(3,0)), 1, -t*(-s(15,0) + u(5,0)), t*(-s(14,0) + u(4,0)), 0, 0, 0, -s(6,0)*t, -s(9,0)*t, s(8,0)*t, 0, 0, 0, s(6,0)*t, s(9,0)*t, -s(8,0)*t,//quartanion
0, 0, 0, 0, 0, 0, t*(-s(14,0) + u(4,0)), t*(-s(15,0) + u(5,0)), 1, -t*(-s(13,0) + u(3,0)), 0, 0, 0, s(9,0)*t, -s(6,0)*t, -s(7,0)*t, 0, 0, 0, -s(9,0)*t, s(6,0)*t, s(7,0)*t, //quartanion
0, 0, 0, 0, 0, 0, t*(-s(15,0) + u(5,0)), -t*(-s(14,0) + u(4,0)), t*(-s(13,0) + u(3,0)), 1, 0, 0, 0, -s(8,0)*t, s(7,0)*t, -s(6,0)*t, 0, 0, 0, s(8,0)*t, -s(7,0)*t, s(6,0)*t, //quartanion
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0;


  ekf::jaccobian_f = jaccobian_f;
}