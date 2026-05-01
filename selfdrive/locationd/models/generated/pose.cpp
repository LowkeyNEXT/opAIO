#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3379745892007797494) {
   out_3379745892007797494[0] = delta_x[0] + nom_x[0];
   out_3379745892007797494[1] = delta_x[1] + nom_x[1];
   out_3379745892007797494[2] = delta_x[2] + nom_x[2];
   out_3379745892007797494[3] = delta_x[3] + nom_x[3];
   out_3379745892007797494[4] = delta_x[4] + nom_x[4];
   out_3379745892007797494[5] = delta_x[5] + nom_x[5];
   out_3379745892007797494[6] = delta_x[6] + nom_x[6];
   out_3379745892007797494[7] = delta_x[7] + nom_x[7];
   out_3379745892007797494[8] = delta_x[8] + nom_x[8];
   out_3379745892007797494[9] = delta_x[9] + nom_x[9];
   out_3379745892007797494[10] = delta_x[10] + nom_x[10];
   out_3379745892007797494[11] = delta_x[11] + nom_x[11];
   out_3379745892007797494[12] = delta_x[12] + nom_x[12];
   out_3379745892007797494[13] = delta_x[13] + nom_x[13];
   out_3379745892007797494[14] = delta_x[14] + nom_x[14];
   out_3379745892007797494[15] = delta_x[15] + nom_x[15];
   out_3379745892007797494[16] = delta_x[16] + nom_x[16];
   out_3379745892007797494[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1703252081661007218) {
   out_1703252081661007218[0] = -nom_x[0] + true_x[0];
   out_1703252081661007218[1] = -nom_x[1] + true_x[1];
   out_1703252081661007218[2] = -nom_x[2] + true_x[2];
   out_1703252081661007218[3] = -nom_x[3] + true_x[3];
   out_1703252081661007218[4] = -nom_x[4] + true_x[4];
   out_1703252081661007218[5] = -nom_x[5] + true_x[5];
   out_1703252081661007218[6] = -nom_x[6] + true_x[6];
   out_1703252081661007218[7] = -nom_x[7] + true_x[7];
   out_1703252081661007218[8] = -nom_x[8] + true_x[8];
   out_1703252081661007218[9] = -nom_x[9] + true_x[9];
   out_1703252081661007218[10] = -nom_x[10] + true_x[10];
   out_1703252081661007218[11] = -nom_x[11] + true_x[11];
   out_1703252081661007218[12] = -nom_x[12] + true_x[12];
   out_1703252081661007218[13] = -nom_x[13] + true_x[13];
   out_1703252081661007218[14] = -nom_x[14] + true_x[14];
   out_1703252081661007218[15] = -nom_x[15] + true_x[15];
   out_1703252081661007218[16] = -nom_x[16] + true_x[16];
   out_1703252081661007218[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7865439658282295603) {
   out_7865439658282295603[0] = 1.0;
   out_7865439658282295603[1] = 0;
   out_7865439658282295603[2] = 0;
   out_7865439658282295603[3] = 0;
   out_7865439658282295603[4] = 0;
   out_7865439658282295603[5] = 0;
   out_7865439658282295603[6] = 0;
   out_7865439658282295603[7] = 0;
   out_7865439658282295603[8] = 0;
   out_7865439658282295603[9] = 0;
   out_7865439658282295603[10] = 0;
   out_7865439658282295603[11] = 0;
   out_7865439658282295603[12] = 0;
   out_7865439658282295603[13] = 0;
   out_7865439658282295603[14] = 0;
   out_7865439658282295603[15] = 0;
   out_7865439658282295603[16] = 0;
   out_7865439658282295603[17] = 0;
   out_7865439658282295603[18] = 0;
   out_7865439658282295603[19] = 1.0;
   out_7865439658282295603[20] = 0;
   out_7865439658282295603[21] = 0;
   out_7865439658282295603[22] = 0;
   out_7865439658282295603[23] = 0;
   out_7865439658282295603[24] = 0;
   out_7865439658282295603[25] = 0;
   out_7865439658282295603[26] = 0;
   out_7865439658282295603[27] = 0;
   out_7865439658282295603[28] = 0;
   out_7865439658282295603[29] = 0;
   out_7865439658282295603[30] = 0;
   out_7865439658282295603[31] = 0;
   out_7865439658282295603[32] = 0;
   out_7865439658282295603[33] = 0;
   out_7865439658282295603[34] = 0;
   out_7865439658282295603[35] = 0;
   out_7865439658282295603[36] = 0;
   out_7865439658282295603[37] = 0;
   out_7865439658282295603[38] = 1.0;
   out_7865439658282295603[39] = 0;
   out_7865439658282295603[40] = 0;
   out_7865439658282295603[41] = 0;
   out_7865439658282295603[42] = 0;
   out_7865439658282295603[43] = 0;
   out_7865439658282295603[44] = 0;
   out_7865439658282295603[45] = 0;
   out_7865439658282295603[46] = 0;
   out_7865439658282295603[47] = 0;
   out_7865439658282295603[48] = 0;
   out_7865439658282295603[49] = 0;
   out_7865439658282295603[50] = 0;
   out_7865439658282295603[51] = 0;
   out_7865439658282295603[52] = 0;
   out_7865439658282295603[53] = 0;
   out_7865439658282295603[54] = 0;
   out_7865439658282295603[55] = 0;
   out_7865439658282295603[56] = 0;
   out_7865439658282295603[57] = 1.0;
   out_7865439658282295603[58] = 0;
   out_7865439658282295603[59] = 0;
   out_7865439658282295603[60] = 0;
   out_7865439658282295603[61] = 0;
   out_7865439658282295603[62] = 0;
   out_7865439658282295603[63] = 0;
   out_7865439658282295603[64] = 0;
   out_7865439658282295603[65] = 0;
   out_7865439658282295603[66] = 0;
   out_7865439658282295603[67] = 0;
   out_7865439658282295603[68] = 0;
   out_7865439658282295603[69] = 0;
   out_7865439658282295603[70] = 0;
   out_7865439658282295603[71] = 0;
   out_7865439658282295603[72] = 0;
   out_7865439658282295603[73] = 0;
   out_7865439658282295603[74] = 0;
   out_7865439658282295603[75] = 0;
   out_7865439658282295603[76] = 1.0;
   out_7865439658282295603[77] = 0;
   out_7865439658282295603[78] = 0;
   out_7865439658282295603[79] = 0;
   out_7865439658282295603[80] = 0;
   out_7865439658282295603[81] = 0;
   out_7865439658282295603[82] = 0;
   out_7865439658282295603[83] = 0;
   out_7865439658282295603[84] = 0;
   out_7865439658282295603[85] = 0;
   out_7865439658282295603[86] = 0;
   out_7865439658282295603[87] = 0;
   out_7865439658282295603[88] = 0;
   out_7865439658282295603[89] = 0;
   out_7865439658282295603[90] = 0;
   out_7865439658282295603[91] = 0;
   out_7865439658282295603[92] = 0;
   out_7865439658282295603[93] = 0;
   out_7865439658282295603[94] = 0;
   out_7865439658282295603[95] = 1.0;
   out_7865439658282295603[96] = 0;
   out_7865439658282295603[97] = 0;
   out_7865439658282295603[98] = 0;
   out_7865439658282295603[99] = 0;
   out_7865439658282295603[100] = 0;
   out_7865439658282295603[101] = 0;
   out_7865439658282295603[102] = 0;
   out_7865439658282295603[103] = 0;
   out_7865439658282295603[104] = 0;
   out_7865439658282295603[105] = 0;
   out_7865439658282295603[106] = 0;
   out_7865439658282295603[107] = 0;
   out_7865439658282295603[108] = 0;
   out_7865439658282295603[109] = 0;
   out_7865439658282295603[110] = 0;
   out_7865439658282295603[111] = 0;
   out_7865439658282295603[112] = 0;
   out_7865439658282295603[113] = 0;
   out_7865439658282295603[114] = 1.0;
   out_7865439658282295603[115] = 0;
   out_7865439658282295603[116] = 0;
   out_7865439658282295603[117] = 0;
   out_7865439658282295603[118] = 0;
   out_7865439658282295603[119] = 0;
   out_7865439658282295603[120] = 0;
   out_7865439658282295603[121] = 0;
   out_7865439658282295603[122] = 0;
   out_7865439658282295603[123] = 0;
   out_7865439658282295603[124] = 0;
   out_7865439658282295603[125] = 0;
   out_7865439658282295603[126] = 0;
   out_7865439658282295603[127] = 0;
   out_7865439658282295603[128] = 0;
   out_7865439658282295603[129] = 0;
   out_7865439658282295603[130] = 0;
   out_7865439658282295603[131] = 0;
   out_7865439658282295603[132] = 0;
   out_7865439658282295603[133] = 1.0;
   out_7865439658282295603[134] = 0;
   out_7865439658282295603[135] = 0;
   out_7865439658282295603[136] = 0;
   out_7865439658282295603[137] = 0;
   out_7865439658282295603[138] = 0;
   out_7865439658282295603[139] = 0;
   out_7865439658282295603[140] = 0;
   out_7865439658282295603[141] = 0;
   out_7865439658282295603[142] = 0;
   out_7865439658282295603[143] = 0;
   out_7865439658282295603[144] = 0;
   out_7865439658282295603[145] = 0;
   out_7865439658282295603[146] = 0;
   out_7865439658282295603[147] = 0;
   out_7865439658282295603[148] = 0;
   out_7865439658282295603[149] = 0;
   out_7865439658282295603[150] = 0;
   out_7865439658282295603[151] = 0;
   out_7865439658282295603[152] = 1.0;
   out_7865439658282295603[153] = 0;
   out_7865439658282295603[154] = 0;
   out_7865439658282295603[155] = 0;
   out_7865439658282295603[156] = 0;
   out_7865439658282295603[157] = 0;
   out_7865439658282295603[158] = 0;
   out_7865439658282295603[159] = 0;
   out_7865439658282295603[160] = 0;
   out_7865439658282295603[161] = 0;
   out_7865439658282295603[162] = 0;
   out_7865439658282295603[163] = 0;
   out_7865439658282295603[164] = 0;
   out_7865439658282295603[165] = 0;
   out_7865439658282295603[166] = 0;
   out_7865439658282295603[167] = 0;
   out_7865439658282295603[168] = 0;
   out_7865439658282295603[169] = 0;
   out_7865439658282295603[170] = 0;
   out_7865439658282295603[171] = 1.0;
   out_7865439658282295603[172] = 0;
   out_7865439658282295603[173] = 0;
   out_7865439658282295603[174] = 0;
   out_7865439658282295603[175] = 0;
   out_7865439658282295603[176] = 0;
   out_7865439658282295603[177] = 0;
   out_7865439658282295603[178] = 0;
   out_7865439658282295603[179] = 0;
   out_7865439658282295603[180] = 0;
   out_7865439658282295603[181] = 0;
   out_7865439658282295603[182] = 0;
   out_7865439658282295603[183] = 0;
   out_7865439658282295603[184] = 0;
   out_7865439658282295603[185] = 0;
   out_7865439658282295603[186] = 0;
   out_7865439658282295603[187] = 0;
   out_7865439658282295603[188] = 0;
   out_7865439658282295603[189] = 0;
   out_7865439658282295603[190] = 1.0;
   out_7865439658282295603[191] = 0;
   out_7865439658282295603[192] = 0;
   out_7865439658282295603[193] = 0;
   out_7865439658282295603[194] = 0;
   out_7865439658282295603[195] = 0;
   out_7865439658282295603[196] = 0;
   out_7865439658282295603[197] = 0;
   out_7865439658282295603[198] = 0;
   out_7865439658282295603[199] = 0;
   out_7865439658282295603[200] = 0;
   out_7865439658282295603[201] = 0;
   out_7865439658282295603[202] = 0;
   out_7865439658282295603[203] = 0;
   out_7865439658282295603[204] = 0;
   out_7865439658282295603[205] = 0;
   out_7865439658282295603[206] = 0;
   out_7865439658282295603[207] = 0;
   out_7865439658282295603[208] = 0;
   out_7865439658282295603[209] = 1.0;
   out_7865439658282295603[210] = 0;
   out_7865439658282295603[211] = 0;
   out_7865439658282295603[212] = 0;
   out_7865439658282295603[213] = 0;
   out_7865439658282295603[214] = 0;
   out_7865439658282295603[215] = 0;
   out_7865439658282295603[216] = 0;
   out_7865439658282295603[217] = 0;
   out_7865439658282295603[218] = 0;
   out_7865439658282295603[219] = 0;
   out_7865439658282295603[220] = 0;
   out_7865439658282295603[221] = 0;
   out_7865439658282295603[222] = 0;
   out_7865439658282295603[223] = 0;
   out_7865439658282295603[224] = 0;
   out_7865439658282295603[225] = 0;
   out_7865439658282295603[226] = 0;
   out_7865439658282295603[227] = 0;
   out_7865439658282295603[228] = 1.0;
   out_7865439658282295603[229] = 0;
   out_7865439658282295603[230] = 0;
   out_7865439658282295603[231] = 0;
   out_7865439658282295603[232] = 0;
   out_7865439658282295603[233] = 0;
   out_7865439658282295603[234] = 0;
   out_7865439658282295603[235] = 0;
   out_7865439658282295603[236] = 0;
   out_7865439658282295603[237] = 0;
   out_7865439658282295603[238] = 0;
   out_7865439658282295603[239] = 0;
   out_7865439658282295603[240] = 0;
   out_7865439658282295603[241] = 0;
   out_7865439658282295603[242] = 0;
   out_7865439658282295603[243] = 0;
   out_7865439658282295603[244] = 0;
   out_7865439658282295603[245] = 0;
   out_7865439658282295603[246] = 0;
   out_7865439658282295603[247] = 1.0;
   out_7865439658282295603[248] = 0;
   out_7865439658282295603[249] = 0;
   out_7865439658282295603[250] = 0;
   out_7865439658282295603[251] = 0;
   out_7865439658282295603[252] = 0;
   out_7865439658282295603[253] = 0;
   out_7865439658282295603[254] = 0;
   out_7865439658282295603[255] = 0;
   out_7865439658282295603[256] = 0;
   out_7865439658282295603[257] = 0;
   out_7865439658282295603[258] = 0;
   out_7865439658282295603[259] = 0;
   out_7865439658282295603[260] = 0;
   out_7865439658282295603[261] = 0;
   out_7865439658282295603[262] = 0;
   out_7865439658282295603[263] = 0;
   out_7865439658282295603[264] = 0;
   out_7865439658282295603[265] = 0;
   out_7865439658282295603[266] = 1.0;
   out_7865439658282295603[267] = 0;
   out_7865439658282295603[268] = 0;
   out_7865439658282295603[269] = 0;
   out_7865439658282295603[270] = 0;
   out_7865439658282295603[271] = 0;
   out_7865439658282295603[272] = 0;
   out_7865439658282295603[273] = 0;
   out_7865439658282295603[274] = 0;
   out_7865439658282295603[275] = 0;
   out_7865439658282295603[276] = 0;
   out_7865439658282295603[277] = 0;
   out_7865439658282295603[278] = 0;
   out_7865439658282295603[279] = 0;
   out_7865439658282295603[280] = 0;
   out_7865439658282295603[281] = 0;
   out_7865439658282295603[282] = 0;
   out_7865439658282295603[283] = 0;
   out_7865439658282295603[284] = 0;
   out_7865439658282295603[285] = 1.0;
   out_7865439658282295603[286] = 0;
   out_7865439658282295603[287] = 0;
   out_7865439658282295603[288] = 0;
   out_7865439658282295603[289] = 0;
   out_7865439658282295603[290] = 0;
   out_7865439658282295603[291] = 0;
   out_7865439658282295603[292] = 0;
   out_7865439658282295603[293] = 0;
   out_7865439658282295603[294] = 0;
   out_7865439658282295603[295] = 0;
   out_7865439658282295603[296] = 0;
   out_7865439658282295603[297] = 0;
   out_7865439658282295603[298] = 0;
   out_7865439658282295603[299] = 0;
   out_7865439658282295603[300] = 0;
   out_7865439658282295603[301] = 0;
   out_7865439658282295603[302] = 0;
   out_7865439658282295603[303] = 0;
   out_7865439658282295603[304] = 1.0;
   out_7865439658282295603[305] = 0;
   out_7865439658282295603[306] = 0;
   out_7865439658282295603[307] = 0;
   out_7865439658282295603[308] = 0;
   out_7865439658282295603[309] = 0;
   out_7865439658282295603[310] = 0;
   out_7865439658282295603[311] = 0;
   out_7865439658282295603[312] = 0;
   out_7865439658282295603[313] = 0;
   out_7865439658282295603[314] = 0;
   out_7865439658282295603[315] = 0;
   out_7865439658282295603[316] = 0;
   out_7865439658282295603[317] = 0;
   out_7865439658282295603[318] = 0;
   out_7865439658282295603[319] = 0;
   out_7865439658282295603[320] = 0;
   out_7865439658282295603[321] = 0;
   out_7865439658282295603[322] = 0;
   out_7865439658282295603[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_544319655963680537) {
   out_544319655963680537[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_544319655963680537[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_544319655963680537[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_544319655963680537[3] = dt*state[12] + state[3];
   out_544319655963680537[4] = dt*state[13] + state[4];
   out_544319655963680537[5] = dt*state[14] + state[5];
   out_544319655963680537[6] = state[6];
   out_544319655963680537[7] = state[7];
   out_544319655963680537[8] = state[8];
   out_544319655963680537[9] = state[9];
   out_544319655963680537[10] = state[10];
   out_544319655963680537[11] = state[11];
   out_544319655963680537[12] = state[12];
   out_544319655963680537[13] = state[13];
   out_544319655963680537[14] = state[14];
   out_544319655963680537[15] = state[15];
   out_544319655963680537[16] = state[16];
   out_544319655963680537[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4635769855990584277) {
   out_4635769855990584277[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4635769855990584277[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4635769855990584277[2] = 0;
   out_4635769855990584277[3] = 0;
   out_4635769855990584277[4] = 0;
   out_4635769855990584277[5] = 0;
   out_4635769855990584277[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4635769855990584277[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4635769855990584277[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4635769855990584277[9] = 0;
   out_4635769855990584277[10] = 0;
   out_4635769855990584277[11] = 0;
   out_4635769855990584277[12] = 0;
   out_4635769855990584277[13] = 0;
   out_4635769855990584277[14] = 0;
   out_4635769855990584277[15] = 0;
   out_4635769855990584277[16] = 0;
   out_4635769855990584277[17] = 0;
   out_4635769855990584277[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4635769855990584277[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4635769855990584277[20] = 0;
   out_4635769855990584277[21] = 0;
   out_4635769855990584277[22] = 0;
   out_4635769855990584277[23] = 0;
   out_4635769855990584277[24] = 0;
   out_4635769855990584277[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4635769855990584277[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4635769855990584277[27] = 0;
   out_4635769855990584277[28] = 0;
   out_4635769855990584277[29] = 0;
   out_4635769855990584277[30] = 0;
   out_4635769855990584277[31] = 0;
   out_4635769855990584277[32] = 0;
   out_4635769855990584277[33] = 0;
   out_4635769855990584277[34] = 0;
   out_4635769855990584277[35] = 0;
   out_4635769855990584277[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4635769855990584277[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4635769855990584277[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4635769855990584277[39] = 0;
   out_4635769855990584277[40] = 0;
   out_4635769855990584277[41] = 0;
   out_4635769855990584277[42] = 0;
   out_4635769855990584277[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4635769855990584277[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4635769855990584277[45] = 0;
   out_4635769855990584277[46] = 0;
   out_4635769855990584277[47] = 0;
   out_4635769855990584277[48] = 0;
   out_4635769855990584277[49] = 0;
   out_4635769855990584277[50] = 0;
   out_4635769855990584277[51] = 0;
   out_4635769855990584277[52] = 0;
   out_4635769855990584277[53] = 0;
   out_4635769855990584277[54] = 0;
   out_4635769855990584277[55] = 0;
   out_4635769855990584277[56] = 0;
   out_4635769855990584277[57] = 1;
   out_4635769855990584277[58] = 0;
   out_4635769855990584277[59] = 0;
   out_4635769855990584277[60] = 0;
   out_4635769855990584277[61] = 0;
   out_4635769855990584277[62] = 0;
   out_4635769855990584277[63] = 0;
   out_4635769855990584277[64] = 0;
   out_4635769855990584277[65] = 0;
   out_4635769855990584277[66] = dt;
   out_4635769855990584277[67] = 0;
   out_4635769855990584277[68] = 0;
   out_4635769855990584277[69] = 0;
   out_4635769855990584277[70] = 0;
   out_4635769855990584277[71] = 0;
   out_4635769855990584277[72] = 0;
   out_4635769855990584277[73] = 0;
   out_4635769855990584277[74] = 0;
   out_4635769855990584277[75] = 0;
   out_4635769855990584277[76] = 1;
   out_4635769855990584277[77] = 0;
   out_4635769855990584277[78] = 0;
   out_4635769855990584277[79] = 0;
   out_4635769855990584277[80] = 0;
   out_4635769855990584277[81] = 0;
   out_4635769855990584277[82] = 0;
   out_4635769855990584277[83] = 0;
   out_4635769855990584277[84] = 0;
   out_4635769855990584277[85] = dt;
   out_4635769855990584277[86] = 0;
   out_4635769855990584277[87] = 0;
   out_4635769855990584277[88] = 0;
   out_4635769855990584277[89] = 0;
   out_4635769855990584277[90] = 0;
   out_4635769855990584277[91] = 0;
   out_4635769855990584277[92] = 0;
   out_4635769855990584277[93] = 0;
   out_4635769855990584277[94] = 0;
   out_4635769855990584277[95] = 1;
   out_4635769855990584277[96] = 0;
   out_4635769855990584277[97] = 0;
   out_4635769855990584277[98] = 0;
   out_4635769855990584277[99] = 0;
   out_4635769855990584277[100] = 0;
   out_4635769855990584277[101] = 0;
   out_4635769855990584277[102] = 0;
   out_4635769855990584277[103] = 0;
   out_4635769855990584277[104] = dt;
   out_4635769855990584277[105] = 0;
   out_4635769855990584277[106] = 0;
   out_4635769855990584277[107] = 0;
   out_4635769855990584277[108] = 0;
   out_4635769855990584277[109] = 0;
   out_4635769855990584277[110] = 0;
   out_4635769855990584277[111] = 0;
   out_4635769855990584277[112] = 0;
   out_4635769855990584277[113] = 0;
   out_4635769855990584277[114] = 1;
   out_4635769855990584277[115] = 0;
   out_4635769855990584277[116] = 0;
   out_4635769855990584277[117] = 0;
   out_4635769855990584277[118] = 0;
   out_4635769855990584277[119] = 0;
   out_4635769855990584277[120] = 0;
   out_4635769855990584277[121] = 0;
   out_4635769855990584277[122] = 0;
   out_4635769855990584277[123] = 0;
   out_4635769855990584277[124] = 0;
   out_4635769855990584277[125] = 0;
   out_4635769855990584277[126] = 0;
   out_4635769855990584277[127] = 0;
   out_4635769855990584277[128] = 0;
   out_4635769855990584277[129] = 0;
   out_4635769855990584277[130] = 0;
   out_4635769855990584277[131] = 0;
   out_4635769855990584277[132] = 0;
   out_4635769855990584277[133] = 1;
   out_4635769855990584277[134] = 0;
   out_4635769855990584277[135] = 0;
   out_4635769855990584277[136] = 0;
   out_4635769855990584277[137] = 0;
   out_4635769855990584277[138] = 0;
   out_4635769855990584277[139] = 0;
   out_4635769855990584277[140] = 0;
   out_4635769855990584277[141] = 0;
   out_4635769855990584277[142] = 0;
   out_4635769855990584277[143] = 0;
   out_4635769855990584277[144] = 0;
   out_4635769855990584277[145] = 0;
   out_4635769855990584277[146] = 0;
   out_4635769855990584277[147] = 0;
   out_4635769855990584277[148] = 0;
   out_4635769855990584277[149] = 0;
   out_4635769855990584277[150] = 0;
   out_4635769855990584277[151] = 0;
   out_4635769855990584277[152] = 1;
   out_4635769855990584277[153] = 0;
   out_4635769855990584277[154] = 0;
   out_4635769855990584277[155] = 0;
   out_4635769855990584277[156] = 0;
   out_4635769855990584277[157] = 0;
   out_4635769855990584277[158] = 0;
   out_4635769855990584277[159] = 0;
   out_4635769855990584277[160] = 0;
   out_4635769855990584277[161] = 0;
   out_4635769855990584277[162] = 0;
   out_4635769855990584277[163] = 0;
   out_4635769855990584277[164] = 0;
   out_4635769855990584277[165] = 0;
   out_4635769855990584277[166] = 0;
   out_4635769855990584277[167] = 0;
   out_4635769855990584277[168] = 0;
   out_4635769855990584277[169] = 0;
   out_4635769855990584277[170] = 0;
   out_4635769855990584277[171] = 1;
   out_4635769855990584277[172] = 0;
   out_4635769855990584277[173] = 0;
   out_4635769855990584277[174] = 0;
   out_4635769855990584277[175] = 0;
   out_4635769855990584277[176] = 0;
   out_4635769855990584277[177] = 0;
   out_4635769855990584277[178] = 0;
   out_4635769855990584277[179] = 0;
   out_4635769855990584277[180] = 0;
   out_4635769855990584277[181] = 0;
   out_4635769855990584277[182] = 0;
   out_4635769855990584277[183] = 0;
   out_4635769855990584277[184] = 0;
   out_4635769855990584277[185] = 0;
   out_4635769855990584277[186] = 0;
   out_4635769855990584277[187] = 0;
   out_4635769855990584277[188] = 0;
   out_4635769855990584277[189] = 0;
   out_4635769855990584277[190] = 1;
   out_4635769855990584277[191] = 0;
   out_4635769855990584277[192] = 0;
   out_4635769855990584277[193] = 0;
   out_4635769855990584277[194] = 0;
   out_4635769855990584277[195] = 0;
   out_4635769855990584277[196] = 0;
   out_4635769855990584277[197] = 0;
   out_4635769855990584277[198] = 0;
   out_4635769855990584277[199] = 0;
   out_4635769855990584277[200] = 0;
   out_4635769855990584277[201] = 0;
   out_4635769855990584277[202] = 0;
   out_4635769855990584277[203] = 0;
   out_4635769855990584277[204] = 0;
   out_4635769855990584277[205] = 0;
   out_4635769855990584277[206] = 0;
   out_4635769855990584277[207] = 0;
   out_4635769855990584277[208] = 0;
   out_4635769855990584277[209] = 1;
   out_4635769855990584277[210] = 0;
   out_4635769855990584277[211] = 0;
   out_4635769855990584277[212] = 0;
   out_4635769855990584277[213] = 0;
   out_4635769855990584277[214] = 0;
   out_4635769855990584277[215] = 0;
   out_4635769855990584277[216] = 0;
   out_4635769855990584277[217] = 0;
   out_4635769855990584277[218] = 0;
   out_4635769855990584277[219] = 0;
   out_4635769855990584277[220] = 0;
   out_4635769855990584277[221] = 0;
   out_4635769855990584277[222] = 0;
   out_4635769855990584277[223] = 0;
   out_4635769855990584277[224] = 0;
   out_4635769855990584277[225] = 0;
   out_4635769855990584277[226] = 0;
   out_4635769855990584277[227] = 0;
   out_4635769855990584277[228] = 1;
   out_4635769855990584277[229] = 0;
   out_4635769855990584277[230] = 0;
   out_4635769855990584277[231] = 0;
   out_4635769855990584277[232] = 0;
   out_4635769855990584277[233] = 0;
   out_4635769855990584277[234] = 0;
   out_4635769855990584277[235] = 0;
   out_4635769855990584277[236] = 0;
   out_4635769855990584277[237] = 0;
   out_4635769855990584277[238] = 0;
   out_4635769855990584277[239] = 0;
   out_4635769855990584277[240] = 0;
   out_4635769855990584277[241] = 0;
   out_4635769855990584277[242] = 0;
   out_4635769855990584277[243] = 0;
   out_4635769855990584277[244] = 0;
   out_4635769855990584277[245] = 0;
   out_4635769855990584277[246] = 0;
   out_4635769855990584277[247] = 1;
   out_4635769855990584277[248] = 0;
   out_4635769855990584277[249] = 0;
   out_4635769855990584277[250] = 0;
   out_4635769855990584277[251] = 0;
   out_4635769855990584277[252] = 0;
   out_4635769855990584277[253] = 0;
   out_4635769855990584277[254] = 0;
   out_4635769855990584277[255] = 0;
   out_4635769855990584277[256] = 0;
   out_4635769855990584277[257] = 0;
   out_4635769855990584277[258] = 0;
   out_4635769855990584277[259] = 0;
   out_4635769855990584277[260] = 0;
   out_4635769855990584277[261] = 0;
   out_4635769855990584277[262] = 0;
   out_4635769855990584277[263] = 0;
   out_4635769855990584277[264] = 0;
   out_4635769855990584277[265] = 0;
   out_4635769855990584277[266] = 1;
   out_4635769855990584277[267] = 0;
   out_4635769855990584277[268] = 0;
   out_4635769855990584277[269] = 0;
   out_4635769855990584277[270] = 0;
   out_4635769855990584277[271] = 0;
   out_4635769855990584277[272] = 0;
   out_4635769855990584277[273] = 0;
   out_4635769855990584277[274] = 0;
   out_4635769855990584277[275] = 0;
   out_4635769855990584277[276] = 0;
   out_4635769855990584277[277] = 0;
   out_4635769855990584277[278] = 0;
   out_4635769855990584277[279] = 0;
   out_4635769855990584277[280] = 0;
   out_4635769855990584277[281] = 0;
   out_4635769855990584277[282] = 0;
   out_4635769855990584277[283] = 0;
   out_4635769855990584277[284] = 0;
   out_4635769855990584277[285] = 1;
   out_4635769855990584277[286] = 0;
   out_4635769855990584277[287] = 0;
   out_4635769855990584277[288] = 0;
   out_4635769855990584277[289] = 0;
   out_4635769855990584277[290] = 0;
   out_4635769855990584277[291] = 0;
   out_4635769855990584277[292] = 0;
   out_4635769855990584277[293] = 0;
   out_4635769855990584277[294] = 0;
   out_4635769855990584277[295] = 0;
   out_4635769855990584277[296] = 0;
   out_4635769855990584277[297] = 0;
   out_4635769855990584277[298] = 0;
   out_4635769855990584277[299] = 0;
   out_4635769855990584277[300] = 0;
   out_4635769855990584277[301] = 0;
   out_4635769855990584277[302] = 0;
   out_4635769855990584277[303] = 0;
   out_4635769855990584277[304] = 1;
   out_4635769855990584277[305] = 0;
   out_4635769855990584277[306] = 0;
   out_4635769855990584277[307] = 0;
   out_4635769855990584277[308] = 0;
   out_4635769855990584277[309] = 0;
   out_4635769855990584277[310] = 0;
   out_4635769855990584277[311] = 0;
   out_4635769855990584277[312] = 0;
   out_4635769855990584277[313] = 0;
   out_4635769855990584277[314] = 0;
   out_4635769855990584277[315] = 0;
   out_4635769855990584277[316] = 0;
   out_4635769855990584277[317] = 0;
   out_4635769855990584277[318] = 0;
   out_4635769855990584277[319] = 0;
   out_4635769855990584277[320] = 0;
   out_4635769855990584277[321] = 0;
   out_4635769855990584277[322] = 0;
   out_4635769855990584277[323] = 1;
}
void h_4(double *state, double *unused, double *out_5952553398141575599) {
   out_5952553398141575599[0] = state[6] + state[9];
   out_5952553398141575599[1] = state[7] + state[10];
   out_5952553398141575599[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5971696922559280156) {
   out_5971696922559280156[0] = 0;
   out_5971696922559280156[1] = 0;
   out_5971696922559280156[2] = 0;
   out_5971696922559280156[3] = 0;
   out_5971696922559280156[4] = 0;
   out_5971696922559280156[5] = 0;
   out_5971696922559280156[6] = 1;
   out_5971696922559280156[7] = 0;
   out_5971696922559280156[8] = 0;
   out_5971696922559280156[9] = 1;
   out_5971696922559280156[10] = 0;
   out_5971696922559280156[11] = 0;
   out_5971696922559280156[12] = 0;
   out_5971696922559280156[13] = 0;
   out_5971696922559280156[14] = 0;
   out_5971696922559280156[15] = 0;
   out_5971696922559280156[16] = 0;
   out_5971696922559280156[17] = 0;
   out_5971696922559280156[18] = 0;
   out_5971696922559280156[19] = 0;
   out_5971696922559280156[20] = 0;
   out_5971696922559280156[21] = 0;
   out_5971696922559280156[22] = 0;
   out_5971696922559280156[23] = 0;
   out_5971696922559280156[24] = 0;
   out_5971696922559280156[25] = 1;
   out_5971696922559280156[26] = 0;
   out_5971696922559280156[27] = 0;
   out_5971696922559280156[28] = 1;
   out_5971696922559280156[29] = 0;
   out_5971696922559280156[30] = 0;
   out_5971696922559280156[31] = 0;
   out_5971696922559280156[32] = 0;
   out_5971696922559280156[33] = 0;
   out_5971696922559280156[34] = 0;
   out_5971696922559280156[35] = 0;
   out_5971696922559280156[36] = 0;
   out_5971696922559280156[37] = 0;
   out_5971696922559280156[38] = 0;
   out_5971696922559280156[39] = 0;
   out_5971696922559280156[40] = 0;
   out_5971696922559280156[41] = 0;
   out_5971696922559280156[42] = 0;
   out_5971696922559280156[43] = 0;
   out_5971696922559280156[44] = 1;
   out_5971696922559280156[45] = 0;
   out_5971696922559280156[46] = 0;
   out_5971696922559280156[47] = 1;
   out_5971696922559280156[48] = 0;
   out_5971696922559280156[49] = 0;
   out_5971696922559280156[50] = 0;
   out_5971696922559280156[51] = 0;
   out_5971696922559280156[52] = 0;
   out_5971696922559280156[53] = 0;
}
void h_10(double *state, double *unused, double *out_8956665038462042797) {
   out_8956665038462042797[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8956665038462042797[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8956665038462042797[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1835671244125414391) {
   out_1835671244125414391[0] = 0;
   out_1835671244125414391[1] = 9.8100000000000005*cos(state[1]);
   out_1835671244125414391[2] = 0;
   out_1835671244125414391[3] = 0;
   out_1835671244125414391[4] = -state[8];
   out_1835671244125414391[5] = state[7];
   out_1835671244125414391[6] = 0;
   out_1835671244125414391[7] = state[5];
   out_1835671244125414391[8] = -state[4];
   out_1835671244125414391[9] = 0;
   out_1835671244125414391[10] = 0;
   out_1835671244125414391[11] = 0;
   out_1835671244125414391[12] = 1;
   out_1835671244125414391[13] = 0;
   out_1835671244125414391[14] = 0;
   out_1835671244125414391[15] = 1;
   out_1835671244125414391[16] = 0;
   out_1835671244125414391[17] = 0;
   out_1835671244125414391[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1835671244125414391[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1835671244125414391[20] = 0;
   out_1835671244125414391[21] = state[8];
   out_1835671244125414391[22] = 0;
   out_1835671244125414391[23] = -state[6];
   out_1835671244125414391[24] = -state[5];
   out_1835671244125414391[25] = 0;
   out_1835671244125414391[26] = state[3];
   out_1835671244125414391[27] = 0;
   out_1835671244125414391[28] = 0;
   out_1835671244125414391[29] = 0;
   out_1835671244125414391[30] = 0;
   out_1835671244125414391[31] = 1;
   out_1835671244125414391[32] = 0;
   out_1835671244125414391[33] = 0;
   out_1835671244125414391[34] = 1;
   out_1835671244125414391[35] = 0;
   out_1835671244125414391[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1835671244125414391[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1835671244125414391[38] = 0;
   out_1835671244125414391[39] = -state[7];
   out_1835671244125414391[40] = state[6];
   out_1835671244125414391[41] = 0;
   out_1835671244125414391[42] = state[4];
   out_1835671244125414391[43] = -state[3];
   out_1835671244125414391[44] = 0;
   out_1835671244125414391[45] = 0;
   out_1835671244125414391[46] = 0;
   out_1835671244125414391[47] = 0;
   out_1835671244125414391[48] = 0;
   out_1835671244125414391[49] = 0;
   out_1835671244125414391[50] = 1;
   out_1835671244125414391[51] = 0;
   out_1835671244125414391[52] = 0;
   out_1835671244125414391[53] = 1;
}
void h_13(double *state, double *unused, double *out_4237705816007003230) {
   out_4237705816007003230[0] = state[3];
   out_4237705816007003230[1] = state[4];
   out_4237705816007003230[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4864415942833570531) {
   out_4864415942833570531[0] = 0;
   out_4864415942833570531[1] = 0;
   out_4864415942833570531[2] = 0;
   out_4864415942833570531[3] = 1;
   out_4864415942833570531[4] = 0;
   out_4864415942833570531[5] = 0;
   out_4864415942833570531[6] = 0;
   out_4864415942833570531[7] = 0;
   out_4864415942833570531[8] = 0;
   out_4864415942833570531[9] = 0;
   out_4864415942833570531[10] = 0;
   out_4864415942833570531[11] = 0;
   out_4864415942833570531[12] = 0;
   out_4864415942833570531[13] = 0;
   out_4864415942833570531[14] = 0;
   out_4864415942833570531[15] = 0;
   out_4864415942833570531[16] = 0;
   out_4864415942833570531[17] = 0;
   out_4864415942833570531[18] = 0;
   out_4864415942833570531[19] = 0;
   out_4864415942833570531[20] = 0;
   out_4864415942833570531[21] = 0;
   out_4864415942833570531[22] = 1;
   out_4864415942833570531[23] = 0;
   out_4864415942833570531[24] = 0;
   out_4864415942833570531[25] = 0;
   out_4864415942833570531[26] = 0;
   out_4864415942833570531[27] = 0;
   out_4864415942833570531[28] = 0;
   out_4864415942833570531[29] = 0;
   out_4864415942833570531[30] = 0;
   out_4864415942833570531[31] = 0;
   out_4864415942833570531[32] = 0;
   out_4864415942833570531[33] = 0;
   out_4864415942833570531[34] = 0;
   out_4864415942833570531[35] = 0;
   out_4864415942833570531[36] = 0;
   out_4864415942833570531[37] = 0;
   out_4864415942833570531[38] = 0;
   out_4864415942833570531[39] = 0;
   out_4864415942833570531[40] = 0;
   out_4864415942833570531[41] = 1;
   out_4864415942833570531[42] = 0;
   out_4864415942833570531[43] = 0;
   out_4864415942833570531[44] = 0;
   out_4864415942833570531[45] = 0;
   out_4864415942833570531[46] = 0;
   out_4864415942833570531[47] = 0;
   out_4864415942833570531[48] = 0;
   out_4864415942833570531[49] = 0;
   out_4864415942833570531[50] = 0;
   out_4864415942833570531[51] = 0;
   out_4864415942833570531[52] = 0;
   out_4864415942833570531[53] = 0;
}
void h_14(double *state, double *unused, double *out_3009295363005077584) {
   out_3009295363005077584[0] = state[6];
   out_3009295363005077584[1] = state[7];
   out_3009295363005077584[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2888908490263907860) {
   out_2888908490263907860[0] = 0;
   out_2888908490263907860[1] = 0;
   out_2888908490263907860[2] = 0;
   out_2888908490263907860[3] = 0;
   out_2888908490263907860[4] = 0;
   out_2888908490263907860[5] = 0;
   out_2888908490263907860[6] = 1;
   out_2888908490263907860[7] = 0;
   out_2888908490263907860[8] = 0;
   out_2888908490263907860[9] = 0;
   out_2888908490263907860[10] = 0;
   out_2888908490263907860[11] = 0;
   out_2888908490263907860[12] = 0;
   out_2888908490263907860[13] = 0;
   out_2888908490263907860[14] = 0;
   out_2888908490263907860[15] = 0;
   out_2888908490263907860[16] = 0;
   out_2888908490263907860[17] = 0;
   out_2888908490263907860[18] = 0;
   out_2888908490263907860[19] = 0;
   out_2888908490263907860[20] = 0;
   out_2888908490263907860[21] = 0;
   out_2888908490263907860[22] = 0;
   out_2888908490263907860[23] = 0;
   out_2888908490263907860[24] = 0;
   out_2888908490263907860[25] = 1;
   out_2888908490263907860[26] = 0;
   out_2888908490263907860[27] = 0;
   out_2888908490263907860[28] = 0;
   out_2888908490263907860[29] = 0;
   out_2888908490263907860[30] = 0;
   out_2888908490263907860[31] = 0;
   out_2888908490263907860[32] = 0;
   out_2888908490263907860[33] = 0;
   out_2888908490263907860[34] = 0;
   out_2888908490263907860[35] = 0;
   out_2888908490263907860[36] = 0;
   out_2888908490263907860[37] = 0;
   out_2888908490263907860[38] = 0;
   out_2888908490263907860[39] = 0;
   out_2888908490263907860[40] = 0;
   out_2888908490263907860[41] = 0;
   out_2888908490263907860[42] = 0;
   out_2888908490263907860[43] = 0;
   out_2888908490263907860[44] = 1;
   out_2888908490263907860[45] = 0;
   out_2888908490263907860[46] = 0;
   out_2888908490263907860[47] = 0;
   out_2888908490263907860[48] = 0;
   out_2888908490263907860[49] = 0;
   out_2888908490263907860[50] = 0;
   out_2888908490263907860[51] = 0;
   out_2888908490263907860[52] = 0;
   out_2888908490263907860[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_3379745892007797494) {
  err_fun(nom_x, delta_x, out_3379745892007797494);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1703252081661007218) {
  inv_err_fun(nom_x, true_x, out_1703252081661007218);
}
void pose_H_mod_fun(double *state, double *out_7865439658282295603) {
  H_mod_fun(state, out_7865439658282295603);
}
void pose_f_fun(double *state, double dt, double *out_544319655963680537) {
  f_fun(state,  dt, out_544319655963680537);
}
void pose_F_fun(double *state, double dt, double *out_4635769855990584277) {
  F_fun(state,  dt, out_4635769855990584277);
}
void pose_h_4(double *state, double *unused, double *out_5952553398141575599) {
  h_4(state, unused, out_5952553398141575599);
}
void pose_H_4(double *state, double *unused, double *out_5971696922559280156) {
  H_4(state, unused, out_5971696922559280156);
}
void pose_h_10(double *state, double *unused, double *out_8956665038462042797) {
  h_10(state, unused, out_8956665038462042797);
}
void pose_H_10(double *state, double *unused, double *out_1835671244125414391) {
  H_10(state, unused, out_1835671244125414391);
}
void pose_h_13(double *state, double *unused, double *out_4237705816007003230) {
  h_13(state, unused, out_4237705816007003230);
}
void pose_H_13(double *state, double *unused, double *out_4864415942833570531) {
  H_13(state, unused, out_4864415942833570531);
}
void pose_h_14(double *state, double *unused, double *out_3009295363005077584) {
  h_14(state, unused, out_3009295363005077584);
}
void pose_H_14(double *state, double *unused, double *out_2888908490263907860) {
  H_14(state, unused, out_2888908490263907860);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
