import std;
import lotus;

using namespace std;

void timeout(int seconds);

int main(int argc, char **args) {
    std::cout << "Starting Lotus Game Engine Testing Playground..." << std::endl;
    std::thread([] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cerr << "Timeout reached. Terminating program.\n";
        std::exit(0);
    }).detach();

    GameObject sq1;
    GameObject sq2(0.1, 0.1);

    State state;
    state.objs.insert(state.objs.end(), {&sq1, &sq2});
    RenderManager renderManager;
    GameLoop gameLoop(&renderManager, &state);

    for (int i = 0; i < argc; i++) {
        if (strcmp(args[i], "-w") == 0) {
            renderManager.setWireframeMode(true);
        }
        if (strcmp(args[i], "-t") == 0) {
            cout << "hI";
        }
    }

    return gameLoop.execute();
}
