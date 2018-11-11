#ifndef INC_LAPP_APPLICATION_H_
#define INC_LAPP_APPLICATION_H_
/**
@file Application.h
@author t-sakai
@date 2018/10/29 create
*/
#include "lapp.h"

namespace lgfx
{
    class Window;
}

namespace lapp
{
    class Application
    {
    public:
        virtual ~Application();
        virtual bool initialize(InitParam& initParam) =0;
        virtual void terminate() =0;
        virtual bool update() =0;

        virtual lgfx::Window& getWindow() =0;
    protected:
        LAPP_NON_COPYABLE(Application);

        Application();
    };
}
#endif //INC_LAPP_APPLICATION_H_
