#include "../include/App.hpp"
#include "../include/EasyWindow/EasyWindow.hpp"
#include <iostream>

App::App(RunType run_type): do_exit(false), exit_code(0)
{
    switch(run_type)
    {
    case RunType::Manual:
        this->state = AppState::MainMenu;
        break;
    case RunType::Scheduled:
        this->state = AppState::Exercise;
        break;
    }
}

int App::run()
{
    while(!this->do_exit)
    {
        switch(this->state)
        {
        case AppState::MainMenu:
            this->mainMenu();
            break;
        case AppState::Exercise:
            this->exercise();
            break;
        }
    }
    return this->exit_code;
}

void App::mainMenu()
{
    constexpr int exercise_button = 1;
    constexpr int label = 2;
    constexpr int text_input = 3;
    constexpr int ok_button = 4;
    constexpr int close_button = 5;
    EasyWindow window({500,500},"ExExExExercise Time! - Main Menu");
    window.addButton(exercise_button,{200,150},"Let's do exercise!",
        {
            {"onclick",[&](){
                this->state = AppState::Exercise;
                window.close();
            }}
        }
    );
    window.addTextView(label,{100,225},"Enter the time to do exercise:");
    window.addTextInput(text_input,{100,300});
    window.addButton(ok_button,{100,375},"Ok",
        {
            {"onclick",[&](){
                std::cout << "Content: " << window.getElementDataByIdentifier(text_input)["content"] << std::endl;
                /* Save data to storage */
            }}
        });
    window.addButton(close_button,{300,375},"Close",
        {
            {"onclick",[&](){
                this->do_exit = true;
                window.close();
            }}
        });
    window.run(
        {
            {"close",[&](){
                this->do_exit = true;
                window.close();
            }}
        });
}

void App::exercise()
{
    constexpr int emergency_button = 1;
    constexpr int leave_button = 2;
    EasyWindow window({500,500},"ExExExExercise Time! - Exercise Menu");
    window.addButton(emergency_button,{200,250},"Emergency!",
                     {
                         {"onclick",[&](){
                            std::cout << "Emergency button used!" << std::endl;
                            /* Do if emergency button cooldown is over */
                                window.close();
                                this->do_exit = true;
                                /* Set emergency button cooldown */
                            /* Else if emergency button cooldown is over */
                                /* Display error message */
                         }}
                    });
    window.addButton(leave_button,{200,300},"Leave!",
                     {
                         {"onclick",[&](){
                            window.close();
                            this->do_exit = true;
                         }}
                     });
    /* Hide Leave button for X seconds */
    window.run();
}
