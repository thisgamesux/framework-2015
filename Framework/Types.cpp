#include "stdafx.h"

using namespace FWSDK;

#define HLSMAX		240
#define RGBMAX		255
#define UNDEFINED	(HLSMAX*2/3)

FWSDK::Color FWSDK::Color::Darker(WORD var) {
	WORD hue, lum, sat;

	GetHLS(hue, lum, sat, this->a);

	lum = ((lum - var) >= 0) ? (lum - var) : 0;

	return GetFromHLS(hue, lum, sat, this->a);
}

FWSDK::Color FWSDK::Color::Lighter(WORD var) {
	WORD hue, lum, sat;
	GetHLS(hue, lum, sat, this->a);

	lum = ((lum + var) <= HLSMAX) ? (lum + var) : 0;

	return GetFromHLS(hue, lum, sat, this->a);
}

void FWSDK::Color::GetHLS(WORD &hue, WORD &lum, WORD &sat, UINT32 &alpha) {
	alpha = this->a;

	BYTE cMax, cMin;
	
	WORD R = static_cast<WORD>(this->r);
	WORD G = static_cast<WORD>(this->g); 
	WORD B = static_cast<WORD>(this->b);

	WORD Rdelta, Gdelta, Bdelta;
	cMax = (BYTE)max(max(R, G), B);
	cMin = (BYTE)min(min(R, G), B);
	lum = (((cMax + cMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);

	if (cMax == cMin)
	{
		sat = 0;
		hue = UNDEFINED;
		return;
	}
	else
	{
		if (lum <= (HLSMAX / 2))
		{
			sat = (((cMax - cMin) * HLSMAX) +
				((cMax + cMin) / 2)) / (cMax + cMin);
		}
		else
		{
			sat = (((cMax - cMin) * HLSMAX) +
				((2 * RGBMAX - cMax - cMin) / 2)) / (2 * RGBMAX - cMax - cMin);
		}

		Rdelta = (((cMax - R)*(HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
		Gdelta = (((cMax - G)*(HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
		Bdelta = (((cMax - B)*(HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);

		if (R == cMax)
		{
			hue = Bdelta - Gdelta;
		}
		else if (G == cMax)
		{
			hue = (HLSMAX / 3) + Rdelta - Bdelta;
		}
		else
		{
			hue = ((2 * HLSMAX) / 3) + Gdelta - Rdelta;
		}

		if (hue < 0)
			hue += HLSMAX;

		if (hue > HLSMAX)
			hue -= HLSMAX;
	}
}

FWSDK::Color FWSDK::Color::GetFromHLS(WORD hue, WORD lum, WORD sat, UINT32 alpha) {
	WORD R, G, B;
	WORD Magic1, Magic2;
	if (sat == 0)
	{
		R = G = B = (lum * RGBMAX) / HLSMAX;
		if (hue != UNDEFINED){
			return Color(0, 0, 0, 255);
		}
	}
	else{
		if (lum <= (HLSMAX / 2))
		{
			Magic2 = (lum*(HLSMAX + sat) + (HLSMAX / 2)) / HLSMAX;
		}
		else{
			Magic2 = lum + sat - ((lum*sat) + (HLSMAX / 2)) / HLSMAX;
		}
		Magic1 = 2 * lum - Magic2;

		R = (HueToRGB(Magic1, Magic2, hue + (HLSMAX / 3))*RGBMAX + (HLSMAX / 2)) / HLSMAX;
		G = (HueToRGB(Magic1, Magic2, hue)*RGBMAX + (HLSMAX / 2)) / HLSMAX;
		B = (HueToRGB(Magic1, Magic2, hue - (HLSMAX / 3))*RGBMAX + (HLSMAX / 2)) / HLSMAX;
	}

	return FWSDK::Color(
		static_cast<UINT8>(R), 
		static_cast<UINT8>(G), 
		static_cast<UINT8>(B), 
		static_cast<UINT8>(alpha));
}

WORD FWSDK::Color::HueToRGB(WORD n1, WORD n2, WORD hue) {
	if (hue < 0)
		hue += HLSMAX;

	if (hue > HLSMAX)
		hue -= HLSMAX;

	if (hue < (HLSMAX / 6))
		return (n1 + (((n2 - n1)*hue + (HLSMAX / 12)) / (HLSMAX / 6)));
	if (hue < (HLSMAX / 2))
		return (n2);
	if (hue < ((HLSMAX * 2) / 3))
		return (n1 + (((n2 - n1)*(((HLSMAX * 2) / 3) - hue) + (HLSMAX / 12)) / (HLSMAX / 6)));

	return (n1);
}