#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_6488781494517591682);
void live_err_fun(double *nom_x, double *delta_x, double *out_2206567335740594794);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_7534223956631673677);
void live_H_mod_fun(double *state, double *out_267459291633431913);
void live_f_fun(double *state, double dt, double *out_7779820943618949475);
void live_F_fun(double *state, double dt, double *out_4570807537390999743);
void live_h_4(double *state, double *unused, double *out_5060985148067649094);
void live_H_4(double *state, double *unused, double *out_579774104657356683);
void live_h_9(double *state, double *unused, double *out_2613642194774319056);
void live_H_9(double *state, double *unused, double *out_820963751286947328);
void live_h_10(double *state, double *unused, double *out_5774953153959404874);
void live_H_10(double *state, double *unused, double *out_1089897536802106678);
void live_h_12(double *state, double *unused, double *out_3802137394676973531);
void live_H_12(double *state, double *unused, double *out_5599230512689318478);
void live_h_35(double *state, double *unused, double *out_8469603781095016121);
void live_H_35(double *state, double *unused, double *out_3946436162029964059);
void live_h_32(double *state, double *unused, double *out_2374127699736375452);
void live_H_32(double *state, double *unused, double *out_8161112191362210628);
void live_h_13(double *state, double *unused, double *out_6037962622334781032);
void live_H_13(double *state, double *unused, double *out_6334724335402959320);
void live_h_14(double *state, double *unused, double *out_2613642194774319056);
void live_H_14(double *state, double *unused, double *out_820963751286947328);
void live_h_33(double *state, double *unused, double *out_6501956064144544098);
void live_H_33(double *state, double *unused, double *out_7096993166668821663);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}