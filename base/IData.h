#ifndef IDATA_H
#define IDATA_H

#include <string>

//Interface for Alex data. 

namespace alex {

	class IData {
	public:
	virtual ~IData () {};
	//virtual std::string Serialize() const = 0;
	//virtual void Recreate(std::string) = 0;
	};

	class INamed {
	public:
	virtual ~INamed () {};
	virtual std::string  Name() const = 0;
	virtual void SetName(std::string) = 0;
	};
}
#endif //IDATA_H