/* @file RGBAColor.cpp
 *
 * @author Kelsey Yuen
 * @date 03-21-2013
 */
#include "rgbacolor.h"

RGBAColor::operator==(RGBAColor const &other) const{
	return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha;
}

RGBAColor::operator!=(RGBAColor const &other) const{
	return !(*this == other);
}

RGBAColor::RGBAColor() : red(255), green(255), blue(255), alpha(255) {
}

RGBAColor::RGBAColor(unsigned char r, unsigned char g, unsigned char b) : red(r), green(g), blue(b), alpha(255){
}

RGBAColor::RGBAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : red(r), green(g), blue(b), alpha(a) {
}

RGBAColor::operator=(RGBAColor const &other) const{
	if (this != &other)
		_copy(other);
	return *this;
}

void RGBAColor::_copy(RGBAColor const &other){
	red = other.red;
	green = other.green;
	blue = other.blue;
	alpha = other.alpha;
}

std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel)
{
	out << "(" << (int) pixel.red << "," << (int) pixel.green << ","
		<< (int) pixel.blue << ")";
	if (pixel.alpha != 255)
		out << " a:" << pixel.alpha;
	return out;
}