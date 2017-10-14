/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include "camera_aravis/CameraAravis.hpp"

using namespace camera;
using namespace camera_aravis;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}


bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    if(_reset_device_on_startup.value())
    	CameraAravis::resetCamera(_camera_id.value());

    CameraAravis* camera = new CameraAravis();
    camera->openCamera(_camera_id.value(), _eth_packet_size.value());

    if(_reset_timestamp.value())
        camera->resetTimestamp();

    cam_interface = camera;
    cam_interface->setCallbackFcn(triggerFunction,this);
    cam_interface->setErrorCallbackFcn(errorFunction,this);

    return true;
}

void Task::connectionLost()
{

    RTT::log(RTT::Error) << "Connection Lost" << RTT::endlog();
    exception(LOST_CONNECTION);
}

void camera_aravis::triggerFunction(const void *p)
{
	((RTT::TaskContext*)p)->getActivity()->trigger();
}

void camera_aravis::errorFunction(const void *p)
{
    ((Task*)p)->connectionLost();
}
