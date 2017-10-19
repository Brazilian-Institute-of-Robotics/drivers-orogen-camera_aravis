require 'orocos'
require 'vizkit'
include Orocos

Orocos.initialize

Orocos.run 'camera_aravis::Task' => 'camera'  do

    camera = Orocos.name_service.get 'camera'

    Orocos.conf.load_dir('.')

    Orocos.conf.apply(camera,['default', 'spare_camera'], :override => true)

    camera.configure
    camera.start

    task_inspector = Vizkit.default_loader.TaskInspector
    Vizkit.display camera, :widget => task_inspector
    Vizkit.exec
end

