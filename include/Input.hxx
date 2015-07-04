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

        bool _moveUp;
        bool _moveDown;
        bool _moveRight;
        bool _moveLeft;
        bool _quit;

    private:


};

#endif // INPUT_H
