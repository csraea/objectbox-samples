#define OBX_CPP_FILE
#include "tasklist-example-app.hpp"

int main(int argc, char* argv[]) {
    // create_obx_model() provided by objectbox-model.h
    // obx interface contents provided by objectbox.hpp
    obx::Options options(create_obx_model());

    if (int err = processArgs(argc, argv, options)) {
        return err;
    }

    obx::Store store(options);
    TasklistCmdlineApp app(store);
    return app.run();
}