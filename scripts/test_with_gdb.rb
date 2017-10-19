require 'orocos'
include Orocos

Orocos.initialize

Orocos.run 'camera_aravis::Task' => 'camera', :gdb=>true  do

    camera = Orocos.name_service.get 'camera'

    Orocos.conf.load_dir('.')

    Orocos.conf.apply(camera,['default', 'spare_camera'], :override => true)

    camera.configure
    camera.start

    Orocos.watch(camera)
    puts "done."

end

