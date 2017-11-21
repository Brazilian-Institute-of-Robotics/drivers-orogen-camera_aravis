/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include "camera_aravis/CameraAravis.hpp"

using namespace camera;
using namespace camera_aravis;

Task::Task(std::string const& name)
    : TaskBase(name), m_lost_connection(false)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine), m_lost_connection(false)
{
}

Task::~Task()
{
}


bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    m_lost_connection = false;
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

void Task::updateHook()
{
    if (m_lost_connection)
        exception(LOST_CONNECTION);
    else
        TaskBase::updateHook();
}

void Task::connectionLost()
{

    RTT::log(RTT::Error) << "Connection Lost" << RTT::endlog();
    m_lost_connection = true;
}

void camera_aravis::triggerFunction(const void *p)
{
	((RTT::TaskContext*)p)->getActivity()->trigger();
}

void camera_aravis::errorFunction(const void *p)
{
    ((Task*)p)->connectionLost();
    ((RTT::TaskContext*)p)->getActivity()->trigger();
}
