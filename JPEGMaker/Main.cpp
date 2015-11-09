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

	JSAMPLE* image_buffer;
	//vector<char> image_buffer;
	//XInfo_t xinfo = getXInfo(":0");
	//XImage* screen_shot = takeScreenshot(xinfo, buffer);

	int image_height = 1024;
	int image_width = 819;

	CImg<unsigned char> *image = ReadJpegIntoCImg("hyojoo_gray.jpeg");
	CImgDisplay main_disp(*image, "Click a point");

	//write_JPEG_file("hyojoo_gray.jpeg", 1, image_buffer, image_height, image_width);
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
void write_JPEG_file(char *filename, int quality, JSAMPLE* image_buffer
		, int image_height, int image_width)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FILE *outfile;
	JSAMPROW row_pointer[1];
	int row_stride;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if((outfile = fopen(filename, "wb")) == NULL){
		fprintf(stderr, "Can't open %s\n", filename);
		exit(1);
	}
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = image_width;
	cinfo.image_height = image_height;
	cinfo.input_components = 1;
	cinfo.in_color_space = JCS_GRAYSCALE;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);

	jpeg_start_compress(&cinfo, TRUE);
	
	row_stride = image_width*3;

	while(cinfo.next_scanline < cinfo.image_height){
		row_pointer[0] = &image_buffer[cinfo.next_scanline*row_stride];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);

	jpeg_destroy_compress(&cinfo);

}
CImg<unsigned char> *ReadJpegIntoCImg(char *filename)
{
	FILE *file;
	if((file = fopen(filename, "rb")) == NULL){
		fprintf(stderr, "Can't open %s\n", filename);
		exit(1);
	}
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, file);
	jpeg_read_header(&cinfo, true);

	jpeg_start_decompress(&cinfo);

	int width = cinfo.output_width;
	int height = cinfo.output_height;
	int numChannels = cinfo.num_components;
	unsigned long dataSize = width*height*numChannels;

	unsigned char *data = (unsigned char *)malloc(dataSize);
	unsigned char* rowptr;
	while(cinfo.output_scanline < height){
		rowptr = data + cinfo.output_scanline * width * numChannels;
		jpeg_read_scanlines(&cinfo, &rowptr, 1);
	}
	jpeg_finish_decompress(&cinfo);

	fclose(file);

	CImg<unsigned char> *image = new CImg<unsigned char>(width, height, 1, numChannels);
	
	for(int i=0; i < width ; i++){
		for(int j=0; j < height; j++){
			for(int k=0; k < numChannels; k++){
				*image->data(i,j,0,k) = data[j*width*numChannels+ i*numChannels + k];
			}
		}
	}

	free(data);

	return image;
}
