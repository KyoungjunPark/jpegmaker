/*****************************************************************************/
/*       Computer Science Engineering, Chung-Ang University, Seoul Korea     */
/*                                                                           */
/*   Title      : Design a Converter between JPEG format and Gray scale image*/
/*   File Name  : Main.cpp                                                   */
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

#include "Main.h"

int main()
{
	CImg<unsigned char> image("hyojoo.jpeg");
	//CImg<unsigned char> grayImage = RGBtoGrayScale(image);
	CImg<unsigned char> grayImage("hyojoo_gray.jpeg");

	/*
	for(int i = 0; i < grayImage.dimx(); i++){
		for(int j = 0; j < grayImage.dimy(); j++){
			for(int k=0; k<3; k++){
				grayImage(i,j,0,k) /= 2;
				main_disp(grayImage, "Main display", 0);
			}
		}
	}
	*/
	CImgDisplay main_disp(grayImage, "Main display");
	//fftw example
	fftw_complex *in, *out;
	fftw_plan p;

	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 8);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 8);
	p = fftw_plan_dft_1d(8, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p);

	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);

	cin.get();
	return 0;
}
CImg<unsigned char> RGBtoGrayScale(CImg<unsigned char> original_image)
{
	CImg<unsigned char> imgGray = original_image.get_RGBtoYCbCr().get_channel(0);
	imgGray.save("hyojoo_gray.jpeg");
	return imgGray;
}
