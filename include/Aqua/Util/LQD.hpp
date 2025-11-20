#pragma once
#include <string>
#include <Aqua/Core/Types.hpp>

/* 
 *
 * What is a Liquid File? 
 * A liquid file (.lqd) is a file format used to package game assets into a standardized binary format.
 *
 * What does a .lqd file look like? 
 * the first 64 bytes correspond to the name of the file.
 * the next 64 bits are the total size of the file.
 * The next 16 bits are the version of the file.
 * The next byte is for the count of entries of the TOC (Table Of Contents)
 * Total Preamble Size: 75 bytes.
 *
 * Each entry in the TOC is 128 byes.
 * - 1  byte for the type of the data.
 * - 64 bytes for the name
 * - 32 bits for the offset
 * - 32 bits for the size
 * - 55 bytes of padding.
 *
 * after the TOC we have 8 bytes of padding followed by each entry.
 *
 * Liquid files are little endian. (for now?)
 *
 */

namespace Aqua {
class LQD {
public:
	LQD(std::string path) {}

	//NOTE: Maybe vert + frag shader eventually? For now focus on .png, .wav, etc.. -plum
	enum DataType : u8 {
		PNG_IMG,
	};
	
	//TODO: WRITE
	//Get known data as bytes
	//serialize bytes
	//write to file

	//TODO: READ
	//Load file as bytes
	//parse preamble
	//parse TOC
	//read data from file using toc.
	
private:
	const std::string extension = ".lqd";
	const u8 preambleSize = 80;

	u8 fileName[64];
	u64 fileSize;
	u16 version;

	u8 tocEntrySize = 128;
	u8 tocEntryUsedSize = 73;
	u8 tocEntries;
	u32 tocSize;
}; 
}
