//
// Created by urbschaj on 10.01.19.
//

#ifndef POWERPMAC_PPMACCOREINTERFACE_H
#define POWERPMAC_PPMACCOREINTERFACE_H

namespace ppmac {

	class ppmaccoreinterface
	{
	public:
		ppmaccoreinterface();
		~ppmaccoreinterface();
		void initialize();
	private:
		void gangsta();
	};

	ppmaccoreinterface& GetCoreObject();
}


#endif //POWERPMAC_PPMACCOREINTERFACE_H
