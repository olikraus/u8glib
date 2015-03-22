/*
 * Windows Bitmap File Loader
 * Version 1.2.1 (20070430)
 *
 * Supported Formats: 1, 4, 8, 16, 24, 32 Bit Images
 * Alpha Bitmaps are also supported.
 * Supported compression types: RLE 8, BITFIELDS
 *
 * Created by: Benjamin Kalytta, 2006 - 2007
 *
 * Licence: Free to use
 * Source can be found at http://www.kalytta.com/bitmap.h
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char uint8_t;

#pragma once
#pragma pack(1)

#define BITMAP_SIGNATURE 'MB'

typedef struct {
	unsigned short int Signature;
	unsigned int Size;
	unsigned int Reserved;
	unsigned int BitsOffset;
} BITMAP_FILEHEADER;

#define BITMAP_FILEHEADER_SIZE 14

typedef struct {
	unsigned int HeaderSize;
	int Width;
	int Height;
	unsigned short int Planes;
	unsigned short int BitCount;
	unsigned int Compression;
	unsigned int SizeImage;
	int PelsPerMeterX;
	int PelsPerMeterY;
	unsigned int ClrUsed;
	unsigned int ClrImportant;
	unsigned int RedMask;
	unsigned int GreenMask;
	unsigned int BlueMask;
	unsigned int AlphaMask;
	unsigned int CsType;
	unsigned int Endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
	unsigned int GammaRed;
	unsigned int GammaGreen;
	unsigned int GammaBlue;
} BITMAP_HEADER;

typedef struct {
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Alpha;
} RGBA;

typedef struct {
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Alpha;
} BGRA;

typedef struct {
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
} BGR;

typedef struct {
	unsigned short int Blue:5;
	unsigned short int Green:5;
	unsigned short int Red:5;
	unsigned short int Reserved:1;
} BGR16;

#if 0

#define RIFF_SIGNATURE	0x46464952
#define RIFF_TYPE		0x204c4150
#define PAL_SIGNATURE	0x61746164
#define PAL_UNKNOWN		0x01000300

typedef struct {
	unsigned int Signature;
	unsigned int FileLength;
	unsigned int Type;
	unsigned int PalSignature;
	unsigned int ChunkSize;
	unsigned int Unkown;
} PAL;

#endif

class CBitmap {
private:
	BITMAP_FILEHEADER m_BitmapFileHeader;
	BITMAP_HEADER m_BitmapHeader;
	RGBA *m_BitmapData;
	unsigned int m_BitmapSize;
	BGRA *m_ColorTable;
	unsigned int m_ColorTableSize;

private:

	unsigned int ShiftRightByMask(unsigned int Color, unsigned int Mask, unsigned int DistributeToBits = 8) {
		
		if (Mask == 0) return 0;

		unsigned int ShiftCount = 0;
		unsigned int Test = 0x00000001;

		while (ShiftCount < 32) {
			if (Mask & Test) {
				break;
			}
			Test <<= 1;
			ShiftCount++;
		}
		
		unsigned int BitCount = 32;
		Test = 0x80000000;

		while (BitCount) {
			if ((Mask >> ShiftCount) & Test) {
				break;
			}
			Test >>= 1;
			BitCount--;
		}

		unsigned int BaseColor = (Color & Mask) >> ShiftCount;

		if (DistributeToBits > BitCount) {
			/* We have to fill lower bits */
			unsigned int BitsToFill = DistributeToBits - BitCount;
			while (BitsToFill--) {
				BaseColor <<= 1;
				if (BaseColor & 1) {
					BaseColor |= 1;
				}
			}
		} else if (DistributeToBits < BitCount) {
			BaseColor >>= (BitCount - DistributeToBits);
		}
		return BaseColor;
	}

public:
	
	CBitmap() : m_BitmapData(0), m_BitmapSize(0), m_ColorTableSize(0), m_ColorTable(0) {
		Dispose();
	}
	
	CBitmap(const char* Filename) : m_BitmapData(0), m_BitmapSize(0), m_ColorTableSize(0), m_ColorTable(0) {
		Load(Filename);
	}
	
	~CBitmap() {
		Dispose();
	}
	
	void Dispose() {
		if (m_BitmapData) delete[] m_BitmapData;
		if (m_ColorTable) delete[] m_ColorTable;
		m_ColorTableSize = 0;
		m_BitmapData = 0;
		m_ColorTable = 0;
		memset(&m_BitmapFileHeader, 0, sizeof(m_BitmapFileHeader));
		memset(&m_BitmapHeader, 0, sizeof(m_BitmapHeader));
	}
	
	/* Load specified Bitmap and stores it as RGBA in an internal buffer */
	
	bool Load(const char *Filename) {
		FILE *file = fopen(Filename, "rb");

		Dispose();
		
		if (file == 0) return false;
		
		fread(&m_BitmapFileHeader, BITMAP_FILEHEADER_SIZE, 1, file);
		if (m_BitmapFileHeader.Signature != BITMAP_SIGNATURE) {
			return false;
		}

		fread(&m_BitmapHeader, sizeof(BITMAP_HEADER), 1, file);
		
		/* Load Color Table */
		
		fseek(file, BITMAP_FILEHEADER_SIZE + m_BitmapHeader.HeaderSize, SEEK_SET);
		
		if (m_BitmapHeader.BitCount == 1) {
			m_ColorTableSize = 2;
		} else if (m_BitmapHeader.BitCount == 4) {
			m_ColorTableSize = 16;
		} else if (m_BitmapHeader.BitCount == 8) {
			m_ColorTableSize = 256;
		}
		
		m_ColorTable = new BGRA[m_ColorTableSize];
		
		fread(m_ColorTable, sizeof(BGRA), m_ColorTableSize, file);

		/* ... Color Table for 16 or 32 Bit Images are not supported yet */	
		
		m_BitmapSize = GetWidth() * GetHeight();
		m_BitmapData = new RGBA[m_BitmapSize];
		
		unsigned int LineWidth = ((GetWidth() * GetBitCount() / 8) + 3) & ~3;
		unsigned char *Line = new unsigned char[LineWidth];
		
		fseek(file, m_BitmapFileHeader.BitsOffset, SEEK_SET);
		
		int Index = 0;
		
		if (m_BitmapHeader.Compression == 0) {
			for (int i = 0; i < GetHeight(); i++) {
				fread(Line, LineWidth, 1, file);
				
				unsigned char *LinePtr = Line;
				
				for (int j = 0; j < GetWidth(); j++) {
					if (m_BitmapHeader.BitCount == 1) {
						unsigned int Color = *((unsigned char*) LinePtr);
						for (int k = 0; k < 8; k++) {
							m_BitmapData[Index].Red = m_ColorTable[Color & 0x80 ? 1 : 0].Red;
							m_BitmapData[Index].Green = m_ColorTable[Color & 0x80 ? 1 : 0].Green;
							m_BitmapData[Index].Blue = m_ColorTable[Color & 0x80 ? 1 : 0].Blue;
							m_BitmapData[Index].Alpha = m_ColorTable[Color & 0x80 ? 1 : 0].Alpha;
							Index++;
							Color <<= 1;
						}
						LinePtr++;
						j += 7;
					} else if (m_BitmapHeader.BitCount == 4) {
						unsigned int Color = *((unsigned char*) LinePtr);
						m_BitmapData[Index].Red = m_ColorTable[(Color >> 4) & 0x0f].Red;
						m_BitmapData[Index].Green = m_ColorTable[(Color >> 4) & 0x0f].Green;
						m_BitmapData[Index].Blue = m_ColorTable[(Color >> 4) & 0x0f].Blue;
						m_BitmapData[Index].Alpha = m_ColorTable[(Color >> 4) & 0x0f].Alpha;
						Index++;
						m_BitmapData[Index].Red = m_ColorTable[Color & 0x0f].Red;
						m_BitmapData[Index].Green = m_ColorTable[Color & 0x0f].Green;
						m_BitmapData[Index].Blue = m_ColorTable[Color & 0x0f].Blue;
						m_BitmapData[Index].Alpha = m_ColorTable[Color & 0x0f].Alpha;
						Index++;
						LinePtr++;
						j++;
					} else if (m_BitmapHeader.BitCount == 8) {
						unsigned int Color = *((unsigned char*) LinePtr);
						m_BitmapData[Index].Red = m_ColorTable[Color].Red;
						m_BitmapData[Index].Green = m_ColorTable[Color].Green;
						m_BitmapData[Index].Blue = m_ColorTable[Color].Blue;
						m_BitmapData[Index].Alpha = m_ColorTable[Color].Alpha;
						Index++;
						LinePtr++;
					} else if (m_BitmapHeader.BitCount == 16) {
						unsigned int Color = *((unsigned short int*) LinePtr);
						m_BitmapData[Index].Red = ((Color >> 10) & 0x1f) << 3;
						m_BitmapData[Index].Green = ((Color >> 5) & 0x1f) << 3;
						m_BitmapData[Index].Blue = (Color & 0x1f) << 3;
						m_BitmapData[Index].Alpha = 255;
						Index++;
						LinePtr += 2;
					} else if (m_BitmapHeader.BitCount == 24) {
						unsigned int Color = *((unsigned int*) LinePtr);
						m_BitmapData[Index].Blue = Color & 0xff;
						m_BitmapData[Index].Green = (Color >> 8) & 0xff;
						m_BitmapData[Index].Red = (Color >> 16) & 0xff;
						m_BitmapData[Index].Alpha = 255;
						Index++;
						LinePtr += 3;
					} else if (m_BitmapHeader.BitCount == 32) {
						unsigned int Color = *((unsigned int*) LinePtr);
						m_BitmapData[Index].Blue = Color & 0xff;
						m_BitmapData[Index].Green = (Color >> 8) & 0xff;
						m_BitmapData[Index].Red = (Color >> 16) & 0xff;
						m_BitmapData[Index].Alpha = Color >> 24;
						Index++;
						LinePtr += 4;
					}
				}
			}
		} else if (m_BitmapHeader.Compression == 1) { // RLE 8
			unsigned char Count = 0;
			unsigned char ColorIndex = 0;
			int x = 0, y = 0;

			while (!feof(file)) {
				fread(&Count, 1, 1, file);
				fread(&ColorIndex, 1, 1, file);

				if (Count > 0) {
					Index = x + y * GetWidth();
					for (int k = 0; k < Count; k++) {
						m_BitmapData[Index + k].Red = m_ColorTable[ColorIndex].Red;
						m_BitmapData[Index + k].Green = m_ColorTable[ColorIndex].Green;
						m_BitmapData[Index + k].Blue = m_ColorTable[ColorIndex].Blue;
						m_BitmapData[Index + k].Alpha = m_ColorTable[ColorIndex].Alpha;
					}
					x += Count;
				} else if (Count == 0) {
					int Flag = ColorIndex;
					if (Flag == 0) {
						x = 0;
						y++;
					} else if (Flag == 1) {
						break;
					} else if (Flag == 2) {
						char rx = 0;
						char ry = 0;
						fread(&rx, 1, 1, file);
						fread(&ry, 1, 1, file);
						x += rx;
						y += ry;
					} else {
						Count = Flag;
						Index = x + y * GetWidth();
						for (int k = 0; k < Count; k++) {
							fread(&ColorIndex, 1, 1, file);
							m_BitmapData[Index + k].Red = m_ColorTable[ColorIndex].Red;
							m_BitmapData[Index + k].Green = m_ColorTable[ColorIndex].Green;
							m_BitmapData[Index + k].Blue = m_ColorTable[ColorIndex].Blue;
							m_BitmapData[Index + k].Alpha = m_ColorTable[ColorIndex].Alpha;
						}
						x += Count;
						if (ftell(file) & 1) fseek(file, 1, SEEK_CUR);
					}
				}
			}
		} else if (m_BitmapHeader.Compression == 2) { // RLE 4
			/* RLE 4 is not supported */
		} else if (m_BitmapHeader.Compression == 3) { // BITFIELDS
			
			/* We assumes that mask of each color component can be in any order */

			for (int i = 0; i < GetHeight(); i++) {
				fread(Line, LineWidth, 1, file);
				
				unsigned char *LinePtr = Line;
				
				for (int j = 0; j < GetWidth(); j++) {
					
					unsigned int Color = 0;

					if (m_BitmapHeader.BitCount == 16) {
						Color = *((unsigned short int*) LinePtr);
						LinePtr += 2;
					} else if (m_BitmapHeader.BitCount == 32) {
						Color = *((unsigned int*) LinePtr);
						LinePtr += 4;
					}
					m_BitmapData[Index].Red = ShiftRightByMask(Color, m_BitmapHeader.RedMask);
					m_BitmapData[Index].Green = ShiftRightByMask(Color, m_BitmapHeader.GreenMask);
					m_BitmapData[Index].Blue = ShiftRightByMask(Color, m_BitmapHeader.BlueMask);
					m_BitmapData[Index].Alpha = ShiftRightByMask(Color, m_BitmapHeader.AlphaMask);

					Index++;
				}
			}
		}

		fclose(file);
		return true;
	}
	
	bool Save(char* Filename, unsigned int BitCount = 32) {
		FILE *file = fopen(Filename, "wb");

		if (file == 0) return false;
		
		BITMAP_FILEHEADER bfh = {0};
		BITMAP_HEADER bh = {0};

		bfh.Signature = BITMAP_SIGNATURE;
		bfh.BitsOffset = sizeof(BITMAP_HEADER) + sizeof(BITMAP_FILEHEADER);
		bfh.Size = (GetWidth() * GetHeight() * BitCount) / 8 + bfh.BitsOffset;
	
		bh.HeaderSize = sizeof(BITMAP_HEADER);
		bh.BitCount = BitCount;
		
		if (BitCount == 32) {
			bh.Compression = 3; // BITFIELD
			bh.AlphaMask = 0xff000000;
			bh.BlueMask = 0x00ff0000;
			bh.GreenMask = 0x0000ff00;
			bh.RedMask = 0x000000ff;
		} else {
			bh.Compression = 0; // RGB
		}

		bh.Planes = 1;
		bh.Height = GetHeight();
		bh.Width = GetWidth();
		bh.SizeImage = (GetWidth() * GetHeight() * BitCount) / 8;
		bh.PelsPerMeterX = 3780;
		bh.PelsPerMeterY = 3780;
		
		if (BitCount == 32) {
			fwrite(&bfh, sizeof(BITMAP_FILEHEADER), 1, file);
			fwrite(&bh, sizeof(BITMAP_HEADER), 1, file);
			fwrite(m_BitmapData, bh.SizeImage, 1, file);
		} else if (BitCount < 16) {
			unsigned char* Bitmap = new unsigned char[bh.SizeImage];
			
			BGRA *Palette = 0;
			unsigned int PaletteSize = 0;

			if (GetBitsWithPalette(Bitmap, bh.SizeImage, BitCount, Palette, PaletteSize)) {
				bfh.BitsOffset += PaletteSize * sizeof(BGRA);

				fwrite(&bfh, sizeof(BITMAP_FILEHEADER), 1, file);
				fwrite(&bh, sizeof(BITMAP_HEADER), 1, file);
				fwrite(Palette, PaletteSize, sizeof(BGRA), file);
				fwrite(Bitmap, bh.SizeImage, 1, file);
			}
			delete [] Bitmap;
			delete [] Palette;
		} else {
			unsigned char* Bitmap = new unsigned char[bh.SizeImage];

			if (GetBits(Bitmap, bh.SizeImage, BitCount)) {
				fwrite(&bfh, sizeof(BITMAP_FILEHEADER), 1, file);
				fwrite(&bh, sizeof(BITMAP_HEADER), 1, file);
				fwrite(Bitmap, bh.SizeImage, 1, file);
			}
			delete [] Bitmap;
		}

		fclose(file);
		return true;
	}

	/*
 	 * simple bitmap to hex file converter for display renderer. Header: FMT H W 
 	 */
	bool SaveBM8IncludeHex(const char *Filename, const char *Field="logo") {
		FILE *file = fopen(Filename, "wb");

		char buf[16];
		if (NULL == file) {
			return false;
		}
		int hg = GetHeight(), wg = GetWidth();
		fprintf(file,"/* header format : Bits Height Width */\n");
		fprintf(file, "const unsigned char %s[] = {\n", Field);
		fprintf(file, "  0x%x, 0x%x, 0x%x,", 8, hg, wg);
		/* rendering from bottom to up */
		for (int h = hg-1; h >= 0; h--)
		{
			fprintf(file, "\n  ");
			for (int w = 0; w < wg; w++)
			{
				uint8_t r = m_BitmapData[w+h*wg].Red, 
					g = m_BitmapData[w+h*wg].Green,
					b = m_BitmapData[w+h*wg].Blue;

				/* 332 format */
				uint8_t rgb332 = (r>>5)<<5 | (g>>5)<<2 | (b>>6);
				sprintf(buf, "0x%02x", rgb332);
				fprintf(file, "%s, ", buf);
			}
		}
		fprintf(file, "\n};");
		fclose(file);
		return true;
	}

	unsigned int GetWidth() {
		return m_BitmapHeader.Width < 0 ? -m_BitmapHeader.Width : m_BitmapHeader.Width;
	}
	
	unsigned int GetHeight() {
		return m_BitmapHeader.Height < 0 ? -m_BitmapHeader.Height : m_BitmapHeader.Height;
	}
	
	unsigned int GetBitCount() {
		return m_BitmapHeader.BitCount;
	}
	
	/* Copies internal RGBA buffer to user specified buffer */
	
	bool GetBits(void* Buffer, unsigned int &Size) {
		bool Result = false;
		if (Size == 0 || Buffer == 0) {
			Size = m_BitmapSize * sizeof(RGBA);
			Result = m_BitmapSize != 0;
		} else {
			memcpy(Buffer, m_BitmapData, Size);
			Result = true;
		}
		return Result;
	}

	/* Returns internal RGBA buffer */
	
	void* GetBits() {
		return m_BitmapData;
	}
	
	/* Copies internal RGBA buffer to user specified buffer and convertes into destination bit format.
	 * Supported Bit depths are: 16 (5-5-5), 24, 32
	 */

	bool GetBits(void* Buffer, unsigned int &Size, unsigned int BitCount) {
		bool Result = false;

		if (Size == 0 || Buffer == 0) {
			Size = (m_BitmapSize * BitCount) / 8;
			return true;
		}

		if (BitCount > 32) {
			return false;
		}
		
		unsigned char* BufferPtr = (unsigned char*) Buffer;

		for (int i = 0; i < m_BitmapSize; i++) {
			if (BitCount == 16) {
				((BGR16*) BufferPtr)->Blue = ShiftRightByMask(m_BitmapData[i].Blue, 0xff, 5);
				((BGR16*) BufferPtr)->Green = ShiftRightByMask(m_BitmapData[i].Green, 0xff, 5);
				((BGR16*) BufferPtr)->Red = ShiftRightByMask(m_BitmapData[i].Red, 0xff, 5);
				BufferPtr += 2;
			} else if (BitCount == 24) {
				((BGR*) BufferPtr)->Blue = m_BitmapData[i].Blue;
				((BGR*) BufferPtr)->Green = m_BitmapData[i].Green;
				((BGR*) BufferPtr)->Red = m_BitmapData[i].Red;
				BufferPtr += 3;
			} else if (BitCount == 32) {
				((BGRA*) BufferPtr)->Blue = m_BitmapData[i].Blue;
				((BGRA*) BufferPtr)->Green = m_BitmapData[i].Green;
				((BGRA*) BufferPtr)->Red = m_BitmapData[i].Red;
				((BGRA*) BufferPtr)->Alpha = m_BitmapData[i].Alpha;
				BufferPtr += 4;
			}
		}
		
		Result = true;

		return Result;
	}
	
	/* See GetBits(). 
	 * It creates a corresponding color table (palette) which have to be destroyed by the user after usage.
	 * Supported Bit depths are: 4, 8
	 * Todo: Optimize, use optimized palette, do ditehring
	 */

	bool GetBitsWithPalette(void* Buffer, unsigned int &Size, unsigned int BitCount, BGRA* &Palette, unsigned int &PaletteSize, bool OptimalPalette = false) {
		bool Result = false;

		if (BitCount > 16) {
			return false;
		}

		if (Size == 0 || Buffer == 0) {
			Size = (m_BitmapSize * BitCount) / 8;
			return true;
		}
		
		if (BitCount == 4) {
			PaletteSize = 16;
			Palette = new BGRA[PaletteSize];
			for (int r = 0; r < 4; r++) {
				for (int g = 0; g < 2; g++) {
					for (int b = 0; b < 2; b++) {
						Palette[r | g << 2 | b << 3].Red = (r << 6) | 0x35;
						Palette[r | g << 2 | b << 3].Green = (g << 7) | 0x55;
						Palette[r | g << 2 | b << 3].Blue = (b << 7) | 0x55;
						Palette[r | g << 2 | b << 3].Alpha = 0xff;
					}
				}
			}
		} else if (BitCount == 8) {
			PaletteSize = 256;
			Palette = new BGRA[PaletteSize];
			for (int r = 0; r < 8; r++) {
				for (int g = 0; g < 8; g++) {
					for (int b = 0; b < 4; b++) {
						Palette[r | g << 3 | b << 6].Red = (r << 5) | 0x15;
						Palette[r | g << 3 | b << 6].Green = (g << 5) | 0x15;
						Palette[r | g << 3 | b << 6].Blue = (b << 6) | 0x35;
						Palette[r | g << 3 | b << 6].Alpha = 0xff;
					}
				}
			}
		}
		
		unsigned char* BufferPtr = (unsigned char*) Buffer;
		
		for (int i = 0; i < m_BitmapSize; i++) {
			if (BitCount == 4) {
				*BufferPtr = (m_BitmapData[i].Red >> 6) | (m_BitmapData[i].Green >> 7) << 2 | (m_BitmapData[i].Blue >> 7) << 3;
				i++;
				*BufferPtr |= ((m_BitmapData[i].Red >> 6) | (m_BitmapData[i].Green >> 7) << 2 | (m_BitmapData[i].Blue >> 7) << 3) << 4;
				BufferPtr++;
			} else if (BitCount == 8) {
				*BufferPtr = (m_BitmapData[i].Red >> 5) | (m_BitmapData[i].Green >> 5) << 3 | (m_BitmapData[i].Blue >> 5) << 6;
				BufferPtr++;
			}
		}
		
		Result = true;

		return Result;
	}

	/* Set Bitmap Bits. Will be converted to RGBA internally */

	void SetBits(void* Buffer, unsigned int Width, unsigned int Height, unsigned int RedMask, unsigned int GreenMask, unsigned int BlueMask, unsigned int AlphaMask = 0) {
		unsigned char *BufferPtr = (unsigned char*) Buffer;
		
		Dispose();

		m_BitmapHeader.Width = Width;
		m_BitmapHeader.Height = Height;
		m_BitmapHeader.BitCount = 32;
		m_BitmapHeader.Compression = 3; 

		m_BitmapSize = GetWidth() * GetHeight();
		m_BitmapData = new RGBA[m_BitmapSize];
		
		/* Find BitCount by Mask, maximum is 32 Bit */
		
		unsigned int Test = 0x80000000;
		unsigned int BitCount = 32;
		
		while (BitCount) {
			if ((RedMask | GreenMask | BlueMask | AlphaMask) & Test) {
				break;
			}
			Test >>= 1;
			BitCount--;
		}

		for (int i = 0; i < m_BitmapSize; i++) {
			unsigned int Color = 0;
			if (BitCount <= 8) {
				Color = *((unsigned char*) BufferPtr);
				BufferPtr += 1;
			} else if (BitCount <= 16) {
				Color = *((unsigned short int*) BufferPtr);
				BufferPtr += 2;
			} else if (BitCount <= 24) {
				Color = *((unsigned int*) BufferPtr);
				BufferPtr += 3;
			} else if (BitCount <= 32) {
				Color = *((unsigned int*) BufferPtr);
				BufferPtr += 4;
			} else {
				/* unsupported */
				BufferPtr += 1;
			}
			m_BitmapData[i].Alpha = ShiftRightByMask(Color, AlphaMask);
			m_BitmapData[i].Red = ShiftRightByMask(Color, RedMask);
			m_BitmapData[i].Green = ShiftRightByMask(Color, GreenMask);
			m_BitmapData[i].Blue = ShiftRightByMask(Color, BlueMask);
		}
	}

	void SetAlphaBits(unsigned char Alpha) {
		for (int i = 0; i < m_BitmapSize; i++) {
			m_BitmapData[i].Alpha = Alpha;
		}
	}
	
};
