/**
@file Core.h
@author t-sakai
@date 2018/10/30 create
*/
#include "Core.h"
#include "Application.h"
#include "Input.h"

namespace lapp
{
    Application* Core::application_ = LAPP_NULL;
    Input* Core::input_ = LAPP_NULL;

    bool Core::initialize(InitParam& initParam, Application* app)
    {
        LAPP_ASSERT(LAPP_NULL != app);
        if(LAPP_NULL != application_){
            LAPP_DELETE(app);
            return false;
        }
        if(!app->initialize(initParam)){
            LAPP_DELETE(app);
            return false;
        }

        InputParam inputParam = {app->getWindow().getHandle(), initParam.maxGamePads_, initParam.mouse_, initParam.keyboard_};
        Input* input = LAPP_NEW Input;
        if(!input->initialize(inputParam)){
            input->terminate();
            LAPP_DELETE(input);
            LAPP_DELETE(app);
            return false;
        }

        input_ = input;

        application_ = app;
        return true;
    }

    void Core::terminate()
    {
        if(LAPP_NULL != input_){
            input_->terminate();
            LAPP_DELETE(input_);
        }
        if(LAPP_NULL != application_){
            application_->terminate();
            LAPP_DELETE(application_);
        }
    }

    void Core::update()
    {
        while(application_->update()){
            input_->update();
            Sleep(16);
        }
    }

    Application& Core::getApp()
    {
        return *application_;
    }

    Input& Core::getInput()
    {
        return *input_;
    }
}
