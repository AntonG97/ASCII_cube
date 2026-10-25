#include <memory>
#include "Shape.h"

enum class Status : int
{
    NOT_SET = 0,
    INCORRECT_ARGS = 1
};

struct Resolution
{
    int width_;
    int height_;
    Resolution() :
    width_(static_cast<int>(Status::NOT_SET)),
    height_(static_cast<int>(Status::NOT_SET))
    {

    }
};

struct ParsedPacket
{
public:
    std::unique_ptr<Shape> shape_;
    int scale_;
    bool isColorSet_;
    Resolution resolution_;

    ParsedPacket() :
    shape_(nullptr),
    scale_(static_cast<int>(Status::NOT_SET)),
    isColorSet_(static_cast<bool>(Status::NOT_SET)),
    resolution_()
    {

    }

    ParsedPacket(ParsedPacket& rhs) :
    shape_(std::move(rhs.shape_)),
    scale_(rhs.scale_),
    isColorSet_(rhs.isColorSet_),
    resolution_(rhs.resolution_)
    {

    }
};
