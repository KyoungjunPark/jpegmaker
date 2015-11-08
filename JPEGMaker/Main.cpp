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

	/* Change Original image to GrayScale image
	CImg<unsigned char> imgOriginal("hyojoo.jpeg");
	CImg<unsigned char> imgGrayScale = RGBtoGrayScale(imgOriginal);
	*/

	JSAMPLE *image_buffer;
	int image_height;
	int image_width;

	
	
	system("pause");
	return 0;
}
CImg<unsigned char> RGBtoGrayScale(CImg<unsigned char> original)
{
	CImg<unsigned char> imgGray;

	imgGray = original.get_RGBtoYCbCr().get_channel(0);
	imgGray.save("hyojoo_gray.jpeg");
	return imgGray;
}
void write_JPEG_file(char *filename, int quality)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FILE *outfile;
	JSAMPROW row_pointer[1];
	int row_stride;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

}
