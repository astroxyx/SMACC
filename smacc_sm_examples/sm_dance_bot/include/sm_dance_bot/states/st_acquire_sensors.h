using namespace smacc;

struct StAcquireSensors : 
      smacc::SmaccState<StAcquireSensors, SmDanceBot>
{
   using SmaccState::SmaccState;

   typedef mpl::list<
       
       // Expected event
       sc::transition<EvStateFinish<StAcquireSensors>, StNavigateToWaypointsX>,
       
       // Keyboard event
       sc::transition<EvKeyPressN<SbKeyboard>, StNavigateToWaypointsX>,

       // Sensor events
       sc::custom_reaction<EvTopicMessage<LidarSensor>>,
       sc::custom_reaction<EvTopicMessage<smacc::SensorTopic<sensor_msgs::Temperature>>>
       >
       reactions;

   AllEventAggregator allSensorsReady;

   void onInitialize()
   {
      this->configure<ObstaclePerceptionOrthogonal>(std::make_shared<LidarSensor>("/front/scan", 1, ros::Duration(10)));
      this->configure<SensorOrthogonal>(std::make_shared<SbConditionTemperatureSensor>("/temperature"));
      this->configure<KeyboardOrthogonal>(std::make_shared<SbKeyboard>());
      this->configure<PublisherOrthogonal>(std::make_shared<SbStringPublisher>("Hello World!"));

      allSensorsReady.setTriggerEventTypesCount(2);
   }
   
   sc::result react(const EvTopicMessage<LidarSensor> &ev)
   {
      ROS_INFO_ONCE("Lidar sensor is ready");

      if (allSensorsReady.notify(ev))
         this->throwFinishEvent();

      return discard_event();
   }

   sc::result react(const EvTopicMessage<smacc::SensorTopic<sensor_msgs::Temperature>> &ev)
   {
      ROS_INFO_ONCE("Temperature sensor is ready");
      if (allSensorsReady.notify(ev))
         this->throwFinishEvent();

      return discard_event();
   }
};