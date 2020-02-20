#include <smacc/smacc.h>
namespace sm_three_some
{
// STATE DECLARATION
class MsRecover : public smacc::SmaccState<MsRecover, SmThreeSome>
{
public:
   using SmaccState::SmaccState;

// TRANSITION TABLE
   typedef mpl::list<
    
   Transition<EvToDeep, sc::deep_history<StState1>, SUCCESS>
   
   >reactions;
};
} // namespace sm_three_some