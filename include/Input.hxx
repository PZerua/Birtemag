#ifndef INPUT_H
#define INPUT_H
#include "../include/Common_libs.hxx"

class Input
{
    public:
        Input();
        virtual ~Input();
        //void Player_Control();
        void checkControls(SDL_Event *events);

        bool _quit;
        bool _mouseClick;
        bool _f2;
        bool _f3;

    private:


};

#endif // INPUT_H
