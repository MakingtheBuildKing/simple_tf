#include <iostream>
#include <thread>

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

class TFM{

    public:

    TFM();
    ~TFM();

    private:

    ros::NodeHandle nh;    
    int task();
};

TFM::TFM(){

    nh = ros::NodeHandle();
    task();
}

TFM::~TFM(){}

int TFM::task(){

    ros::Rate spinRate(60);
    tf::TransformListener tfl_turtle1;

    while(ros::ok()){

        tfl_turtle1.waitForTransform("/world", "/turtle1", ros::Time(0), ros::Duration(1));
        tf::StampedTransform stf_turtle1;

        try{

            tfl_turtle1.lookupTransform("/world", "/turtle1", ros::Time(0), stf_turtle1);
            ROS_INFO("<- Current ROS time");
            printf(
            "         %d.%d <- tf timestamp\n   frame ID       : %s\n   child frame ID : %s\n       transform:\n           tx : %f\n           ty : %f\n           tz : %f\n\n           qx : %f\n           qy : %f\n           qz : %f\n           qw : %f\n",stf_turtle1.stamp_.sec, stf_turtle1.stamp_.nsec,
            stf_turtle1.frame_id_.c_str(), stf_turtle1.child_frame_id_.c_str(), stf_turtle1.getOrigin().x(), stf_turtle1.getOrigin().y(), stf_turtle1.getOrigin().z(), stf_turtle1.getRotation().x(), stf_turtle1.getRotation().y(), stf_turtle1.getRotation().z(), stf_turtle1.getRotation().w());
        }
        catch(tf::TransformException &ex){
            ROS_ERROR("Invalid Transform : %s", ex.what());
        }

        ros::spinOnce();
        spinRate.sleep();
    }
    return 0;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "simple_tf");

    TFM simtf;

    ros::Rate spinRate(60);

    while(ros::ok()){

        spinRate.sleep();
        ros::spinOnce();
    }
}
    