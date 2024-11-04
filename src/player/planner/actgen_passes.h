// -*-c++-*-


#ifndef ACTGEN_PASSES_H
#define ACTGEN_PASSES_H

#include "action_generator.h"

class ActGen_Passes
    : public ActionGenerator {

public:
    ActGen_Passes();

    virtual
    ~ActGen_Passes();
    virtual
    void generate( std::vector< ActionStatePair > * result,
                   const PredictState & state,
                   const rcsc::WorldModel & wm,
                   const std::vector< ActionStatePair > & path ) const;
};

#endif