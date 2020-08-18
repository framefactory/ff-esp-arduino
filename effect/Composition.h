/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_COMPOSITION_H
#define _ESP_EFFECT_COMPOSITION_H

#include "library.h"
#include "Bitmap.h"
#include "Layer.h"

#include <vector>

F_BEGIN_NAMESPACE

class Effect;
class Timing;

class Composition : public Bitmap
{
public:
    typedef std::vector<Layer*> layerVec_t;

    Composition(int width, int height);
    virtual ~Composition();

    void fetchRealTime(float timezoneOffset, float dstOffset);
    bool render();

    size_t addLayer(Layer* pLayer);
    Layer* addEffectLayer(Effect* pEffect, MixOp op = Or);
    void insertLayerAt(Layer* pLayer, size_t index);
    void removeLayerAt(size_t index);

    Layer* layer(int index) const { return _layers[index]; }
    size_t numLayers() const { return _layers.size(); }

    const Timing* timing() const { return _pTiming; }

private:
    layerVec_t _layers;
    Timing* _pTiming;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_COMPOSITION_H