#include "TObject.h"
#include <string>
class FileSelector : public TObject {

	public :
		FileSelector( std::string info = "", std::string filename = "" );
		~FileSelector();

		void print() const;
		bool input( std::istream & in );

		std::string info() const;
		std::string filename() const;

	private :
		std::string info_;
		std::string filename_;

	ClassDef(FileSelector,1)

};
