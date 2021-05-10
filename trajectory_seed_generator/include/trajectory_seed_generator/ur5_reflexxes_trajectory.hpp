#include <ros/ros.h>

#include <sensor_msgs/JointState.h>

#include <kdl/jntarray.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chainfksolver.hpp>
#include <kdl/chainiksolver.hpp>

#include <ReflexxesTypeII/ReflexxesAPI.h>
#include <ReflexxesTypeII/RMLPositionFlags.h>
#include <ReflexxesTypeII/RMLPositionInputParameters.h>
#include <ReflexxesTypeII/RMLPositionOutputParameters.h>

#include <box_position_subscriber/box_position_subscriber.hpp> 

class ur5_reflexxes_trajectory {

    private:

        ros::NodeHandle nh;
        ros::Subscriber sub_js;
        ros::Publisher pub_traj;

        ReflexxesAPI* rml;
        RMLPositionInputParameters* ip;
        RMLPositionOutputParameters* op;
        RMLPositionFlags flags;

        KDL::Tree tree;
        KDL::Chain chain;
        KDL::ChainFkSolverPos* fk_pos;
        KDL::ChainIkSolverPos* ik_pos;
        KDL::ChainIkSolverVel* ik_vel;

        KDL::JntArray joint_state;

        box_pos_subscriber box_pos_sub;

        void computeTrajectory();

    public:

        ur5_reflexxes_trajectory( ros::NodeHandle& nh, float controllerPeriod );
        ~ur5_reflexxes_trajectory() {};

        void generateSeedTrajectory();
        void TPoseTrajectory();

        void jointStateCallback(const sensor_msgs::JointState& js );

};