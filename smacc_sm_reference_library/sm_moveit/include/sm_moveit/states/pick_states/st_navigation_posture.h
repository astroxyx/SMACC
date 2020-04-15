#pragma once

namespace sm_moveit
{
namespace pick_states
{
// STATE DECLARATION
struct StNavigationPosture : smacc::SmaccState<StNavigationPosture, SS>
{
    using SmaccState::SmaccState;

    // TRANSITION TABLE
    typedef mpl::list<
        //Transition<MoveGroupMotionExecutionSucceded<ClMoveGroup, OrArm>, StCloseGripper>
        Transition<MoveGroupMotionExecutionFailed<ClMoveGroup, OrArm>, StNavigationPosture, ABORT>>
        reactions;

    // STATE FUNCTIONS
    static void staticConfigure()
    {
        configure_orthogonal<OrArm, CbMoveRelative>();
    }

    void runtimeConfigure()
    {
        ClMoveGroup *moveGroupClient;
        this->requiresClient(moveGroupClient);

        ClPerceptionSystem *perceptionSystem;
        this->requiresClient(perceptionSystem);

        //geometry_msgs::Transform transform;
        //transform.rotation.w=1;
        auto moveCartesianRelative = this->getOrthogonal<OrArm>()->getClientBehavior<CbMoveRelative>();

        auto quat = tf::createQuaternionFromRPY(M_PI, 0, 0);
        moveCartesianRelative->transform_.translation.z = 0.05;
        tf::quaternionTFToMsg(quat, moveCartesianRelative->transform_.rotation);

        auto currentTable = perceptionSystem->getCurrentTable();
        if (currentTable == RobotProcessStatus::TABLE0)
        {
            moveCartesianRelative->transform_.translation.x = -0.15;
        }
        else if (currentTable == RobotProcessStatus::TABLE1)
        {
            moveCartesianRelative->transform_.translation.x = 0.15;
        }

        moveGroupClient->onMotionExecutionSuccedded(&StNavigationPosture::throwSequenceFinishedEvent, this);
    }
};

} // namespace pick_states
} // namespace sm_moveit