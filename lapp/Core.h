#ifndef INC_LAPP_CORE_H_
#define INC_LAPP_CORE_H_
/**
@file Core.h
@author t-sakai
@date 2018/10/30 create
*/
#include "lapp.h"

namespace lapp
{
    class Application;
    class Input;

    class Core
    {
    public:
        static bool initialize(InitParam& initParam, Application* app);
        static void terminate();

        static void update();

        static Application& getApp();
        static Input& getInput();

    private:
        Core(const Core&) = delete;
        Core(Core&&) = delete;
        Core& operator=(const Core&) = delete;
        Core& operator=(Core&&) = delete;

        friend class Application;

        static Application* application_;
        static Input* input_;
    };
}
#endif //INC_LAPP_CORE_H_
