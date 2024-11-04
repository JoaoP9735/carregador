// -*-c++-*-



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "actgen_passes.h"

#include "strict_check_pass_generator.h"

#include "action_state_pair.h"
#include "predict_state.h"

#include <rcsc/common/logger.h>

//#define DEBUG_PRINT

using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!


 */

/*-------------------------------------------------------------------*/
/*!

 */
ActGen_Passes::ActGen_Passes()
{

}

/*-------------------------------------------------------------------*/
/*!

 */
ActGen_Passes::~ActGen_Passes()
{

}
void
ActGen_Passes::generate( std::vector< ActionStatePair > * result,
                                  const PredictState & state,
                                  const WorldModel & wm,
                                  const std::vector< ActionStatePair > & path ) const
{


    const std::vector< CooperativeAction::Ptr > &
        courses = StrictCheckPassGenerator::instance().courses( wm );

    //
    // add pass course candidates
    //
    const std::vector< CooperativeAction::Ptr >::const_iterator end = courses.end();
    for ( std::vector< CooperativeAction::Ptr >::const_iterator act = courses.begin();
          act != end;
          ++act )
    {
        if ( (*act)->targetPlayerUnum() == Unum_Unknown )
        {
#ifdef DEBUG_PRINT
            dlog.addText( Logger::ACTION_CHAIN,
                          __FILE__": can't pass from %d,"
                          " target invalid",
                          state.ballHolder()->unum() );
#endif
            continue;
        }

        const AbstractPlayerObject * target_player = state.ourPlayer( (*act)->targetPlayerUnum() );

        if ( ! target_player )
        {
#ifdef DEBUG_PRINT
            dlog.addText( Logger::ACTION_CHAIN,
                          __FILE__": can't pass from %d to %d, NULL target player",
                          state.ballHolder()->unum(),
                          (*act)->targetPlayerUnum() );
#endif
            continue;
        }

        result->push_back( ActionStatePair( *act,
                                            new PredictState( state,
                                                              (*act)->durationStep(),
                                                              (*act)->targetPlayerUnum(),
                                                              (*act)->targetPoint() ) ) );
    }
}
