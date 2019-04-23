#include "../include/FileSelector.hh"
#include <iostream>

ClassImp(FileSelector)


//FileSelector::FileSelector( std::string info = "", std::string filename = "" ){
FileSelector::FileSelector( std::string info, std::string filename ){
	info_ = info ;
	filename_ = filename ;
}

FileSelector::~FileSelector(){};

bool FileSelector::input( std::istream & in ){

	std::string line;
	std::getline( in, line, ',');
	info_ = line;
	std::getline( in, line);
	filename_ = line;

	if( line == "" ){
		 return false;
	}else{
		return true;
	}

}

void FileSelector::print() const{
	std::cout << "Info: " << info_ << std::endl;
	std::cout << "Root file: " << filename_ << std::endl;
}

std::string FileSelector::info() const { return info_; }
std::string FileSelector::filename() const { return filename_; }


