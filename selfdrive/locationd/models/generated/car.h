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
void car_err_fun(double *nom_x, double *delta_x, double *out_9177242422690822598);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4717329060782240891);
void car_H_mod_fun(double *state, double *out_505794735897599614);
void car_f_fun(double *state, double dt, double *out_6642089061481146019);
void car_F_fun(double *state, double dt, double *out_1805696417807019095);
void car_h_25(double *state, double *unused, double *out_4749968379448791834);
void car_H_25(double *state, double *unused, double *out_6276645405458073544);
void car_h_24(double *state, double *unused, double *out_1732395222096527795);
void car_H_24(double *state, double *unused, double *out_4727424075262761752);
void car_h_30(double *state, double *unused, double *out_2710590384800096491);
void car_H_30(double *state, double *unused, double *out_7642402338123869874);
void car_h_26(double *state, double *unused, double *out_1767080531898434056);
void car_H_26(double *state, double *unused, double *out_8428595349377421848);
void car_h_27(double *state, double *unused, double *out_8695102426599914137);
void car_H_27(double *state, double *unused, double *out_5467639026323444963);
void car_h_29(double *state, double *unused, double *out_5747376436244429176);
void car_H_29(double *state, double *unused, double *out_8152633682438262058);
void car_h_28(double *state, double *unused, double *out_8392014116100267651);
void car_H_28(double *state, double *unused, double *out_3070234665368731484);
void car_h_31(double *state, double *unused, double *out_1112518851194769484);
void car_H_31(double *state, double *unused, double *out_7802387247144070372);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}