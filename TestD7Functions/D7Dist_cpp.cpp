#pragma warning( disable : 4101) // for unreference local variables
#pragma warning( disable : 4100) //  unreferenced formal parameter
#pragma warning( disable : 4505) // unreferenced local function has been removed


#include "stdafx.h"
#ifndef D7DIST_H
#define D7DIST_H

#include <cmath>
#include <vector>

#include "D7DMS.h"
#include "D7Refl.h"
#include "D7Perp.h"
#include "D7Prj.h"

#include "D7Dist_cpp.h"
//
//  CD7Dist.c
//
//
//  Created by Herbert J. Bernstein and Lawrence C. Andrews on 3/04/17.
//
//

/* #define D7DIST_DEBUG */
/* #define D7DIST_NO_OUTER_PASS */


static const std::vector< void(*)(const double[], double[])> g_vDMS = GetDMSFunctions();
static const std::vector< void(*)(const double[], double[])> g_vperp = GetPerpFunctions();
static const std::vector< void(*)(const double[], double[])> g_vprj = GetProjectorFunctions();
static const std::vector< void(*)(const double[], double[])> g_vrefl = GetReflectionFunctions();



/* inward normals in D7 */
double D7N_1x[7] =
{ -0.7071067811865475, 0.7071067811865475, 0.0, 0.0, 0.0, 0.0, 0.0 };
double D7N_2x[7] =
{ 0.0, -0.7071067811865475, 0.7071067811865475, 0.0, 0.0, 0.0, 0.0 };
double D7N_3x[7] =
{ 0.0, 0.0, -0.7071067811865475, 0.7071067811865475, 0.0, 0.0, 0.0 };
double D7N_4x[7] =
{ -0.3273268353539886,  0.4364357804719848,  0.4364357804719848,
-0.3273268353539886, -0.4364357804719848,  0.3273268353539886,  0.3273268353539886 };
double D7N_5x[7] =
{ 0.4364357804719848, -0.3273268353539886, -0.3273268353539886,
0.4364357804719848, -0.4364357804719848,  0.3273268353539886,  0.3273268353539886 };
double D7N_6x[7] =
{ 0.4364357804719848, -0.3273268353539886,  0.4364357804719848,
-0.3273268353539886,  0.3273268353539886, -0.4364357804719848,  0.3273268353539886 };
double D7N_7x[7] =
{ -0.3273268353539886,  0.4364357804719848, -0.3273268353539886,
0.4364357804719848,  0.3273268353539886, -0.4364357804719848,  0.3273268353539886 };
double D7N_8x[7] =
{ 0.4364357804719848,  0.4364357804719848, -0.3273268353539886,
-0.3273268353539886,  0.3273268353539886,  0.3273268353539886, -0.4364357804719848 };
double D7N_9x[7] =
{ -0.3273268353539886, -0.3273268353539886,  0.4364357804719848,
0.4364357804719848,  0.3273268353539886,  0.3273268353539886, -0.4364357804719848 };



#define D7Refl_1 0
#define D7Refl_2 6
#define D7Refl_3 2
#define D7Refl_4 1
#define D7Refl_term -1

int D7Rord[24] = { 0,1,2,3,4,5,12,18,6,7,8,9,10,11,13,14,15,16,17,19,20,21,22,23 };


int D7Perm[24][8] = {

   /* D7Perm_1 {1,2,3,4,5,6,7},   Ident   OK */
   { D7Refl_1,D7Refl_term,0,0,0,0,0,0 },
   /* D7Perm_2 {1,2,4,3,6,5,7}            OK */
{ D7Refl_4,D7Refl_term,0,0,0,0,0,0 },
/* D7Perm_3 {1,3,2,4,5,7,6}            OK */
{ D7Refl_3,D7Refl_term,0,0,0,0,0,0 },
/* D7Perm_4 {1,3,4,2,7,5,6},           OK */
{ D7Refl_4,D7Refl_3,D7Refl_term,0,0,0,0,0 },
/* D7Perm_5 {1,4,2,3,6,7,5}            OK */
{ D7Refl_3,D7Refl_4,D7Refl_term,0,0,0,0,0 },
/* D7Perm_6  {1,4,3,2,7,6,5}           OK */
{ D7Refl_4,D7Refl_3,D7Refl_4,D7Refl_term,0,0,0,0 },
/* D7Perm_7  {3,1,2,4,7,5,6}           OK */
{ D7Refl_2,D7Refl_3,D7Refl_term,0,0,0,0,0 },
/* D7Perm_8  {4,1,2,3,7,6,5}           OK */
{ D7Refl_2,D7Refl_3,D7Refl_4,D7Refl_term,0,0,0,0 },
/* D7Perm_9  {2, 1, 3, 4}              OK */
{ D7Refl_2,D7Refl_term,0,0,0,0,0,0 },
/* D7Perm_10 {2, 1 ,4, 3}              OK */
{ D7Refl_4,D7Refl_2,D7Refl_term,0,0,0,0,0 },
/* D7Perm_11 {2, 3, 1, 4}              OK */
{ D7Refl_3,D7Refl_2,D7Refl_term,0,0,0,0,0 },
/* D7Perm_12 {2, 3, 4, 1}              OK */
{ D7Refl_4,D7Refl_3,D7Refl_2,D7Refl_term,0,0,0,0 },
/* D7Perm_13 {2, 4, 1, 3}              OK */
{ D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_term,0,0,0,0 },
/* D7Perm_14 {2, 4, 3, 1}              OK */
{ D7Refl_4,D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_term,0,0,0 },
/* D7Perm_15 {3, 1, 4, 2}              OK */
{ D7Refl_4,D7Refl_2,D7Refl_3,D7Refl_term,0,0,0,0 },
/* D7Perm_16 {3, 2, 1, 4}              OK */
{ D7Refl_3,D7Refl_2,D7Refl_3,D7Refl_term,0,0,0,0 },
/* D7Perm_17 {3, 2, 4, 1}              OK */
{ D7Refl_4,D7Refl_3,D7Refl_2,D7Refl_3,D7Refl_term,0,0,0 },
/* D7Perm_18 {3, 4, 1, 2}              OK */
{ D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_3,D7Refl_term,0,0,0 },
/* D7Perm_19 {3, 4, 2, 1}              OK */
{ D7Refl_4,D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_3,D7Refl_term,0,0 },
/* D7Perm_20 {4, 1, 3, 2}              OK */
{ D7Refl_2,D7Refl_4,D7Refl_3,D7Refl_4,D7Refl_term,0,0,0 },
/* D7Perm_21 {4, 2, 1, 3}              OK */
{ D7Refl_2,D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_term,0,0,0 },
/* D7Perm_22 {4, 2, 3, 1}              OK */
{ D7Refl_2,D7Refl_4,D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_term,0,0 },
/* D7Perm_23 {4, 3, 1, 2}              OK */
{ D7Refl_2,D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_3,D7Refl_term,0,0 },
/* D7Perm_24 {4, 3, 2, 1}              OK */
{ D7Refl_4,D7Refl_2,D7Refl_3,D7Refl_4,D7Refl_2,D7Refl_3,D7Refl_term,0 }
};



/* Test if outside D7 region
return 0 if outside */

int d7test(double g[7]) {
   int retval = 0;
   if (fabs(g[0] + g[1] + g[2] + g[3] - g[4] - g[5] - g[6]) > 1.e-5) retval |= 0x1;
   if (g[0] + g[3] < g[4] + 1.e-5) retval |= 0x2;
   if (g[1] + g[3] < g[5] + 1.e-5) retval |= 0x4;
   if (g[2] + g[3] < g[6] + 1.e-5) retval |= 0x8;
   if (g[1] + g[2] < g[4] + 1.e-5) retval |= 0x10;
   if (g[0] + g[2] < g[5] + 1.e-5) retval |= 0x20;
   if (g[0] + g[1] < g[6] + 1.e-5) retval |= 0x40;
   if (g[0] <  -1.e-5) retval |= 0x80;
   if (g[1] <  -1.e-5) retval |= 0x100;
   if (g[2] <  -1.e-5) retval |= 0x200;
   if (g[3] <  -1.e-5) retval |= 0x400;
   if (g[4] <  -1.e-5) retval |= 0x800;
   if (g[5] <  -1.e-5) retval |= 0x1000;
   if (g[6] <  -1.e-5) retval |= 0x2000;

   return retval;
}


/* Compute the dot product of 2 D7 vectors */

double d7dotprod(double v1[7], double v2[7]) {

   return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3] + v1[4] * v2[4] + v1[5] * v2[5] + v1[6] * v2[6];

}

#define CD7M_d7dotprod(v1,v2) \
    v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3]+v1[4]*v2[4]+v1[5]*v2[5]+v1[6]*v2[6]

#define CD7M_d7dotprod_byelem(v11,v12,v13,v14,v15,v16,v17,v21,v22,v23,v24,v25,v26,v27) \
    v11*v21+v12*v22+v13*v23+v14*v24+v15*v25+v16*v26+v17*v27


/* Compute the minimum dot product of minimal length of the dot products of 2 D7 vectors in all permutations */


double d71234dotprod(double v1[7], double v2[7]) {
   double trialval;
   double dtrial[24];
   int i;
   dtrial[0] = CD7M_d7dotprod_byelem(v1[0], v1[1], v1[2], v1[3], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[1] = CD7M_d7dotprod_byelem(v1[0], v1[1], v1[3], v1[2], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[2] = CD7M_d7dotprod_byelem(v1[0], v1[2], v1[1], v1[3], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[3] = CD7M_d7dotprod_byelem(v1[0], v1[2], v1[3], v1[1], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[4] = CD7M_d7dotprod_byelem(v1[0], v1[3], v1[1], v1[2], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[5] = CD7M_d7dotprod_byelem(v1[0], v1[3], v1[2], v1[1], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[6] = CD7M_d7dotprod_byelem(v1[1], v1[0], v1[2], v1[3], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[7] = CD7M_d7dotprod_byelem(v1[1], v1[0], v1[3], v1[2], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[8] = CD7M_d7dotprod_byelem(v1[1], v1[2], v1[0], v1[3], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[9] = CD7M_d7dotprod_byelem(v1[1], v1[2], v1[3], v1[0], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[10] = CD7M_d7dotprod_byelem(v1[1], v1[3], v1[0], v1[2], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[11] = CD7M_d7dotprod_byelem(v1[1], v1[3], v1[2], v1[0], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[12] = CD7M_d7dotprod_byelem(v1[2], v1[0], v1[1], v1[3], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[13] = CD7M_d7dotprod_byelem(v1[2], v1[0], v1[3], v1[1], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[14] = CD7M_d7dotprod_byelem(v1[2], v1[1], v1[0], v1[3], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[15] = CD7M_d7dotprod_byelem(v1[2], v1[1], v1[3], v1[0], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[16] = CD7M_d7dotprod_byelem(v1[2], v1[3], v1[0], v1[1], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[17] = CD7M_d7dotprod_byelem(v1[2], v1[3], v1[1], v1[0], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[18] = CD7M_d7dotprod_byelem(v1[3], v1[0], v1[1], v1[2], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[19] = CD7M_d7dotprod_byelem(v1[3], v1[0], v1[2], v1[1], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[20] = CD7M_d7dotprod_byelem(v1[3], v1[1], v1[0], v1[2], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[21] = CD7M_d7dotprod_byelem(v1[3], v1[1], v1[2], v1[0], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[22] = CD7M_d7dotprod_byelem(v1[3], v1[2], v1[0], v1[1], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[23] = CD7M_d7dotprod_byelem(v1[3], v1[2], v1[1], v1[0], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);

   trialval = dtrial[0];
   for (i = 1; i < 24; i++) if (trialval > fabs(dtrial[i])) trialval = dtrial[i];
   return (trialval);
}



/* Compute the simple Euclidean distance between 2 D7 vectors */

double d7eucldistsq(double v1[7], double v2[7]) {

   double vtemp;
   int ii;
   double distsq;

   distsq = 0.;

   for (ii = 0; ii < 7; ii++) {
      vtemp = v1[ii] - v2[ii];
      distsq += vtemp * vtemp;
   }
   return distsq;
}

double d7eucldist(double v1[7], double v2[6]) {

   return sqrt(d7eucldistsq(v1, v2));

}



#define CD7M_min2(a,b) (((a)<(b))?(a):(b))
#define CD7M_min3(a,b,c) ((CD7M_min2(a,b)<(c))?(CD7M_min2(a,b)):(c))
#define CD7M_min4(a,b,c,d) ((CD7M_min3(a,b,c)<(d))?(CD7M_min3(a,b,c)):(d))
#define CD7M_min5(a,b,c,d,e) ((CD7M_min4(a,b,c,d)<(e))?(CD7M_min4(a,b,c,d)):(e))
#define CD7M_min6(a,b,c,d,e,f) ((CD7M_min5(a,b,c,d,e)<(f))?(CD7M_min5(a,b,c,d,e)):(f))
#define CD7M_min7(a,b,c,d,e,f,g) ((CD7M_min6(a,b,c,d,e,f)<(g))?(CD7M_min6(a,b,c,d,e,f)):(g))
#define CD7M_min8(a,b,c,d,e,f,g,h) ((CD7M_min7(a,b,c,d,e,f,g)<(h))?(CD7M_min7(a,b,c,d,e,f,g)):(h))


/* Macro versions of distances */

#define CD7M_normsq(v) v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]+v[4]*v[4]+v[5]*v[5]
#define CD7M_norm(v) sqrt(CD7M_normsq(v))
#define CD7M_d7normsq(v) v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]+v[4]*v[4]+v[5]*v[5]+v[6]*v[6]
#define CD7M_d7norm(v) sqrt(CD7M_d7normsq(v))

#define CD7M_gdistsq(v1,v2) \
( \
(v1[0]-v2[0])*(v1[0]-v2[0])+\
(v1[1]-v2[1])*(v1[1]-v2[1])+\
(v1[2]-v2[2])*(v1[2]-v2[2])+\
(v1[3]-v2[3])*(v1[3]-v2[3])+\
(v1[4]-v2[4])*(v1[4]-v2[4])+\
(v1[5]-v2[5])*(v1[5]-v2[5]))

#define CD7M_gdist(v1,v2) sqrt(CD7M_gdistsq(v1,v2))

#define CD7M_d7eucldistsq(v1,v2) \
( \
(v1[0]-v2[0])*(v1[0]-v2[0])+\
(v1[1]-v2[1])*(v1[1]-v2[1])+\
(v1[2]-v2[2])*(v1[2]-v2[2])+\
(v1[3]-v2[3])*(v1[3]-v2[3])+\
(v1[4]-v2[4])*(v1[4]-v2[4])+\
(v1[5]-v2[5])*(v1[5]-v2[5])+\
(v1[6]-v2[6])*(v1[6]-v2[6])\
)

#define CD7M_d7eucldist(v1,v2) sqrt(CD7M_d7eucldistsq(v1,v2))






/*     Compute the best distance between 2 s6 vectors
allowing for permulations of d1, d2, d3, b4
*/

#define CD7M_d7eucldistsq_byelem(v11,v12,v13,v14,v15,v16,v17,v21,v22,v23,v24,v25,v26,v27) \
fabs((v11-v21)*(v11-v21)+(v12-v22)*(v12-v22)+(v13-v23)*(v13-v23) + \
(v14-v24)*(v14-v24)+(v15-v25)*(v15-v25)+(v16-v26)*(v16-v26) + (v16-v26)*(v16-v26))

#define CD7M_d7prods_byelem(v11,v12,v13,v14,v15,v16,v17,v21,v22,v23,v24,v25,v26,v27) \
2.*(v11*v21+v12*v22+v13*v23+v14*v24+v15*v25+v16*v26+v17*v27)

#define CD7M_d71234distsq(v1,v2) \
CD7M_min3(\
CD7M_min8(\
CD7M_d7eucldistsq_byelem(v1[0],v1[1],v1[2],v1[3],v1[4],v1[5],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[0],v1[1],v1[3],v1[2],v1[5],v1[4],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[0],v1[2],v1[1],v1[3],v1[4],v1[6],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[0],v1[2],v1[3],v1[1],v1[6],v1[4],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[0],v1[3],v1[1],v1[2],v1[5],v1[6],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[0],v1[3],v1[2],v1[1],v1[6],v1[5],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[2],v1[0],v1[1],v1[3],v1[6],v1[4],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[3],v1[0],v1[1],v1[2],v1[6],v1[5],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6])),\
CD7M_min8(\
CD7M_d7eucldistsq_byelem(v1[1],v1[0],v1[2],v1[3],v1[5],v1[4],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[1],v1[0],v1[3],v1[2],v1[4],v1[5],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[1],v1[2],v1[0],v1[3],v1[5],v1[6],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[1],v1[2],v1[3],v1[0],v1[6],v1[5],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[1],v1[3],v1[0],v1[2],v1[4],v1[6],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[1],v1[3],v1[2],v1[0],v1[6],v1[4],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[2],v1[0],v1[3],v1[1],v1[4],v1[6],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[2],v1[1],v1[0],v1[3],v1[6],v1[5],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6])),\
CD7M_min8(\
CD7M_d7eucldistsq_byelem(v1[2],v1[1],v1[3],v1[0],v1[5],v1[6],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[2],v1[3],v1[0],v1[1],v1[4],v1[5],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[2],v1[3],v1[1],v1[0],v1[5],v1[4],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[3],v1[0],v1[2],v1[1],v1[5],v1[6],v1[4],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[3],v1[1],v1[0],v1[2],v1[6],v1[4],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[3],v1[1],v1[2],v1[0],v1[4],v1[6],v1[5],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[3],v1[2],v1[0],v1[1],v1[5],v1[4],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6]),\
CD7M_d7eucldistsq_byelem(v1[3],v1[2],v1[1],v1[0],v1[4],v1[5],v1[6],\
v2[0],v2[1],v2[2],v2[3],v2[4],v2[5],v2[6])))

#define CD7M_d71234dist(v1,v2) sqrt(CD7M_d71234distsq(v1,v2))

double d71234distsq(double v1[7], double v2[7]) {
   double distsq;
   double dwnby;
   double dtrial[24];
   int i;
   distsq = v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2] + v1[3] * v1[3] + v1[4] * v1[4] + v1[5] * v1[5] + v1[6] * v1[6]
      + v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2] + v2[3] * v2[3] + v2[4] * v2[4] + v2[5] * v2[5] + v2[6] * v2[6];
   dtrial[0] = CD7M_d7prods_byelem(v1[0], v1[1], v1[2], v1[3], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[1] = CD7M_d7prods_byelem(v1[0], v1[1], v1[3], v1[2], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[2] = CD7M_d7prods_byelem(v1[0], v1[2], v1[1], v1[3], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[3] = CD7M_d7prods_byelem(v1[0], v1[2], v1[3], v1[1], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[4] = CD7M_d7prods_byelem(v1[0], v1[3], v1[1], v1[2], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[5] = CD7M_d7prods_byelem(v1[0], v1[3], v1[2], v1[1], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[6] = CD7M_d7prods_byelem(v1[1], v1[0], v1[2], v1[3], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[7] = CD7M_d7prods_byelem(v1[1], v1[0], v1[3], v1[2], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[8] = CD7M_d7prods_byelem(v1[1], v1[2], v1[0], v1[3], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[9] = CD7M_d7prods_byelem(v1[1], v1[2], v1[3], v1[0], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[10] = CD7M_d7prods_byelem(v1[1], v1[3], v1[0], v1[2], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[11] = CD7M_d7prods_byelem(v1[1], v1[3], v1[2], v1[0], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[12] = CD7M_d7prods_byelem(v1[2], v1[0], v1[1], v1[3], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[13] = CD7M_d7prods_byelem(v1[2], v1[0], v1[3], v1[1], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[14] = CD7M_d7prods_byelem(v1[2], v1[1], v1[0], v1[3], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[15] = CD7M_d7prods_byelem(v1[2], v1[1], v1[3], v1[0], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[16] = CD7M_d7prods_byelem(v1[2], v1[3], v1[0], v1[1], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[17] = CD7M_d7prods_byelem(v1[2], v1[3], v1[1], v1[0], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[18] = CD7M_d7prods_byelem(v1[3], v1[0], v1[1], v1[2], v1[6], v1[5], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[19] = CD7M_d7prods_byelem(v1[3], v1[0], v1[2], v1[1], v1[5], v1[6], v1[4], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[20] = CD7M_d7prods_byelem(v1[3], v1[1], v1[0], v1[2], v1[6], v1[4], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[21] = CD7M_d7prods_byelem(v1[3], v1[1], v1[2], v1[0], v1[4], v1[6], v1[5], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[22] = CD7M_d7prods_byelem(v1[3], v1[2], v1[0], v1[1], v1[5], v1[4], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);
   dtrial[23] = CD7M_d7prods_byelem(v1[3], v1[2], v1[1], v1[0], v1[4], v1[5], v1[6], v2[0], v2[1], v2[2], v2[3], v2[4], v2[5], v2[6]);

   dwnby = dtrial[0];
   for (i = 1; i < 24; i++) if (dtrial[i] > dwnby) dwnby = dtrial[i];
   return (fabs(distsq - dwnby));
}

#define d71234dist(v1,v2) sqrt(d71234distsq(v1,v2))


/*     Compute the best distance between 2 G6 vectors
allowing for permulations of g1, g2, g3 as
well as sign changes
*/


void d7cpyvn(int n, double src[], double dst[]) {
   int i;
   for (i = 0; i < n; i++) {
      dst[i] = src[i];
   }
}


void imv7(double v1[7], int m[49], double v2[7]) {
   int i, j;
   double sum;
   for (i = 0; i < 7; i++) {
      sum = 0.0;
      for (j = 0; j < 7; j++) {
         sum = sum + ((double)m[7 * i + j])*v1[j];
      }
      v2[i] = sum;
   }
}


void rmv7(double v1[7], double m[49], double v2[7]) {
   int i, j;
   double sum;
   for (i = 0; i < 7; i++) {
      sum = 0.0;
      for (j = 0; j < 7; j++) {
         sum = sum + m[7 * i + j] * v1[j];
      }
      v2[i] = sum;
   }
}




void d7twoPminusI(double pg[7], double g[7], double gout[7]) {
   int i;
   for (i = 0; i<7; i++) {
      gout[i] = 2.*pg[i] - g[i];
   }
}


/*     Map a G6 vector onto the boundaries after
applying the 24-way unfolding */

#ifdef D7DIST_NO_OUTER_PASS
#define D7NREFL_OUTER_FULL 1
#define D7NREFL_OUTER_MIN 1
#define D7NREFL_OUTER_MID 1
#else
#define D7NREFL_OUTER_FULL 24
#define D7NREFL_OUTER_MID 12
#define D7NREFL_OUTER_MIN 8
#endif


#define SUMD7ERR 1
#define NEGVAL   2
#define POSDOT   4
#define NOTORD   8

int d7notred(double gvec[7], int *errors) {
   int lerr;
   lerr = 0;
   if (fabs(gvec[0] + gvec[1] + gvec[2] + gvec[3] - gvec[4] - gvec[5] - gvec[6])> 1.e-15) {
      lerr |= SUMD7ERR;
   }
   if (gvec[0] < -1.e-15
      || gvec[1] < -1.e-15
      || gvec[2] < -1.e-15
      || gvec[3] < -1.e-15
      || gvec[4] < -1.e-15
      || gvec[5] < -1.e-15
      || gvec[6] < -1.e-15) {
      lerr |= NEGVAL;
   }

   if (gvec[4] - gvec[0] - gvec[3] > 1.e-15
      || gvec[5] - gvec[1] - gvec[3] > 1.e-15
      || gvec[6] - gvec[2] - gvec[3] > 1.e-15
      || gvec[4] - gvec[1] - gvec[2] > 1.e-15
      || gvec[5] - gvec[0] - gvec[2] > 1.e-15
      || gvec[6] - gvec[0] - gvec[1] > 1.e-15) {
      lerr |= POSDOT;
   }

   if (gvec[0] > gvec[1] + 1.e-15
      || gvec[1] > gvec[2] + 1.e-15
      || gvec[2] > gvec[3] + 1.e-15) {
      lerr |= NOTORD;
   }
   if (errors) *errors = lerr;
   return lerr;
}

double d7bddist(double gvec[7], int bdnum) {

   int errors = 0;

   double outside = -1.;

   double pg[7];

   //rmv7(gvec, d7prj[bdnum], pg);
   g_vprj[bdnum](gvec, pg);

   if (d7notred(gvec, &errors)) outside = 1.;

   return outside * (CD7M_d7eucldist(gvec, pg));

}



/* Get the minimum distance to the boundaries */

double d7minbddist(double gvec[7]) {
   int ii;
   double dists[9];
   double minbd;

   dists[0] = fabs(d7bddist(gvec, D7P_1));
   dists[1] = fabs(d7bddist(gvec, D7P_2));
   dists[2] = fabs(d7bddist(gvec, D7P_3));
   dists[3] = fabs(d7bddist(gvec, D7P_4));
   dists[4] = fabs(d7bddist(gvec, D7P_5));
   dists[5] = fabs(d7bddist(gvec, D7P_6));
   dists[6] = fabs(d7bddist(gvec, D7P_7));
   dists[7] = fabs(d7bddist(gvec, D7P_8));
   dists[8] = fabs(d7bddist(gvec, D7P_9));

   minbd = dists[0];
   for (ii = 0; ii<8; ii++) {
      if (ii == 6) continue;
      minbd = CD7M_min(minbd, dists[ii]);
   }
   return minbd;
}



void d7bdmaps(double gvec[7],
   double dists[ND7BND],
   int iord[ND7BND],
   double pgs[ND7BND][7],
   double rgs[ND7BND][7],
   double mpgs[ND7BND][7],
   double mvecs[ND7BND][7],
   double maxdist,
   int * ngood) {

   int jj, itemp, igap, idone;

   for (jj = 0; jj < ND7BND; jj++) {
      iord[jj] = jj;
   }

   *ngood = ND7BND;
   for (jj = 0; jj < ND7BND; jj++) {
      //rmv7(gvec, d7prj[jj], pgs[jj]);
      g_vprj[jj](gvec, pgs[jj]);
      d7twoPminusI(pgs[jj], gvec, rgs[jj]);
      //imv7(pgs[jj], D7MS[jj], mpgs[jj]);
      g_vDMS[jj](pgs[jj], mpgs[jj]);
      //imv7(gvec, D7MS[jj], mvecs[jj]);
      g_vDMS[jj](gvec, mvecs[jj]);
      dists[jj] = CD7M_d71234dist(gvec, pgs[jj]);
      if (dists[jj] > maxdist) (*ngood)--;
   }


   igap = ND7BND;
   while (igap > 1) {
      igap = igap / 2;
      idone = 0;
      while (!idone) {
         idone = 1;
         for (jj = 0; jj < ND7BND - igap; jj += igap) {
            if (dists[iord[jj]] > dists[iord[jj + igap]]) {
               idone = 0;
               itemp = iord[jj];
               iord[jj] = iord[jj + igap];
               iord[jj + igap] = itemp;
            }
         }
      }
   }

}

/* revised D7Dist_2bds

Compute lengths of paths from g_lft to g_rgt through bd_up and bd_dwn


*/

double D7Dist_2bds_rev(double g_lft[7], double g_rgt[7],
   double pg_lft_up[7], double mpg_lft_up[7],
   double pg_rgt_up[7], double mpg_rgt_up[7], int bd_up,
   double pg_rgt_dwn[7], double mpg_rgt_dwn[7],
   double pg_lft_dwn[7], double mpg_lft_dwn[7], int bd_dwn,
   double dist) {

   double bddist_lft_up, bddist_lft_dwn, bddist_right_up, bddist_right_dwn;
   double alpha_lft_up, alpha_lft_dwn;
   double bdint_lft_up[7], bdint_lft_dwn[7], mbdint_lft_up[7], mbdint_lft_dwn[7];
   int ii;
   double gvec_lft_bd_lft_up, gvec_lft_mbd_lft_up, gvec_lft_bd_lft_dwn, gvec_lft_mbd_lft_dwn;
   double gvec_lft_bd_rgt_dwn, gvec_lft_mbd_rgt_dwn, gvec_lft_bd_rgt_up, gvec_lft_mbd_rgt_up;
   double gvec_rgt_bd_lft_up, gvec_rgt_mbd_lft_up, gvec_rgt_bd_lft_dwn, gvec_rgt_mbd_lft_dwn;
   double gvec_rgt_bd_rgt_dwn, gvec_rgt_mbd_rgt_dwn;
   double gvec_lft_bd_lft_upbd_rgt_dwn, gvec_lft_bd_lft_upmbd_rgt_dwn;
   double gvec_lft_mbd_lft_upbd_rgt_dwn, gvec_lft_mbd_lft_upmbd_rgt_dwn;
   double bd_lft_upbd_rgt_dwn, bd_lft_upmbd_rgt_dwn;
   double mbd_lft_upbd_rgt_dwn, mbd_lft_upmbd_rgt_dwn;

   double dist_bd_up_bd_dwn, dist_bd_up_mbd_dwn, dist_mbd_up_bd_dwn, dist_mbd_up_mbd_dwn;

   double to_bd_up_lft, to_bd_up_rgt, to_bd_dwn_lft, to_bd_dwn_rgt;


   /* distances from g_lft and g_rgt to bd_up and bd_dwn */

   bddist_lft_up = fabs(d7bddist(g_lft, bd_up));
   bddist_lft_dwn = fabs(d7bddist(g_lft, bd_dwn));
   bddist_right_up = fabs(d7bddist(g_rgt, bd_up));
   bddist_right_dwn = fabs(d7bddist(g_rgt, bd_dwn));

   /* the portions of a minimal mirror path off each boundary */

   if (bddist_lft_up + bddist_right_up < bddist_lft_up*1.e-10) {
      alpha_lft_up = 0.;
   }
   else {
      alpha_lft_up = bddist_lft_up / (bddist_lft_up + bddist_right_up);
   }
   if (bddist_lft_dwn + bddist_right_dwn < bddist_lft_dwn*1.e-10) {
      alpha_lft_dwn = 0.;
   }
   else {
      alpha_lft_dwn = bddist_lft_dwn / (bddist_lft_dwn + bddist_right_dwn);
   }

   if (alpha_lft_up > 1.) alpha_lft_up = 1.;
   if (alpha_lft_dwn > 1.) alpha_lft_dwn = 1.;


   if (alpha_lft_up < 0.) alpha_lft_up = 0.;
   if (alpha_lft_dwn < 0.) alpha_lft_dwn = 0.;

   for (ii = 0; ii < 7; ii++) {
      bdint_lft_up[ii] = pg_lft_up[ii] + alpha_lft_up * (pg_rgt_up[ii] - pg_lft_up[ii]);
      bdint_lft_dwn[ii] = pg_lft_dwn[ii] + alpha_lft_dwn * (pg_rgt_dwn[ii] - pg_lft_dwn[ii]);
   }
   //imv7(bdint_lft_up, D7MS[bd_up], mbdint_lft_up);
   //imv7(bdint_lft_dwn, D7MS[bd_dwn], mbdint_lft_dwn);
   g_vDMS[bd_up](bdint_lft_up, mbdint_lft_up);
   g_vDMS[bd_dwn](bdint_lft_dwn, mbdint_lft_dwn);

   /* possible routes


   pg_lft_up  bdint_lft_up      pg_rgt_up
   ------*--------*----------^--------*---------bd_up
   _/ \__     mbdint_lft_up
   _/      \__
   _/           \__
   _/                \__
   g_lft *__                   \__
   \__                   \
   \__              __* g_rgt
   \__         _/
   \__    _/
   \ _/    mbdint_rgt_dwm
   ------*---------------*------^-------*----------bd_dwn
   pg_lft_dwn     bdint_lft_dwn   pg_rgt_dwn

   1.  g_lft -> g_rgt

   to_bd_up_lft = min(g_lft->bd_lft_up, g_lft->mbd_lft_up)
   to_bd_up_rgt = min(g_rgt->bd_lft_up, g_rgt->mbd_lft_up)
   to_bd_dwn_lft = min(g_lft->bd_lft_dwn, g_lft->mbd_lft_dwn)
   to_bd_dwn_rgt = min(g_rgt->bd_lft_dwn, g_rgt->mbd_lft_dwn)

   2.  to_bd_up_lft + to_bd_up_rgt
   3.  to_bd_dwn_lft + to_bd_dwn_rgt
   4.  to_bd_up_lft + to_bd_dwn_rgt
   + min(bdint_lft_up->bdint_lft_dwn,
   mbdint_lft_up->bdint_lft_dwn,
   bdint_lft_up->mbdint_lft_dwn,
   mbdint_lft_up->mbdint_lft_dwn)
   */

   to_bd_up_lft = gvec_lft_bd_lft_up = d71234dist(g_lft, bdint_lft_up);
   gvec_lft_mbd_lft_up = d71234dist(g_lft, mbdint_lft_up);
   if (gvec_lft_mbd_lft_up < to_bd_up_lft) to_bd_up_lft = gvec_lft_mbd_lft_up;

   to_bd_up_rgt = gvec_rgt_bd_lft_up = d71234dist(g_rgt, bdint_lft_up);
   gvec_rgt_mbd_lft_up = d71234dist(g_rgt, mbdint_lft_up);
   if (gvec_rgt_mbd_lft_up < to_bd_up_rgt) to_bd_up_rgt = gvec_rgt_mbd_lft_up;

   if (to_bd_up_lft + to_bd_up_rgt < dist) dist = to_bd_up_lft + to_bd_up_rgt;

   dist_bd_up_bd_dwn = 0.;

   if (bd_up != bd_dwn) {

      to_bd_dwn_lft = gvec_lft_bd_lft_dwn = d71234dist(g_lft, bdint_lft_dwn);
      gvec_lft_mbd_lft_dwn = d71234dist(g_lft, mbdint_lft_dwn);
      if (gvec_lft_mbd_lft_dwn < to_bd_dwn_lft) to_bd_dwn_lft = gvec_lft_mbd_lft_dwn;

      to_bd_dwn_rgt = gvec_rgt_bd_lft_dwn = d71234dist(g_rgt, bdint_lft_dwn);
      gvec_rgt_mbd_lft_dwn = d71234dist(g_rgt, mbdint_lft_dwn);
      if (gvec_rgt_mbd_lft_dwn < to_bd_dwn_rgt) to_bd_dwn_rgt = gvec_rgt_mbd_lft_dwn;

      dist_bd_up_bd_dwn = d71234dist(bdint_lft_up, bdint_lft_dwn);
      dist_bd_up_mbd_dwn = d71234dist(bdint_lft_up, mbdint_lft_dwn);
      if (dist_bd_up_mbd_dwn < dist_bd_up_bd_dwn) dist_bd_up_bd_dwn = dist_bd_up_mbd_dwn;
      dist_mbd_up_bd_dwn = d71234dist(mbdint_lft_up, bdint_lft_dwn);
      if (dist_mbd_up_bd_dwn < dist_bd_up_bd_dwn) dist_bd_up_bd_dwn = dist_mbd_up_bd_dwn;
      dist_mbd_up_mbd_dwn = d71234dist(mbdint_lft_up, mbdint_lft_dwn);
      if (dist_mbd_up_mbd_dwn < dist_bd_up_bd_dwn) dist_bd_up_bd_dwn = dist_mbd_up_mbd_dwn;

      if (to_bd_dwn_lft + to_bd_dwn_rgt < dist) dist = to_bd_dwn_lft + to_bd_dwn_rgt;

      if (dist_bd_up_bd_dwn < dist) {
         if (dist_bd_up_bd_dwn + to_bd_up_lft + to_bd_dwn_rgt < dist) dist = dist_bd_up_bd_dwn + to_bd_up_lft + to_bd_dwn_rgt;
         if (dist_bd_up_bd_dwn + to_bd_dwn_lft + to_bd_up_rgt < dist) dist = dist_bd_up_bd_dwn + to_bd_dwn_lft + to_bd_up_rgt;
      }

   }



   return dist;

}




#include <stdio.h>



#define D7DCUT 0.999995
#define D7fudge(d) D7DCUT*d


/*
Compute tminimal distance between two Delaunay-reduced
vectors in the Delaunay Cone following the embedding paths
to the 9 boundaries
*/



double D7Dist_pass(double gvec1[7], double gvec2[7], double dist) {
   double dists1[ND7BND];
   double pgs1[ND7BND][7], rgs1[ND7BND][7], mpgs1[ND7BND][7], mvecs1[ND7BND][7];
   double dists2[ND7BND];
   double pgs2[ND7BND][7], rgs2[ND7BND][7], mpgs2[ND7BND][7], mvecs2[ND7BND][7];
   int iord1[ND7BND], iord2[ND7BND];
   double mindists1;
   double mindists2;
   int jx1, jx2;
   int j1, j2;
   int ngood1, ngood2;
   double maxdist;

   maxdist = D7fudge(dist);

   d7bdmaps(gvec1, dists1, iord1, pgs1, rgs1, mpgs1, mvecs1, maxdist, &ngood1);
   d7bdmaps(gvec2, dists2, iord2, pgs2, rgs2, mpgs2, mvecs2, maxdist, &ngood2);

   mindists1 = d7minbddist(gvec1);
   mindists2 = d7minbddist(gvec2);

   if (mindists1 + mindists2 > dist) return dist;

   if (mindists1 + mindists2 < maxdist) {
      for (jx1 = 0; jx1 < ngood1; jx1++) {
         double d1;
         j1 = iord1[jx1];
         if (j1 < D7P_4 || j1 == D7P_7 || j1 == D7P_9) continue;
         d1 = dists1[j1];

         if (d1 < maxdist) {
            dist = CD7M_min(dist, d71234dist(gvec2, mpgs1[j1]) + d1);
         }
      }
      for (jx2 = 0; jx2 < ngood2; jx2++) {
         double d2;
         j2 = iord2[jx2];
         if (j2 < D7P_4 || j2 == D7P_7 || j2 == D7P_9) continue;
         d2 = dists2[j2];
         if (d2 < maxdist) {
            dist = CD7M_min(dist, (d71234dist(gvec1, mpgs2[j2]) + d2));

         }
      }
   }

   maxdist = D7fudge(dist);
   for (jx1 = 0; jx1 < ngood1; jx1++) {
      double d1;
      j1 = iord1[jx1];
      if (j1 < D7P_4 || j1 == D7P_7 || j1 == D7P_9) continue;
      d1 = dists1[j1];
      if (d1 < maxdist) {
         for (jx2 = 0; jx2 < ngood2; jx2++) {
            double d2;
            j2 = iord2[jx2];
            if (j2 < D7P_4 || j2 == D7P_7 || j2 == D7P_9) continue;
            d2 = dists2[j2];
            if (d2 < maxdist) {
               dist = D7Dist_2bds_rev(gvec1, gvec2, pgs1[j1], mpgs1[j1], pgs2[j1], mpgs2[j1], j1,
                  pgs2[j2], mpgs2[j2], pgs1[j2], mpgs1[j2], j2, dist);

            }
         }
      }
   }
   return dist;
}


/*
Compute the minimal distance between two Delaunay-reduced
vectors in the D7 Cone following the embedding paths
to the 7 major boundaries
*/





double D7Dist_cpp(double * gvec1, double * gvec2) {
   int rpasses, ir, irt;
   int jr;
   int mixedr;
   double dist, dist1, dist2, distmin;
   double rgvec1[24][7], rgvec2[24][7];
   double trgvec1[24][7], trgvec2[24][7];
   double ndists[24][24];
   double ndist1[24];
   double ndist2[24];
   double temp[24];
   dist1 = d7minbddist(gvec1);
   dist2 = d7minbddist(gvec2);
   distmin = CD7M_min(dist1, dist2);
   rpasses = D7NREFL_OUTER_MIN;
   dist = d71234dist(gvec1, gvec2);
   D7report_integer("\n gvec1 not red ", d7notred(gvec1), "\n");
   D7report_integer("\n gvec2 not red ", d7notred(gvec2), "\n");
   D7report_double("\n  Entered D7Dist gdist = ", dist, ", ");
   D7report_double_vector("gvec1 = ", gvec1, ", ")
      D7report_double_vector("gvec2 = ", gvec2, ";")
      if (dist1 + dist2 <  dist*.999) {
         rpasses = D7NREFL_OUTER_MID;
      }
   if (dist1 < dist*.999 || dist2 < dist*.999) {
      rpasses = D7NREFL_OUTER_FULL;
   }
   ndists[0][0] = dist = D7Dist_pass(gvec1, gvec2, dist);
   /* Collect rpasses-1 transformed vectors */
#pragma omp parallel for schedule(dynamic)
   for (ir = 1; ir < rpasses; ir++) {
      //imv7(gvec1, D7Refl[D7Rord[ir]], rgvec1[ir]);
      //imv7(gvec2, D7Refl[D7Rord[ir]], rgvec2[ir]);
      g_vrefl[D7Rord[ir]](gvec1, rgvec1[ir]);
      g_vrefl[D7Rord[ir]](gvec2, rgvec2[ir]);
      ndists[ir][0] = D7Dist_pass(rgvec1[ir], gvec2, dist);
      ndists[0][ir] = D7Dist_pass(gvec1, rgvec2[ir], dist);
   }



#pragma omp parallel private (ir, jr)
   {
#pragma omp for schedule(dynamic)
      for (mixedr = 0; mixedr < (rpasses - 1)*(rpasses - 1); mixedr++)
      {
         jr = 1 + mixedr % (rpasses - 1);
         ir = 1 + mixedr / (rpasses - 1);
         ndists[ir][jr] = D7Dist_pass(rgvec1[ir], rgvec2[jr], dist);
      }
   }


#pragma omp flush(dist,ndists)
#pragma omp critical(distminimize)
   for (ir = 0; ir < rpasses; ir++) {
      for (jr = 0; jr < rpasses; jr++) {
         if (ndists[ir][jr] < dist) dist = ndists[ir][jr];
         D7report_double_if_changed("\n ndists[ir][jr] ", dist, ", ");
         D7also_if_changed_report_integer("ir =", ir, ", ");
         D7also_if_changed_report_integer("jr =", jr, "\n");
      }
   }
   return dist;
}



#endif /*D7DIST_H */

