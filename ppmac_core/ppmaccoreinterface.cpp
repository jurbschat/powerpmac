//
// Created by urbschaj on 10.01.19.
//

#include "ppmaccoreinterface.h"

#include <iostream>

namespace ppmac
{

	ppmaccoreinterface& GetCoreObject() {
		static ppmaccoreinterface core;
		return core;
	}

	ppmaccoreinterface::ppmaccoreinterface() {
		std::cout << "ppmaccoreinterface::ppmaccoreinterface()" << std::endl;
	}

	ppmaccoreinterface::~ppmaccoreinterface() {
		std::cout << "ppmaccoreinterface::~ppmaccoreinterface()" << std::endl;
	}

	void ppmaccoreinterface::initialize() {
		std::cout << "ppmaccoreinterface::initialize()" << std::endl;;
		gangsta();
	}

	void ppmaccoreinterface::gangsta() {
		std::cout << "ppmaccoreinterface::gangsta()" << std::endl;
	}
}
