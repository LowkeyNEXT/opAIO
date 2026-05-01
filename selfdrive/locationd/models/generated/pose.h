#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3379745892007797494);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1703252081661007218);
void pose_H_mod_fun(double *state, double *out_7865439658282295603);
void pose_f_fun(double *state, double dt, double *out_544319655963680537);
void pose_F_fun(double *state, double dt, double *out_4635769855990584277);
void pose_h_4(double *state, double *unused, double *out_5952553398141575599);
void pose_H_4(double *state, double *unused, double *out_5971696922559280156);
void pose_h_10(double *state, double *unused, double *out_8956665038462042797);
void pose_H_10(double *state, double *unused, double *out_1835671244125414391);
void pose_h_13(double *state, double *unused, double *out_4237705816007003230);
void pose_H_13(double *state, double *unused, double *out_4864415942833570531);
void pose_h_14(double *state, double *unused, double *out_3009295363005077584);
void pose_H_14(double *state, double *unused, double *out_2888908490263907860);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}