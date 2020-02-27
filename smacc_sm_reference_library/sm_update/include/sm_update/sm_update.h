#include <smacc/smacc.h>

// CLIENTS
#include <ros_timer_client/cl_ros_timer.h>

// ORTHOGONALS
#include <sm_update/orthogonals/or_timer.h>

//CLIENT BEHAVIORS
#include <ros_timer_client/client_behaviors/cb_timer_countdown_loop.h>
#include <ros_timer_client/client_behaviors/cb_timer_countdown_once.h>

using namespace boost;
using namespace smacc;

namespace sm_update
{

//STATE
class State1;
class State2;

//--------------------------------------------------------------------
//STATE_MACHINE
struct SmUpdate
    : public smacc::SmaccStateMachineBase<SmUpdate, State1>
{
    using SmaccStateMachineBase::SmaccStateMachineBase;

    virtual void onInitialize() override
    {
        this->createOrthogonal<OrTimer>();
    }
};

} // namespace sm_update

#include <sm_update/states/st_state_1.h>
#include <sm_update/states/st_state_2.h>