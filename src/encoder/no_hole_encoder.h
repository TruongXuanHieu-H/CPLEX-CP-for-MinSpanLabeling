#ifndef NO_HOLE_ENCODER_H
#define NO_HOLE_ENCODER_H

#include "encoder.h"

class NoHoleEncoder : public Encoder
{
public:
    IloModel encode_model(ConfigData &config_data, GraphData &graph_data, CPData &cp_data) override;
};

#endif