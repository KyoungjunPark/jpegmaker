#include <stdio.h>
#include <Magick++.h>

#include "CImg\CImg.h"
#include "jpeg\jpeglib.h"
#include <setjmp.h>

using namespace cimg_library;
using namespace Magick;

CImg<unsigned char> RGBtoGrayScale(CImg<unsigned char> original);

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
