import std;
import lotus;

using namespace std;

static void startTerminationTimer() {
    std::thread([] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cerr << "Timeout reached. Terminating program.\n";
        std::exit(0);
    }).detach();
}

int main(int argc, char **args) {
    std::cout << "Starting Lotus Game Engine Testing Playground..." << std::endl;

    State state;
    state.objs.emplace_back();
    state.objs.emplace_back(0.1, 0.1);
    RenderManager renderManager;
    GameLoop gameLoop(&renderManager, &state);

    for (int i = 0; i < argc; i++) {
        if (strcmp(args[i], "-w") == 0) {
            renderManager.setWireframeMode(true);
        }
        if (strcmp(args[i], "-t") == 0) {
            startTerminationTimer();
        }
    }

    return gameLoop.execute();
}
