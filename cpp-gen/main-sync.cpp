#include "tasklist-example-app.hpp"

#include "objectbox-sync.hpp"

using namespace obx;

int main(int argc, char* argv[]) {
    // this example expect sync-server to be running locally
    std::string syncServerURL = "ws://127.0.0.1:9999";

    std::cout << "This is a simple example of a ObjectBox Sync client application." << std::endl
              << "To execute this example yourself, you need to start a sync-server locally:" << std::endl
              << "    ./sync-server --model objectbox-model.json -d server-db --unsecured-no-authentication"
              << " --bind " + syncServerURL << std::endl
              << "Note: update the --model argument path to the model file from this example directory." << std::endl
              << "You can launch multiple instances of this program in parallel in two windows, each with" << std::endl
              << "a separate database by starting each with a different `--directory dirname` argument." << std::endl
              << "The clients automatically connect to the sync-server (URL specified in main-sync.cpp)." << std::endl
              << "See sync in action: create tasks on one client and refresh the list on the other." << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;

    // create_obx_model() provided by objectbox-model.h
    // obx interface contents provided by objectbox.hpp
    Store::Options storeOptions(create_obx_model());

    if (int err = processArgs(argc, argv, storeOptions)) {
        return err;
    }

    Store store(storeOptions);

    // Note: server is expected to be set up with no authentication for this demo
    std::shared_ptr<SyncClient> client = Sync::client(store, syncServerURL, SyncCredentials::none());
    client->start();

    TasklistCmdlineApp app(store);
    return app.run();
}