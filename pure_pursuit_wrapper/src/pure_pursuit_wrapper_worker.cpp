/*
 * Copyright (C) 2018-2020 LEIDOS.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include "pure_pursuit_wrapper/pure_pursuit_wrapper_worker.hpp"

namespace pure_pursuit_wrapper {

autoware_msgs::Waypoint PurePursuitWrapperWorker::TrajectoryPlanPointToWaypointConverter(double current_time, geometry_msgs::PoseStamped pose, cav_msgs::TrajectoryPlanPoint tpp, cav_msgs::TrajectoryPlanPoint tpp2) {

  autoware_msgs::Waypoint waypoint;


  waypoint.pose.pose.position.x = tpp.x;
  waypoint.pose.pose.position.y = tpp.y;
  double delta_x = tpp.x - tpp2.x;
  double delta_y = tpp.y - tpp2.y;
  double delta_pos = sqrt(delta_x * delta_x + delta_y * delta_y);
  double delta_t_second = (double)abs(tpp2.target_time - tpp.target_time) / 1e9;

  if(delta_t_second != 0) {
    waypoint.twist.twist.linear.x = delta_pos / delta_t_second;
  }
  else {
    waypoint.twist.twist.linear.x = 0;
  }

  return waypoint;
};

}
