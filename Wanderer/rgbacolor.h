/* @file RGBAColor.h
 * Based heavily on rgbapixel by Chase Geigle, Spring 2012
 *
 * @author Kelsey Yuen
 * @date 03-21-2013
 */
#ifndef RGBACOLOR_H
#define RGBACOLOR_H 
 
class RGBAColor{
	public:
		unsigned char red; 	// Byte for red component of the pixel
		unsigned char green;	// etc.
		unsigned char blue;
		unsigned char alpha;
		
		/* Equality Operator
		* @param other	Other pixel to check equality with
		*/
		bool operator==(RGBAColor const & other) const;
		
		/* Inequality Operator
		* @param other	Other pixel to check inequality with.
		*/
		bool operator!=(RGBAColor const & other) const;
		
		/* Default Constructor
		* By default is white and opaque (non-transparent) :: 255,255,255,255
		*/
		RGBAColor();
		
		/* Opaque Constructor
		* Constructs an opaque RGBAColor with given red, green, and blue color values. Alpha is 255.
		* @param red
		* @param green
		* @param blue
		*/
		RGBAColor(unsigned char red, unsigned char green, unsigned char blue);
		
		/* Complete Constructor
		* Constructs an RGBAColor with desired color and transparency
		* @param red
		* @param green
		* @param blue
		* @param alpha
		*/
		RGBAColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		
		/* Assignment Opreator for setting two pixels equal to each other
		* @param other	Other pixel to be copied
		* @return The current pixel for assignment chaining
		*/
		RGBAColor const &operator=(RGBAColor const &other) const;
		
	private:
		void _copy(RGBAColor const &other);
};

/**
 * Stream operator that allows pixels to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param pixel Pixel to write to the stream.
 */
std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel);

#endif	// RGBACOLOR_H