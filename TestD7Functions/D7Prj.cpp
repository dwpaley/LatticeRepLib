#include "stdafx.h"

#include "D7Prj.h"

void D7prj1(const double d[], double dd[]) {
   /*prj[D7P_1]  ,1,*/
   dd[0] = +0.3571428571428572*d[0] + 0.3571428571428572*d[1] - 0.1428571428571428*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[1] = +0.3571428571428572*d[0] + 0.3571428571428572*d[1] - 0.1428571428571428*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[2] = -0.1428571428571428*d[0] - 0.1428571428571428*d[1] + 0.8571428571428571*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[3] = -0.1428571428571428*d[0] - 0.1428571428571428*d[1] - 0.1428571428571428*d[2] + 0.8571428571428571*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[4] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] + 0.8571428571428571*d[4] - 0.1428571428571428*d[5] - 0.1428571428571428*d[6];
   dd[5] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] - 0.1428571428571428*d[4] + 0.8571428571428571*d[5] - 0.1428571428571428*d[6];
   dd[6] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] - 0.1428571428571428*d[4] - 0.1428571428571428*d[5] + 0.8571428571428571*d[6];
}

void D7prj2(const double d[], double dd[]) {
   /*prj[D7P_2]   2,*/
   dd[0] = +0.8571428571428571*d[0] - 0.1428571428571428*d[1] - 0.1428571428571428*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[1] = -0.1428571428571428*d[0] + 0.3571428571428572*d[1] + 0.3571428571428572*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[2] = -0.1428571428571428*d[0] + 0.3571428571428572*d[1] + 0.3571428571428572*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[3] = -0.1428571428571428*d[0] - 0.1428571428571428*d[1] - 0.1428571428571428*d[2] + 0.8571428571428571*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[4] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] + 0.8571428571428571*d[4] - 0.1428571428571428*d[5] - 0.1428571428571428*d[6];
   dd[5] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] - 0.1428571428571428*d[4] + 0.8571428571428571*d[5] - 0.1428571428571428*d[6];
   dd[6] = 0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] - 0.1428571428571428*d[4] - 0.1428571428571428*d[5] + 0.8571428571428571*d[6];
}

void D7prj3(const double d[], double dd[]) {
   /*prj[D7P_3]   3,*/
   dd[0] = +0.8571428571428571*d[0] - 0.1428571428571428*d[1] - 0.1428571428571428*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[1] = -0.1428571428571428*d[0] + 0.8571428571428571*d[1] - 0.1428571428571428*d[2] - 0.1428571428571428*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[2] = -0.1428571428571428*d[0] - 0.1428571428571428*d[1] + 0.3571428571428572*d[2] + 0.3571428571428572*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[3] = -0.1428571428571428*d[0] - 0.1428571428571428*d[1] + 0.3571428571428572*d[2] + 0.3571428571428572*d[3] + 0.1428571428571428*d[4] + 0.1428571428571428*d[5] + 0.1428571428571428*d[6];
   dd[4] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] + 0.8571428571428571*d[4] - 0.1428571428571428*d[5] - 0.1428571428571428*d[6];
   dd[5] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] - 0.1428571428571428*d[4] + 0.8571428571428571*d[5] - 0.1428571428571428*d[6];
   dd[6] = +0.1428571428571428*d[0] + 0.1428571428571428*d[1] + 0.1428571428571428*d[2] + 0.1428571428571428*d[3] - 0.1428571428571428*d[4] - 0.1428571428571428*d[5] + 0.8571428571428571*d[6];
}

void D7prj4(const double d[], double dd[]) {
   dd[0] = +0.75*d[0] - 0.25*d[3] + 0.25*d[5] + 0.25*d[6];
   dd[1] = +0.6666666666666666*d[1] - 0.3333333333333333*d[2] + 0.3333333333333333*d[4];
   dd[2] = -0.3333333333333333*d[1] + 0.6666666666666666*d[2] + 0.3333333333333333*d[4];
   dd[3] = -0.25*d[0] + 0.75*d[3] + 0.25*d[5] + 0.25*d[6];
   dd[4] = +0.3333333333333333*d[1] + 0.3333333333333333*d[2] + 0.6666666666666666*d[4];
   dd[5] = +0.25*d[0] + 0.25*d[3] + 0.75*d[5] - 0.25*d[6];
   dd[6] = +0.25*d[0] + 0.25*d[3] - 0.25*d[5] + 0.75*d[6];
}

void D7prj5(const double d[], double dd[]) {
   /*prj[D7P_5]   5 */
   dd[0] = 0.6666666666666666*d[0] - 0.3333333333333333*d[3] + 0.3333333333333333*d[4];
   dd[1] = +0.75*d[1] - 0.25*d[2] + 0.25*d[5] + 0.25*d[6];
   dd[2] = -0.25*d[1] + 0.75*d[2] + 0.25*d[5] + 0.25*d[6];
   dd[3] = -0.3333333333333333*d[0] + 0.6666666666666666*d[3] + 0.3333333333333333*d[4];
   dd[4] = 0.3333333333333333*d[0] + 0.3333333333333333*d[3] + 0.6666666666666666*d[4];
   dd[5] = 0.25*d[1] + 0.25*d[2] + 0.75*d[5] - 0.25*d[6];
   dd[6] = 0.25*d[1] + 0.25*d[2] - 0.25*d[5] + 0.75*d[6];
}

void D7prj6(const double d[], double dd[]) {
   /*prj[D7P_6]   6 */
   dd[0] = 0.6666666666666666*d[0] - 0.3333333333333333*d[2] + 0.3333333333333333*d[5];
   dd[1] = 0.75*d[1] - 0.25*d[3] + 0.25*d[4] + 0.25*d[6];
   dd[2] = -0.3333333333333333*d[0] + 0.6666666666666666*d[2] + 0.3333333333333333*d[5];
   dd[3] = -0.25*d[1] + 0.75*d[3] + 0.25*d[4] + 0.25*d[6];
   dd[4] = +0.25*d[1] + 0.25*d[3] + 0.75*d[4] - 0.25*d[6];
   dd[5] = 0.3333333333333333*d[0] + 0.3333333333333333*d[2] + +0.6666666666666666*d[5];
   dd[6] = 0.25*d[1] + 0.25*d[3] - 0.25*d[4] + 0.75*d[6];
}

void D7prj7(const double d[], double dd[]) {
   /*prj[D7P_7]   7 */
   dd[0] = 0.75*d[0] - 0.25*d[2] + 0.25*d[4] + 0.25*d[6];
   dd[1] = 0.0*d[0] + 0.6666666666666666*d[1] - 0.3333333333333333*d[3] + 0.3333333333333333*d[5] + 0.0*d[6];
   dd[2] = -0.25*d[0] + 0.75*d[2] + 0.25*d[4] + 0.25*d[6];
   dd[3] = 0.0*d[0] - 0.3333333333333333*d[1] + 0.6666666666666666*d[3] + 0.3333333333333333*d[5] + 0.0*d[6];
   dd[4] = 0.25*d[0] + 0.25*d[2] + 0.75*d[4] - 0.25*d[6];
   dd[5] = 0.0*d[0] + 0.3333333333333333*d[1] + 0.3333333333333333*d[3] + 0.6666666666666666*d[5] + 0.0*d[6];
   dd[6] = 0.25*d[0] + 0.25*d[2] - 0.25*d[4] + 0.75*d[6];
}

void D7prj8(const double d[], double dd[]) {
   /*prj[D7P_8]   8 */
   dd[0] = 0.6666666666666666*d[0] - 0.3333333333333333*d[1] + 0.3333333333333333*d[6];
   dd[1] = -0.3333333333333333*d[0] + 0.6666666666666666*d[1] + 0.3333333333333333*d[6];
   dd[2] = 0.75*d[2] - 0.25*d[3] + 0.25*d[4] + 0.25*d[5] + 0.0*d[6];
   dd[3] = -0.25*d[2] + 0.75*d[3] + 0.25*d[4] + 0.25*d[5] + 0.0*d[6];
   dd[4] = 0.25*d[2] + 0.25*d[3] + 0.75*d[4] - 0.25*d[5] + 0.0*d[6];
   dd[5] = 0.25*d[2] + 0.25*d[3] - 0.25*d[4] + 0.75*d[5] + 0.0*d[6];
   dd[6] = 0.3333333333333333*d[0] + 0.3333333333333333*d[1] + 0.6666666666666666*d[6];
}

void D7prj9(const double d[], double dd[]) {
   /*prj[D7P_9]   9 */
   dd[0] = 0.75*d[0] - 0.25*d[1] + 0.0*d[2] + 0.0*d[3] + 0.25*d[4] + 0.25*d[5];
   dd[1] = -0.25*d[0] + 0.75*d[1] + 0.0*d[2] + 0.0*d[3] + 0.25*d[4] + 0.25*d[5];
   dd[2] = 0.0*d[0] + 0.0*d[1] + 0.6666666666666666*d[2] - 0.3333333333333333*d[3] + 0.3333333333333333*d[6];
   dd[3] = 0.0*d[0] + 0.0*d[1] - 0.3333333333333333*d[2] + 0.6666666666666666*d[3] + 0.3333333333333333*d[6];
   dd[4] = 0.25*d[0] + 0.25*d[1] + 0.0*d[2] + 0.0*d[3] + 0.75*d[4] - 0.25*d[5];
   dd[5] = 0.25*d[0] + 0.25*d[1] + 0.0*d[2] + 0.0*d[3] - 0.25*d[4] + 0.75*d[5];
   dd[6] = 0.0*d[0] + 0.0*d[1] + 0.3333333333333333*d[2] + 0.3333333333333333*d[3] + 0.6666666666666666*d[6];
}

std::vector< void(*)(const double[], double[])> GetProjectorFunctions() {
   std::vector< void(*)(const double[], double[])> v;
   v.push_back(D7prj1);
   v.push_back(D7prj2);
   v.push_back(D7prj3);
   v.push_back(D7prj4);
   v.push_back(D7prj5);
   v.push_back(D7prj6);
   v.push_back(D7prj7);
   v.push_back(D7prj8);
   v.push_back(D7prj9);
   return v;
}
