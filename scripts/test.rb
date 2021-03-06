require 'vizkit'


Orocos::initialize


Orocos.run "camera_aravis::Task"=> "Task" do
    task = Orocos::TaskContext.get("Task")
    #task.camera_id = "24934672"
#    task.camera_id = "The Imaging Source Europe GmbH-29210317"
#    task.camera_id = "Aravis-GV01"
    task.camera_id = "The Imaging Source Europe GmbH-42210449"
    task.width = 1280
    task.height = 960
    task.exposure = 10000
    task.gain = 1
    task.exposure_mode = 'auto'
    task.camera_format = :MODE_BAYER
    task.whitebalance_mode = 'auto'
    task.fps = 4

    task.configure
    task.start
    Orocos.log_all_ports
    Vizkit.display task
    Vizkit.display task.frame
    
    Vizkit.exec
end
