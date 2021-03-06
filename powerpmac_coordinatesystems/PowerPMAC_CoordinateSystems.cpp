/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        PowerPMAC_CoordinateSystems.cpp
//
// description : C++ source for the PowerPMAC_CoordinateSystems class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               PowerPMAC_CoordinateSystems are implemented in this file.
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

#include "coreinterface.h"
#include "commandbuilder.h"
#include "../tangoutil.h"
#include "resultparser.h"
#include <fmt/format.h>
#include <PowerPMAC_CoordinateSystems.h>
#include <PowerPMAC_CoordinateSystemsClass.h>
#include <memory>

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems.cpp

/**
 *  PowerPMAC_CoordinateSystems class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name      |  Method name
//================================================================
//  State             |  Inherited (no method)
//  Status            |  Inherited (no method)
//  Abort             |  abort
//  RunMotionProgram  |  run_motion_program
//  MultiAxisMove     |  multi_axis_move
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  NumAxis      |  Tango::DevLong	Scalar
//  CoordStates  |  Tango::DevString	Scalar
//  AxisMapping  |  Tango::DevString	Spectrum  ( max = 26)
//================================================================

namespace PowerPMAC_CoordinateSystems_ns
{
/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::namespace_starting) ENABLED START -----*/



/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems()
 *	Description : Constructors for a Tango device
 *                implementing the classPowerPMAC_CoordinateSystems
 */
//--------------------------------------------------------
PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::constructor_1
}
//--------------------------------------------------------
PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::constructor_2
}
//--------------------------------------------------------
PowerPMAC_CoordinateSystems::PowerPMAC_CoordinateSystems(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::delete_device()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::delete_device) ENABLED START -----*/

	StopCoordinateSystem();
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::delete_device
	delete[] attr_NumAxis_read;
	delete[] attr_CoordStates_read;
	delete[] attr_AxisMapping_read;

	connectionEstablished.reset();
	connectionLost.reset();
	statusChanged.reset();
	coordChanged.reset();
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::init_device()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::init_device_before) ENABLED START -----*/

	// pre dev prop read
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	attr_NumAxis_read = new Tango::DevLong[1];
	attr_CoordStates_read = new Tango::DevString[1];
	attr_AxisMapping_read = new Tango::DevString[26];
	//	No longer if mandatory property not set. 
	if (mandatoryNotDefined)
		return;

	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::init_device) ENABLED START -----*/

	*attr_NumAxis_read = 0;
	*attr_CoordStates_read = nullptr;
	std::fill(attr_AxisMapping_read, attr_AxisMapping_read + 26, nullptr);
	started=false;

	coordId = ppmac::CoordID(coordinateIndex);

	ppmac::CoreInterface& ci = ppmac::GetCoreObject();

	connectionEstablished = ci.Signals().ConnectionEstablished([this](){
		StartCoordinateSystem();
	});

	connectionLost = ci.Signals().ConnectionLost([this](){
		StopCoordinateSystem();
	});

	statusChanged = ci.Signals().StatusChanged(coordId, [this](uint64_t newState, uint64_t changed){
		CoordinateStateChanged(newState, changed);
	});
	coordChanged = ci.Signals().CoordChanged(coordId, [this](uint32_t axis){
		CoordinateSystemChanged(axis);
	});

	if(ci.IsConnected()) {
		StartCoordinateSystem();
	} else {
		set_state(Tango::OFF);
	}

	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::init_device
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::get_device_property()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::get_device_property_before

	mandatoryNotDefined = false;

	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("CoordinateIndex"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on PowerPMAC_CoordinateSystemsClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		PowerPMAC_CoordinateSystemsClass	*ds_class =
			(static_cast<PowerPMAC_CoordinateSystemsClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize CoordinateIndex from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  coordinateIndex;
		else {
			//	Try to initialize CoordinateIndex from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  coordinateIndex;
		}
		//	And try to extract CoordinateIndex value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  coordinateIndex;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

	}

	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::get_device_property_after
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::check_mandatory_property()
 *	Description : For mandatory properties check if defined in database.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop)
{
	//	Check if all properties are empty
	if (class_prop.is_empty() && dev_prop.is_empty())
	{
		TangoSys_OMemStream	tms;
		tms << endl <<"Property \'" << dev_prop.name;
		if (Tango::Util::instance()->_UseDb==true)
			tms << "\' is mandatory but not defined in database";
		else
			tms << "\' is mandatory but cannot be defined without database";
		string	status(get_status());
		status += tms.str();
		set_status(status);
		mandatoryNotDefined = true;
		/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::check_mandatory_property) ENABLED START -----*/
		cerr << tms.str() << " for " << device_name << endl;
		
		/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::check_mandatory_property
	}
}


//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::always_executed_hook()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::always_executed_hook()  " << device_name << endl;
	if (mandatoryNotDefined)
	{
		string	status(get_status());
		Tango::Except::throw_exception(
					(const char *)"PROPERTY_NOT_SET",
					status.c_str(),
					(const char *)"PowerPMAC_CoordinateSystems::always_executed_hook()");
	}
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::read_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute NumAxis related method
 *	Description: 
 *
 *	Data type:	Tango::DevLong
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::read_NumAxis(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::read_NumAxis(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::read_NumAxis) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto result = ci.ExecuteCommand(ppmac::cmd::CoordGetAxisCount(coordId));
		Tango::DevLong val = tu::ParseInt32(result);
		*attr_NumAxis_read = val;
		attr.set_value(attr_NumAxis_read);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::read_NumAxis
}
//--------------------------------------------------------
/**
 *	Read attribute CoordStates related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::read_CoordStates(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::read_CoordStates(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::read_CoordStates) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_CoordStates_read);

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();

		uint64_t coordStatus = ci.GetCoordInfo(coordId).status.registerValue;
		auto aciveStates = ppmac::states::GetCoordStateNamesForFlagMatch(coordStatus, 0xFFFFFFFFFFFFFFFF);
		tu::SetStringValue(attr_CoordStates_read, aciveStates);
		attr.set_value(attr_CoordStates_read);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::read_CoordStates
}
//--------------------------------------------------------
/**
 *	Read attribute AxisMapping related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Spectrum max = 26
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::read_AxisMapping(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::read_AxisMapping(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::read_AxisMapping) ENABLED START -----*/
	//	Set the attribute value

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto axisDef = ci.GetMotorAxisDefinitions(coordId);
		for (size_t i = 0; i < axisDef.size(); i++) {
			auto& ad = axisDef[i];
			tu::SetStringValue(&attr_AxisMapping_read[i], fmt::format("Motor {} -> {}", ad.motorId, ad.axisName));
		}
		attr.set_value(attr_AxisMapping_read, axisDef.size());
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::read_AxisMapping
}

//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::add_dynamic_attributes) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command Abort related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::abort()
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::Abort()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::abort) ENABLED START -----*/

	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::CoordAbortMove(coordId));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::abort
}
//--------------------------------------------------------
/**
 *	Command RunMotionProgram related method
 *	Description: 
 *
 *	@param argin 
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::run_motion_program(Tango::DevString argin)
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::RunMotionProgram()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::run_motion_program) ENABLED START -----*/
	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::CoordRunProgram(coordId, argin));
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::run_motion_program
}
//--------------------------------------------------------
/**
 *	Command MultiAxisMove related method
 *	Description: 
 *
 *	@param argin 
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::multi_axis_move(Tango::DevString argin)
{
	DEBUG_STREAM << "PowerPMAC_CoordinateSystems::MultiAxisMove()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::multi_axis_move) ENABLED START -----*/

	try {
		auto mam = ppmac::parser::ParseMultiAxisMove(argin);
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		//TODO: validate axis names ot just ignore them? currently we simply ignore them
		auto cmd = ppmac::cmd::CoordMultiAxisMove(coordId, mam);
		ci.ExecuteCommand(cmd);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::multi_axis_move
}
//--------------------------------------------------------
/**
 *	Method      : PowerPMAC_CoordinateSystems::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void PowerPMAC_CoordinateSystems::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::add_dynamic_commands) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::add_dynamic_commands
}

/*----- PROTECTED REGION ID(PowerPMAC_CoordinateSystems::namespace_ending) ENABLED START -----*/

void PowerPMAC_CoordinateSystems::StartCoordinateSystem() {
	if(started) {
		return;
	}
	started = true;
	//fmt::print("starting coord {}\n", coordinateIndex);
	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		// get the number of axis
		auto result = ci.ExecuteCommand(ppmac::cmd::CoordGetAxisCount(coordId));
		int32_t val = tu::ParseInt32(result);
		if(val >= ppmac::AvailableAxis::maxAxis) {
			set_state(Tango::FAULT);
			Tango::Except::throw_exception("invalid coordinate system", "number of axis must be <= 26 (A-Z)", "PowerPMAC_CoordinateSystems::StartCoordinateSystem");
		}
		*attr_NumAxis_read = val;
		auto coordInfo = ci.GetCoordInfo(coordId);
		UpdateAxisToMatchCurrent(coordInfo.availableAxis);
		UpdateStateFromCurrentStatus(coordInfo.status.registerValue);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
}

void PowerPMAC_CoordinateSystems::StopCoordinateSystem() {
	if(!started) {
		return;
	}
	started = false;
	//fmt::print("stopping coord {}\n", coordinateIndex);
	for(auto& it : attribs) {
		remove_attribute(it.second);
	}
	attribs.clear();
}

void PowerPMAC_CoordinateSystems::CoordinateStateChanged(uint64_t newState, uint64_t changes) {
	UpdateStateFromCurrentStatus(newState);

	if(tu::IsOneOf(get_state(), Tango::ON, Tango::MOVING)) {
		try {
			if (ppmac::bits::rising(newState, changes, ppmac::CoordStatusBits::DestVelZero)) {
				set_state(Tango::ON);
				//fmt::print("set state to ON\n");
			} else if (ppmac::bits::falling(newState, changes, ppmac::CoordStatusBits::DestVelZero)) {
				set_state(Tango::MOVING);
				ClearMoveStatusWaitTimer();
				//fmt::print("clearing move timer timeout!\n");
				//fmt::print("set state to MOVING\n");
			}
			lastCoordState = newState;
		} catch (ppmac::RuntimeError &e) {
			tu::TranslateException(e);
		}
	}
}

void PowerPMAC_CoordinateSystems::CoordinateSystemChanged(int32_t axis) {
	UpdateAxisToMatchCurrent(axis);
}
void PowerPMAC_CoordinateSystems::UpdateAxisToMatchCurrent(int32_t axis) {
	for(int32_t i = 0; i < ppmac::AvailableAxis::maxAxis; i++) {
		bool isSet = ppmac::bits::isSet(axis, i);
		auto it = attribs.find(i);
		if(isSet && it == attribs.end()) {
			auto attribName = ppmac::AvailableAxis::MapAxisToString(i);
			// tango deletes the attrib prt we pass...
			MyAttrib* attrib = new MyAttrib(i, attribName);
			Tango::UserDefaultAttrProp	prop;
			attrib->set_default_properties(prop);
			attrib->set_disp_level(Tango::OPERATOR);
			add_attribute(attrib);
			attribs[i] = attribName;
		} else if(!isSet && it != attribs.end()) {
			remove_attribute(it->second);
			attribs.erase(it);
		}
	}
}
double PowerPMAC_CoordinateSystems::ReadAxisAttrib(int32_t axis) {
	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		auto coordInfo = ci.GetCoordInfo(coordId);
		double pos = coordInfo.position.array[axis];
		//fmt::print("coord:{}, axis:{}, value:{}\n", coordinateIndex, axis, pos);
		return pos;
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
	return -1;
}
void PowerPMAC_CoordinateSystems::WriteAxisAttrib(int32_t axis, double value) {
	try {
		ppmac::CoreInterface& ci = ppmac::GetCoreObject();
		ci.ExecuteCommand(ppmac::cmd::CoordMoveAxis(coordId, ppmac::AvailableAxis::MapAxisToString(axis) ,value));
		movingTimerHandle = ci.AddDeadTimer(std::chrono::milliseconds{50}, [this](){
			if(get_state() == Tango::MOVING) {
				set_state(Tango::ON);
				movingTimerHandle = ppmac::INVALID_HANDLE;
			}
		});
		set_state(Tango::MOVING);
	} catch (ppmac::RuntimeError& e) {
		tu::TranslateException(e);
	}
}
bool PowerPMAC_CoordinateSystems::IsAxisAttribAccessible(int32_t axis, Tango::AttReqType type) {
	(void)axis;
	if(type == Tango::AttReqType::READ_REQ) {
		return get_state() != Tango::OFF;
	} else {
		return get_state() == Tango::ON;
	}
}

void PowerPMAC_CoordinateSystems::ClearMoveStatusWaitTimer() {
	ppmac::CoreInterface& ci = ppmac::GetCoreObject();
	if(movingTimerHandle != ppmac::INVALID_HANDLE) {
		ci.RemoveDeadTimer(movingTimerHandle);
		movingTimerHandle = ppmac::INVALID_HANDLE;
	}
}

void PowerPMAC_CoordinateSystems::UpdateStateFromCurrentStatus(uint64_t coordStatus) {
	bool badState = false;

	if(ppmac::bits::AnyBitSet(coordStatus, ppmac::coordHardErrorStatusBits)) {
		set_state(Tango::DISABLE);
		badState = true;
	}
	else if(ppmac::bits::AnyBitSet(coordStatus, ppmac::coordSoftErrorStatusBits)) {
		set_state(Tango::FAULT);
		badState = true;
	}
	else if(!ppmac::bits::AllBitsSet(coordStatus, ppmac::coordNeededStatusBits)) {
		set_state(Tango::INIT);
		badState = true;
	}
	if(badState) {
		auto needed = ppmac::states::GetCoordStateNamesForFlagMatch(coordStatus, ppmac::coordNeededStatusBits, 0x0);
		auto softError = ppmac::states::GetCoordStateNamesForFlagMatch(coordStatus, ppmac::coordSoftErrorStatusBits);
		auto hardError = ppmac::states::GetCoordStateNamesForFlagMatch(coordStatus, ppmac::coordHardErrorStatusBits);
		set_status(fmt::format("Check coord status\nMissing: {}\nSoft Errors: {}\nHard Errors: {}", needed, softError, hardError));
	}
	else {
		if (ppmac::bits::isSet(coordStatus, ppmac::MotorStatusBits::DestVelZero)) {
			set_state(Tango::ON);
		} else {
			set_state(Tango::MOVING);
		}
		set_status(Tango::StatusNotSet);
	}
}

/*----- PROTECTED REGION END -----*/	//	PowerPMAC_CoordinateSystems::namespace_ending
} //	namespace
