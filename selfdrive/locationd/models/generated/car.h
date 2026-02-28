#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_5406805406734011165);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4305502187180093242);
void car_H_mod_fun(double *state, double *out_4874777254997497173);
void car_f_fun(double *state, double dt, double *out_2473795147483424885);
void car_F_fun(double *state, double dt, double *out_2855864808163184136);
void car_h_25(double *state, double *unused, double *out_2794280426416441853);
void car_H_25(double *state, double *unused, double *out_5963824365652588725);
void car_h_24(double *state, double *unused, double *out_6719804483310724611);
void car_H_24(double *state, double *unused, double *out_2405898766850265589);
void car_h_30(double *state, double *unused, double *out_5742006416771926814);
void car_H_30(double *state, double *unused, double *out_3445491407145340098);
void car_h_26(double *state, double *unused, double *out_8346411737580624465);
void car_H_26(double *state, double *unused, double *out_2659298395891788124);
void car_h_27(double *state, double *unused, double *out_5330586545910796349);
void car_H_27(double *state, double *unused, double *out_1221897335961396881);
void car_h_29(double *state, double *unused, double *out_6345322301448404331);
void car_H_29(double *state, double *unused, double *out_2935260062830947914);
void car_h_28(double *state, double *unused, double *out_5860013810705303558);
void car_H_28(double *state, double *unused, double *out_8017659079900478488);
void car_h_31(double *state, double *unused, double *out_8881628420942758827);
void car_H_31(double *state, double *unused, double *out_5933178403775628297);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}