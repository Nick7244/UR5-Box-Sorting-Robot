#include <box_plugin/box_plugin.hpp>
#include <box_msgs/box_position.h>

namespace gazebo {

    // Empty constructor and desctuctor
    BoxPlugin::BoxPlugin(){}
    BoxPlugin::~BoxPlugin(){}
    
    // Load the plugin
    void BoxPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
        world_ptr_ = _parent->GetWorld();
        gazebo_ros_ = GazeboRosPtr(new GazeboRos(_parent, _sdf, "BoxPlugin"));
        
        // Get parameters for the box
        gazebo_ros_->getParameter<std::string>(box_name, "box", "box");
        
        // Create the box position publisher
        pub = gazebo_ros_->node()->advertise<box_msgs::box_position>("box_position",10);

        // Setup the plugin callback
        update_connetion_ = event::Events::ConnectWorldUpdateBegin(boost::bind(&BoxPlugin::UpdateChild, this));
        
    }

    // Callback function for plugin
    void BoxPlugin::UpdateChild()
    {
        // Get gazebo models
        physics::ModelPtr box_ptr = world_ptr_->ModelByName(box_name);
        
        // Get model positions
        ignition::math::Vector3<double> box_pos = box_ptr->WorldPose().Pos();

        // Create message
        box_msgs::box_position myMessage;
        myMessage.x.data = box_pos.X();
        myMessage.y.data = box_pos.Y();
        myMessage.z.data = box_pos.Z();

        // Publish the message
        pub.publish(myMessage);
    }

    GZ_REGISTER_MODEL_PLUGIN ( BoxPlugin )
    
}