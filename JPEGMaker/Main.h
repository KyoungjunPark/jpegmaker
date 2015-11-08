/*****************************************************************************/
/*       Computer Science Engineering, Chung-Ang University, Seoul Korea     */
/*                                                                           */
/*   Title      : Design a Converter between JPEG format and Gray scale image*/
/*   File Name  : Main.h                                                     */
/*   Author     : Kyoung-Jun Park   pgj525@cau.ac.kr                         */
/*   Date       : Nov 02, 2015                                               */
/*   Version    :                                                            */
/*   Project    :                                                            */
/*   Description: Multimedia Computing                                       */
/*                                                                           */
/*****************************************************************************/

/******************************** Revision History ***************************/
/* Date(M/D/Y) Author                Notes                                   */
/* ==========  ======                ===================                     */
/* 11/02/15    Kyoung-Jun Park       Initial design                          */
/*                                                                           */
/*****************************************************************************/


/******************************** References *********************************/
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include <fftw3.h>

#include "CImg/CImg.h"

using namespace std;
using namespace cimg_library;

CImg<unsigned char> RGBtoGrayScale(CImg<unsigned char> original_image);
