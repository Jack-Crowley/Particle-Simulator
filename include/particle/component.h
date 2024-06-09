#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
    float x;
    float y;

public:
    Component();
    Component(float x, float y);

    void set(Component comp);

    void add(Component comp);
};

#endif