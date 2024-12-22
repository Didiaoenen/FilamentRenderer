#pragma once

#include "CommandlineConfig.h"

namespace matc
{
    class FileConfig : public Config {
    public:

        FileConfig(const std::string& path) {
            mInput = new FilesystemInput(path.c_str());
        }
        
        ~FileConfig() override {
            delete mInput;
        };

        Input* getInput() const noexcept override {
            return mInput;
        }

        Output* getOutput() const noexcept override {
            return nullptr;
        }

        std::string toString() const noexcept override {
            return "";
        }

    private:
        FilesystemInput* mInput = nullptr;
    };
}