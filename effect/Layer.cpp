/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Layer.h"

F_USE_NAMESPACE

Layer::Layer(Bitmap* pBitmapSize, BlendOp op) :
    Bitmap(pBitmapSize->width(), pBitmapSize->height()),
    _blendOp(op)
{
}

Layer::Layer(int width, int height, BlendOp op) :
    Bitmap(width, height),
    _blendOp(op)
{
}

Layer::~Layer()
{
    clear();
}

void Layer::setBlendOperation(BlendOp op) 
{
    _blendOp = op;
}

void Layer::setAutoClear(bool doAutoClear)
{
    _doAutoClear = doAutoClear;
}

void Layer::render(Bitmap* pTarget, Timing& timing) 
{
    if (!enabled()) {
        return;
    }

    if (_doAutoClear) {
        clear();
    }

    renderChildren(this, timing);
    renderToTarget(pTarget, timing);
}

void Layer::add(Composable* pComposable) 
{
    _children.push_back(pComposable);
}

void Layer::remove(Composable* pComposable)
{
    _children.remove(pComposable);
    delete pComposable;
}

void Layer::removeDisabled()
{
    auto it = _children.begin();
    while (it != _children.end()) {
        if ((*it)->enabled()) {
            ++it;
        }
        else {
            auto eraseIt = it;
            ++it;
            delete *eraseIt;
            _children.erase(eraseIt);
        }
    }
}

void Layer::removeAll()
{
    for (auto pChild : _children) {
        delete pChild;
    }

    _children.clear();
}

void Layer::renderChildren(Bitmap* pTarget, Timing& timing)
{
    for (auto pChild : _children) {
        pChild->render(this, timing);
    }
}

void Layer::renderToTarget(Bitmap* pTarget, Timing& timing)
{
    pTarget->copy(*this, _blendOp);
}