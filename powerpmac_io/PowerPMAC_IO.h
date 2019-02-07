/*----- PROTECTED REGION ID(PowerPMAC_IO.h) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_IO.h
//
// description : Include file for the PowerPMAC_IO class
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef PowerPMAC_IO_H
#define PowerPMAC_IO_H

#include "libs/sigs.h"
#include <tango.h>


/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO.h

/**
 *  PowerPMAC_IO class description:
 *    
 */

namespace PowerPMAC_IO_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_IO::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Additional Class Declarations

class PowerPMAC_IO : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(PowerPMAC_IO::Data Members) ENABLED START -----*/

//	Add your own data members
private:
	sigs::Connection connectionEstablished;
	sigs::Connection connectionLost;
	bool isWritable;
	float analogScaleFactor;
/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Data Members

//	Device property data members
public:
	//	Port:	the port must be a named memory address that is mapped to the ppmac registers. 
	//  the format follows the pattern {purpose}{nr}{physical port}
	//  
	//  valid names are:
	//  
	//  [ADC]
	//  ADC1X9
	//  ADC2X9
	//  ADC1X10
	//  ADC2X10
	//  ADC1X11
	//  ADC2X11
	//  ADC1X12
	//  ADC2X12
	//  
	//  [DAC]
	//  DAC1X9
	//  DAC2X9
	//  DAC1X10
	//  DAC2X10
	//  DAC1X11
	//  DAC2X11
	//  DAC1X12
	//  DAC2X12
	//  
	//  [GPIN 5V TTL]
	//  GPIN1X9 
	//  GPIN2X9 
	//  GPIN1X10
	//  GPIN2X10
	//  GPIN1X11
	//  GPIN2X11
	//  GPIN1X12
	//  GPIN2X12
	//  
	//  [GPIN]
	//  GPIN1X15 
	//  GPIN2X15 
	//  GPIN3X15 
	//  GPIN4X15 
	//  GPIN5X15 
	//  GPIN6X15 
	//  GPIN7X15 
	//  GPIN8X15 
	//  GPIN9X15 
	//  GPIN10X15
	//  GPIN11X15
	//  GPIN12X15
	//  GPIN13X15
	//  GPIN14X15
	//  GPIN15X15
	//  GPIN16X15
	//  GPIN1X16 
	//  GPIN2X16 
	//  GPIN3X16 
	//  GPIN4X16 
	//  GPIN5X16 
	//  GPIN6X16 
	//  GPIN7X16 
	//  GPIN8X16 
	//  GPIN9X16 
	//  GPIN10X16
	//  GPIN11X16
	//  GPIN12X16
	//  GPIN13X16
	//  GPIN14X16
	//  GPIN15X16
	//  GPIN16X16
	//  
	//  [GPOUT]
	//  GPOUT1X15
	//  GPOUT2X15
	//  GPOUT3X15
	//  GPOUT4X15
	//  GPOUT5X15
	//  GPOUT6X15
	//  GPOUT7X15
	//  GPOUT8X15
	//  GPOUT1X16
	//  GPOUT2X16
	//  GPOUT3X16
	//  GPOUT4X16
	//  GPOUT5X16
	//  GPOUT6X16
	//  GPOUT7X16
	//  GPOUT8X16
	string	port;

//	Attribute data members
public:
	Tango::DevLong	*attr_RawValue_read;
	Tango::DevDouble	*attr_Value_read;
	Tango::DevDouble	*attr_ScaleFactor_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_IO(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	PowerPMAC_IO(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	PowerPMAC_IO(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~PowerPMAC_IO() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : PowerPMAC_IO::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : PowerPMAC_IO::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute RawValue related methods
 *	Description: raw values are in the range of -32768 to +32768
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
	virtual void read_RawValue(Tango::Attribute &attr);
	virtual void write_RawValue(Tango::WAttribute &attr);
	virtual bool is_RawValue_allowed(Tango::AttReqType type);
/**
 *	Attribute Value related methods
 *	Description: the `working` value is the raw value scaled to -1 to 1. if you e.g. have a +-5V or +-10V input
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_Value(Tango::Attribute &attr);
	virtual void write_Value(Tango::WAttribute &attr);
	virtual bool is_Value_allowed(Tango::AttReqType type);
/**
 *	Attribute ScaleFactor related methods
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
	virtual void read_ScaleFactor(Tango::Attribute &attr);
	virtual void write_ScaleFactor(Tango::WAttribute &attr);
	virtual bool is_ScaleFactor_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_IO::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:


	//--------------------------------------------------------
	/**
	 *	Method      : PowerPMAC_IO::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(PowerPMAC_IO::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Additional Method prototypes
};

/*----- PROTECTED REGION ID(PowerPMAC_IO::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_IO::Additional Classes Definitions

}	//	End of namespace

#endif   //	PowerPMAC_IO_H
