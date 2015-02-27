
#include <iostream>

#include <tf/tf.h>

#include <rosbag/bag.h>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH


int main(int argc, char** argv) {

  std::string bag_path(argv[1]);
  std::string from_frame(argv[2]);
  std::string to_frame(argv[3]);

  rosbag::Bag bag;
  bag.open(bag_path, rosbag::bagmode::Read);

  std::vector<std::string> topics;
  topics.push_back(std::string("tf"));

  rosbag::View view(bag, rosbag::TopicQuery(topics));

  tf::Transformer optimus_prime;

  // TODO: set start time
  ros::Time now;

  foreach(rosbag::MessageInstance const m, view)
  {
    tf::tfMessage::ConstPtr transforms = m.instantiate<tf::tfMessage>();
    if (transforms) {
      foreach(geometry_msgs::TransformStamped const t, transforms->transforms) {
        // TODO: convert t from geometry_msgs::TransformStamped to tf::StampedTransform
        optimus_prime.setTransform(transform);
      }

      if(optimus_prime.canTransform(to_frame, from_frame, now)) {
        tf::StampedTransform resolved;
        optimus_prime.lookupTransform(to_frame, from_frame, now, resolved);

        // TODO: print or save resolved transform

        // Incerement now
        now = now+ros::Duration(0.1);
      }
    }
  }


  return 0;
}
