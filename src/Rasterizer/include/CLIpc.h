#pragma once

#include <cstddef>

#include "IDisplay.h"

class CLIpc : public IDisplay
{
private:
    bool colorIsSet_;
    bool firstFrame_ = true;

public:
    explicit CLIpc(bool colorIsSet);
    ~CLIpc() override;
    void drawPixel(std::size_t x, std::size_t y, char pixel) override;
    void drawBuffer(const RowView& row) override;
    void clear() override;
    std::size_t getWidth() const override;
    std::size_t getHeight() const override;
};