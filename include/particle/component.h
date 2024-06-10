#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
    

public:
    float x;
    float y;

    Component();
    Component(float x, float y);

    void set(Component comp);

    void add(Component comp);
};

#endif