/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_LAYER_H
#define _ESP_EFFECT_LAYER_H

#include "../library.h"
#include "Composable.h"
#include "Bitmap.h"
#include "Effect.h"

#include <list>

F_BEGIN_NAMESPACE

class Layer : public Bitmap, Composable
{
public:
    Layer(Bitmap* pBitmapSize, BlendOp op = Or);
    Layer(int width, int height, BlendOp = Or);
    virtual ~Layer();


    /// Sets the blend operation used when composing this layer.
    void setBlendOperation(BlendOp op);
    /// Returns the blend operation used when composing this layer.
    BlendOp blendOperation() const { return _blendOp; }

    /// Clears the layer before rendering. Default is true.
    void setAutoClear(bool doAutoClear);
    /// Returns true if the layer is cleared before rendering.
    bool autoClear() const { return _doAutoClear; }

    /// Draws this layer onto the given target bitmap using the layer's blend operation.
    void render(Bitmap* pTarget, Timing& timing) override;

    /// Adds the given composable layer or effect to this layer. Takes ownership.
    void add(Composable* pComposable);
    /// Removes a layer or effect and deletes it.
    void remove(Composable* pComposable);
    /// Removes and deletes all disabled composables.
    void removeDisabled();
    /// Removes and deletes all layers and effects.
    void removeAll();

    /// Returns the number of layers and effects added to this layer.
    size_t size() const { return _children.size(); }

protected:
    /// Renders all children to the given target bitmap.
    virtual void renderChildren(Bitmap* pTarget, Timing& timing);
    /// Renders this layer to the given target bitmap.
    virtual void renderToTarget(Bitmap* pTarget, Timing& timing);

private:
    typedef std::list<Composable*> composableList_t;
    composableList_t _children;
    
    BlendOp _blendOp;

    bool _doAutoClear = false;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_LAYER_H