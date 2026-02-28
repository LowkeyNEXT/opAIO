#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5406805406734011165) {
   out_5406805406734011165[0] = delta_x[0] + nom_x[0];
   out_5406805406734011165[1] = delta_x[1] + nom_x[1];
   out_5406805406734011165[2] = delta_x[2] + nom_x[2];
   out_5406805406734011165[3] = delta_x[3] + nom_x[3];
   out_5406805406734011165[4] = delta_x[4] + nom_x[4];
   out_5406805406734011165[5] = delta_x[5] + nom_x[5];
   out_5406805406734011165[6] = delta_x[6] + nom_x[6];
   out_5406805406734011165[7] = delta_x[7] + nom_x[7];
   out_5406805406734011165[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4305502187180093242) {
   out_4305502187180093242[0] = -nom_x[0] + true_x[0];
   out_4305502187180093242[1] = -nom_x[1] + true_x[1];
   out_4305502187180093242[2] = -nom_x[2] + true_x[2];
   out_4305502187180093242[3] = -nom_x[3] + true_x[3];
   out_4305502187180093242[4] = -nom_x[4] + true_x[4];
   out_4305502187180093242[5] = -nom_x[5] + true_x[5];
   out_4305502187180093242[6] = -nom_x[6] + true_x[6];
   out_4305502187180093242[7] = -nom_x[7] + true_x[7];
   out_4305502187180093242[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4874777254997497173) {
   out_4874777254997497173[0] = 1.0;
   out_4874777254997497173[1] = 0;
   out_4874777254997497173[2] = 0;
   out_4874777254997497173[3] = 0;
   out_4874777254997497173[4] = 0;
   out_4874777254997497173[5] = 0;
   out_4874777254997497173[6] = 0;
   out_4874777254997497173[7] = 0;
   out_4874777254997497173[8] = 0;
   out_4874777254997497173[9] = 0;
   out_4874777254997497173[10] = 1.0;
   out_4874777254997497173[11] = 0;
   out_4874777254997497173[12] = 0;
   out_4874777254997497173[13] = 0;
   out_4874777254997497173[14] = 0;
   out_4874777254997497173[15] = 0;
   out_4874777254997497173[16] = 0;
   out_4874777254997497173[17] = 0;
   out_4874777254997497173[18] = 0;
   out_4874777254997497173[19] = 0;
   out_4874777254997497173[20] = 1.0;
   out_4874777254997497173[21] = 0;
   out_4874777254997497173[22] = 0;
   out_4874777254997497173[23] = 0;
   out_4874777254997497173[24] = 0;
   out_4874777254997497173[25] = 0;
   out_4874777254997497173[26] = 0;
   out_4874777254997497173[27] = 0;
   out_4874777254997497173[28] = 0;
   out_4874777254997497173[29] = 0;
   out_4874777254997497173[30] = 1.0;
   out_4874777254997497173[31] = 0;
   out_4874777254997497173[32] = 0;
   out_4874777254997497173[33] = 0;
   out_4874777254997497173[34] = 0;
   out_4874777254997497173[35] = 0;
   out_4874777254997497173[36] = 0;
   out_4874777254997497173[37] = 0;
   out_4874777254997497173[38] = 0;
   out_4874777254997497173[39] = 0;
   out_4874777254997497173[40] = 1.0;
   out_4874777254997497173[41] = 0;
   out_4874777254997497173[42] = 0;
   out_4874777254997497173[43] = 0;
   out_4874777254997497173[44] = 0;
   out_4874777254997497173[45] = 0;
   out_4874777254997497173[46] = 0;
   out_4874777254997497173[47] = 0;
   out_4874777254997497173[48] = 0;
   out_4874777254997497173[49] = 0;
   out_4874777254997497173[50] = 1.0;
   out_4874777254997497173[51] = 0;
   out_4874777254997497173[52] = 0;
   out_4874777254997497173[53] = 0;
   out_4874777254997497173[54] = 0;
   out_4874777254997497173[55] = 0;
   out_4874777254997497173[56] = 0;
   out_4874777254997497173[57] = 0;
   out_4874777254997497173[58] = 0;
   out_4874777254997497173[59] = 0;
   out_4874777254997497173[60] = 1.0;
   out_4874777254997497173[61] = 0;
   out_4874777254997497173[62] = 0;
   out_4874777254997497173[63] = 0;
   out_4874777254997497173[64] = 0;
   out_4874777254997497173[65] = 0;
   out_4874777254997497173[66] = 0;
   out_4874777254997497173[67] = 0;
   out_4874777254997497173[68] = 0;
   out_4874777254997497173[69] = 0;
   out_4874777254997497173[70] = 1.0;
   out_4874777254997497173[71] = 0;
   out_4874777254997497173[72] = 0;
   out_4874777254997497173[73] = 0;
   out_4874777254997497173[74] = 0;
   out_4874777254997497173[75] = 0;
   out_4874777254997497173[76] = 0;
   out_4874777254997497173[77] = 0;
   out_4874777254997497173[78] = 0;
   out_4874777254997497173[79] = 0;
   out_4874777254997497173[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2473795147483424885) {
   out_2473795147483424885[0] = state[0];
   out_2473795147483424885[1] = state[1];
   out_2473795147483424885[2] = state[2];
   out_2473795147483424885[3] = state[3];
   out_2473795147483424885[4] = state[4];
   out_2473795147483424885[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2473795147483424885[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2473795147483424885[7] = state[7];
   out_2473795147483424885[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2855864808163184136) {
   out_2855864808163184136[0] = 1;
   out_2855864808163184136[1] = 0;
   out_2855864808163184136[2] = 0;
   out_2855864808163184136[3] = 0;
   out_2855864808163184136[4] = 0;
   out_2855864808163184136[5] = 0;
   out_2855864808163184136[6] = 0;
   out_2855864808163184136[7] = 0;
   out_2855864808163184136[8] = 0;
   out_2855864808163184136[9] = 0;
   out_2855864808163184136[10] = 1;
   out_2855864808163184136[11] = 0;
   out_2855864808163184136[12] = 0;
   out_2855864808163184136[13] = 0;
   out_2855864808163184136[14] = 0;
   out_2855864808163184136[15] = 0;
   out_2855864808163184136[16] = 0;
   out_2855864808163184136[17] = 0;
   out_2855864808163184136[18] = 0;
   out_2855864808163184136[19] = 0;
   out_2855864808163184136[20] = 1;
   out_2855864808163184136[21] = 0;
   out_2855864808163184136[22] = 0;
   out_2855864808163184136[23] = 0;
   out_2855864808163184136[24] = 0;
   out_2855864808163184136[25] = 0;
   out_2855864808163184136[26] = 0;
   out_2855864808163184136[27] = 0;
   out_2855864808163184136[28] = 0;
   out_2855864808163184136[29] = 0;
   out_2855864808163184136[30] = 1;
   out_2855864808163184136[31] = 0;
   out_2855864808163184136[32] = 0;
   out_2855864808163184136[33] = 0;
   out_2855864808163184136[34] = 0;
   out_2855864808163184136[35] = 0;
   out_2855864808163184136[36] = 0;
   out_2855864808163184136[37] = 0;
   out_2855864808163184136[38] = 0;
   out_2855864808163184136[39] = 0;
   out_2855864808163184136[40] = 1;
   out_2855864808163184136[41] = 0;
   out_2855864808163184136[42] = 0;
   out_2855864808163184136[43] = 0;
   out_2855864808163184136[44] = 0;
   out_2855864808163184136[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2855864808163184136[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2855864808163184136[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2855864808163184136[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2855864808163184136[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2855864808163184136[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2855864808163184136[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2855864808163184136[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2855864808163184136[53] = -9.8000000000000007*dt;
   out_2855864808163184136[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2855864808163184136[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2855864808163184136[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2855864808163184136[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2855864808163184136[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2855864808163184136[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2855864808163184136[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2855864808163184136[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2855864808163184136[62] = 0;
   out_2855864808163184136[63] = 0;
   out_2855864808163184136[64] = 0;
   out_2855864808163184136[65] = 0;
   out_2855864808163184136[66] = 0;
   out_2855864808163184136[67] = 0;
   out_2855864808163184136[68] = 0;
   out_2855864808163184136[69] = 0;
   out_2855864808163184136[70] = 1;
   out_2855864808163184136[71] = 0;
   out_2855864808163184136[72] = 0;
   out_2855864808163184136[73] = 0;
   out_2855864808163184136[74] = 0;
   out_2855864808163184136[75] = 0;
   out_2855864808163184136[76] = 0;
   out_2855864808163184136[77] = 0;
   out_2855864808163184136[78] = 0;
   out_2855864808163184136[79] = 0;
   out_2855864808163184136[80] = 1;
}
void h_25(double *state, double *unused, double *out_2794280426416441853) {
   out_2794280426416441853[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5963824365652588725) {
   out_5963824365652588725[0] = 0;
   out_5963824365652588725[1] = 0;
   out_5963824365652588725[2] = 0;
   out_5963824365652588725[3] = 0;
   out_5963824365652588725[4] = 0;
   out_5963824365652588725[5] = 0;
   out_5963824365652588725[6] = 1;
   out_5963824365652588725[7] = 0;
   out_5963824365652588725[8] = 0;
}
void h_24(double *state, double *unused, double *out_6719804483310724611) {
   out_6719804483310724611[0] = state[4];
   out_6719804483310724611[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2405898766850265589) {
   out_2405898766850265589[0] = 0;
   out_2405898766850265589[1] = 0;
   out_2405898766850265589[2] = 0;
   out_2405898766850265589[3] = 0;
   out_2405898766850265589[4] = 1;
   out_2405898766850265589[5] = 0;
   out_2405898766850265589[6] = 0;
   out_2405898766850265589[7] = 0;
   out_2405898766850265589[8] = 0;
   out_2405898766850265589[9] = 0;
   out_2405898766850265589[10] = 0;
   out_2405898766850265589[11] = 0;
   out_2405898766850265589[12] = 0;
   out_2405898766850265589[13] = 0;
   out_2405898766850265589[14] = 1;
   out_2405898766850265589[15] = 0;
   out_2405898766850265589[16] = 0;
   out_2405898766850265589[17] = 0;
}
void h_30(double *state, double *unused, double *out_5742006416771926814) {
   out_5742006416771926814[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3445491407145340098) {
   out_3445491407145340098[0] = 0;
   out_3445491407145340098[1] = 0;
   out_3445491407145340098[2] = 0;
   out_3445491407145340098[3] = 0;
   out_3445491407145340098[4] = 1;
   out_3445491407145340098[5] = 0;
   out_3445491407145340098[6] = 0;
   out_3445491407145340098[7] = 0;
   out_3445491407145340098[8] = 0;
}
void h_26(double *state, double *unused, double *out_8346411737580624465) {
   out_8346411737580624465[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2659298395891788124) {
   out_2659298395891788124[0] = 0;
   out_2659298395891788124[1] = 0;
   out_2659298395891788124[2] = 0;
   out_2659298395891788124[3] = 0;
   out_2659298395891788124[4] = 0;
   out_2659298395891788124[5] = 0;
   out_2659298395891788124[6] = 0;
   out_2659298395891788124[7] = 1;
   out_2659298395891788124[8] = 0;
}
void h_27(double *state, double *unused, double *out_5330586545910796349) {
   out_5330586545910796349[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1221897335961396881) {
   out_1221897335961396881[0] = 0;
   out_1221897335961396881[1] = 0;
   out_1221897335961396881[2] = 0;
   out_1221897335961396881[3] = 1;
   out_1221897335961396881[4] = 0;
   out_1221897335961396881[5] = 0;
   out_1221897335961396881[6] = 0;
   out_1221897335961396881[7] = 0;
   out_1221897335961396881[8] = 0;
}
void h_29(double *state, double *unused, double *out_6345322301448404331) {
   out_6345322301448404331[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2935260062830947914) {
   out_2935260062830947914[0] = 0;
   out_2935260062830947914[1] = 1;
   out_2935260062830947914[2] = 0;
   out_2935260062830947914[3] = 0;
   out_2935260062830947914[4] = 0;
   out_2935260062830947914[5] = 0;
   out_2935260062830947914[6] = 0;
   out_2935260062830947914[7] = 0;
   out_2935260062830947914[8] = 0;
}
void h_28(double *state, double *unused, double *out_5860013810705303558) {
   out_5860013810705303558[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8017659079900478488) {
   out_8017659079900478488[0] = 1;
   out_8017659079900478488[1] = 0;
   out_8017659079900478488[2] = 0;
   out_8017659079900478488[3] = 0;
   out_8017659079900478488[4] = 0;
   out_8017659079900478488[5] = 0;
   out_8017659079900478488[6] = 0;
   out_8017659079900478488[7] = 0;
   out_8017659079900478488[8] = 0;
}
void h_31(double *state, double *unused, double *out_8881628420942758827) {
   out_8881628420942758827[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5933178403775628297) {
   out_5933178403775628297[0] = 0;
   out_5933178403775628297[1] = 0;
   out_5933178403775628297[2] = 0;
   out_5933178403775628297[3] = 0;
   out_5933178403775628297[4] = 0;
   out_5933178403775628297[5] = 0;
   out_5933178403775628297[6] = 0;
   out_5933178403775628297[7] = 0;
   out_5933178403775628297[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_5406805406734011165) {
  err_fun(nom_x, delta_x, out_5406805406734011165);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4305502187180093242) {
  inv_err_fun(nom_x, true_x, out_4305502187180093242);
}
void car_H_mod_fun(double *state, double *out_4874777254997497173) {
  H_mod_fun(state, out_4874777254997497173);
}
void car_f_fun(double *state, double dt, double *out_2473795147483424885) {
  f_fun(state,  dt, out_2473795147483424885);
}
void car_F_fun(double *state, double dt, double *out_2855864808163184136) {
  F_fun(state,  dt, out_2855864808163184136);
}
void car_h_25(double *state, double *unused, double *out_2794280426416441853) {
  h_25(state, unused, out_2794280426416441853);
}
void car_H_25(double *state, double *unused, double *out_5963824365652588725) {
  H_25(state, unused, out_5963824365652588725);
}
void car_h_24(double *state, double *unused, double *out_6719804483310724611) {
  h_24(state, unused, out_6719804483310724611);
}
void car_H_24(double *state, double *unused, double *out_2405898766850265589) {
  H_24(state, unused, out_2405898766850265589);
}
void car_h_30(double *state, double *unused, double *out_5742006416771926814) {
  h_30(state, unused, out_5742006416771926814);
}
void car_H_30(double *state, double *unused, double *out_3445491407145340098) {
  H_30(state, unused, out_3445491407145340098);
}
void car_h_26(double *state, double *unused, double *out_8346411737580624465) {
  h_26(state, unused, out_8346411737580624465);
}
void car_H_26(double *state, double *unused, double *out_2659298395891788124) {
  H_26(state, unused, out_2659298395891788124);
}
void car_h_27(double *state, double *unused, double *out_5330586545910796349) {
  h_27(state, unused, out_5330586545910796349);
}
void car_H_27(double *state, double *unused, double *out_1221897335961396881) {
  H_27(state, unused, out_1221897335961396881);
}
void car_h_29(double *state, double *unused, double *out_6345322301448404331) {
  h_29(state, unused, out_6345322301448404331);
}
void car_H_29(double *state, double *unused, double *out_2935260062830947914) {
  H_29(state, unused, out_2935260062830947914);
}
void car_h_28(double *state, double *unused, double *out_5860013810705303558) {
  h_28(state, unused, out_5860013810705303558);
}
void car_H_28(double *state, double *unused, double *out_8017659079900478488) {
  H_28(state, unused, out_8017659079900478488);
}
void car_h_31(double *state, double *unused, double *out_8881628420942758827) {
  h_31(state, unused, out_8881628420942758827);
}
void car_H_31(double *state, double *unused, double *out_5933178403775628297) {
  H_31(state, unused, out_5933178403775628297);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
