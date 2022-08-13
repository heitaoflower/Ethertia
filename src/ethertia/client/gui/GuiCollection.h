//
// Created by Dreamtowards on 2022/5/2.
//

#ifndef ETHERTIA_GUICOLLECTION_H
#define ETHERTIA_GUICOLLECTION_H

#include "Gui.h"

class GuiCollection : public Gui
{
    std::vector<Gui*> _children;

public:
    GuiCollection() {
        setWidth(-Inf);
        setHeight(-Inf);
    }

    int count() const override {
        return _children.size();
    }
    Gui* at(int i) override {
        return _children.at(i);
    }
    Gui* last() {
        return at(count()-1);
    }

    void addGui(Gui* g, uint idx) {
        if (g->getParent()) throw std::logic_error("Cannot attach. it belongs to another.");
        _children.insert(_children.begin()+idx, g);
        g->attach(this);
    }
    Gui* addGui(Gui* g) {
        addGui(g, count());
        return this;
    }
    Gui* addGuis(std::initializer_list<Gui*> ls) {
        for (Gui* g : ls) {
            addGui(g);
        }
        return this;
    }

    void removeGui(int idx) {
        auto it = _children.begin()+idx;
        _children.erase(it);
        (*it)->detach();
    }
    void removeGui(Gui* g) {
        removeGui(Collections::find(_children, g));
    }
    void removeLastGui() {
        removeGui(count()-1);
    }
    void removeAllGuis() {
        while (count()) {
            removeLastGui();
        }
    }

    void setGui(uint idx, Gui* g) {
        removeGui(idx);
        addGui(g, idx);
    }

};

#endif //ETHERTIA_GUICOLLECTION_H