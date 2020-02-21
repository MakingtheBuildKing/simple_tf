# Requirements

* [ROS Kinetic Kame](http://wiki.ros.org/kinetic/Installation/Ubuntu)
* ROS turtlesim

# Introduction

## simple_tf_listener
Receive and print `/world` to `/turtle` tf message

## simple_tf_isCaptured
An application of [simple_tf_listener](#simple_tf_listener)

## simple_tf_pass
Receive `/world` to `/turtle` tf message and make `/base` to `/turtle` tf message


# Getting Started

1. Launch turtlesim

    ```bash
    roslaunch turtle_tf turtle_tf_demo.launch
    ```
* ## simple_tf_isCaptured
    Create another terminal (ctrl + alt + t)

    ```bash
    rosrun simple_tf simple_tf_listener
    ```
    then,
    ```
    frame ID       : world
    child frame ID : turtle1
        transform:
            tx : 5.544445
            ty : 5.544445
            tz : 0.000000

            qx : 0.000000
            qy : 0.000000
            qz : 0.000000
            qw : 1.000000
    ```

* ## simple_tf_isCaptured
    Create another terminal (ctrl + alt + t)
    ```bash
    rosrun simple_tf simple_tf_isCaptured
    ```
    calculate euclidean distance between two turtles.

    then,
    ```
    [ INFO] [1582275234.157522787]: 
    turtle1 X turtle2
    timestamp distance
        0.-16150952
    euclidian distance
        0.003930
    is Captured? : Yes! or Nope
    ```
* ## simple_tf_pass
    Create another terminal (ctrl + alt + t)
    ```bash
    rosrun simple_tf simple_tf_pass
    ```
    see [this](#simple_tf_pass)