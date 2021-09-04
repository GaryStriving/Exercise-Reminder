enum class AppState
{
    MainMenu,
    Exercise,
};

enum class RunType
{
    Scheduled,
    Manual,
};

class App
{
private:
    bool do_exit;
    int exit_code;
    AppState state;
    void mainMenu();
    void exercise();
public:
    App(RunType run_type);
    int run();
};
