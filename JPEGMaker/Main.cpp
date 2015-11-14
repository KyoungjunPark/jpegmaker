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

unsigned char *raw_image = NULL;

int main()
{

	// Change Original image to GrayScale image
	CImg<unsigned char> imgOriginal("kyoungJun.jpeg");
	CImg<unsigned char> imgGrayScale = RGBtoGrayScale(imgOriginal);
	
	//JSAMPLE* image_buffer;
	char inputFilename[256] = "kyoungJun_gray.jpeg";
	char outputFilename[256] = "kyoungJun_gray_out.jpeg";


	int image_height = 512;
	int image_width = 512;

	if(read_JPEG_file(inputFilename) > 0){
		write_JPEG_file(outputFilename, 15, image_height, image_width);
	}
	return 0;
}
CImg<unsigned char> RGBtoGrayScale(CImg<unsigned char> original)
{
	CImg<unsigned char> imgGray;

	imgGray = original.get_RGBtoYCbCr().get_channel(0);
	imgGray.save("kyoungJun_gray.jpeg");
	return imgGray;
}
int read_JPEG_file(char *filename)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];


	FILE *inputFile = fopen(filename, "rb");
	unsigned long location =0;
	int i =0;

	if(!inputFile){
		printf("Error opening jpeg file %s\n!", filename);
		exit(1);
	}
	
	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, inputFile);
	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress(&cinfo);

	raw_image = (unsigned char*)malloc(cinfo.output_width*cinfo.output_height
			*cinfo.num_components);
	
	row_pointer[0] = (unsigned char*)malloc(cinfo.output_width*cinfo.num_components);
	while(cinfo.output_scanline < cinfo.image_height){
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
		for(i = 0 ; i < cinfo.image_width*cinfo.num_components; i++){
			raw_image[location++] = row_pointer[0][i];
		}
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(row_pointer[0]);
	fclose(inputFile);

	return 1;
}
void write_JPEG_file(char *filename, int quality,
		int image_height, int image_width)
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
	//cinfo.input_components = 3;
	//cinfo.in_color_space = JCS_RGB;
	
	jpeg_set_defaults(&cinfo);

	cinfo.num_components = 1;
	//cinfo.num_components = 3;
	//jpeg_set_quality(&cinfo, quality, TRUE);

	jpeg_start_compress(&cinfo, TRUE);

	while(cinfo.next_scanline < cinfo.image_height){
		row_pointer[0] = &raw_image[cinfo.next_scanline*cinfo.image_width*cinfo.input_components];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);

	jpeg_destroy_compress(&cinfo);

}
