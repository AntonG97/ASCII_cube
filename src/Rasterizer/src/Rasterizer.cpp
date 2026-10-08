#include "Rasterizer.h"

#include <algorithm>
#include <array>
#include <cmath>

namespace
{
    struct ScreenVertex
    {
        double x;
        double y;
        double z;
    };

    double edge(const ScreenVertex& a, const ScreenVertex& b, double x, double y)
    {
        return (x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x);
    }
}

Rasterizer::Rasterizer(Shape& shape, IDisplay& display, Transformation& transformation) :
    shape_(shape),
    transformation_(transformation),
    display_(display),
    buffer_(display.getWidth(), display.getHeight())
{
}

void Rasterizer::render()
{
    transformation_.transform();
    buffer_.clear();

    constexpr std::array<char, 6> pixels{'#', 'o', '=', '*', '%', '$'};
    const std::vector<Face>& faces = shape_.getFaces();
    for (std::size_t index = 0; index < faces.size(); ++index)
    {
        fillFace(faces[index], pixels[index % pixels.size()]);
    }

    display_.clear();
    for (FrameBuffer::Iterator row = buffer_.begin(); row != buffer_.end(); ++row)
    {
        const RowView rowView = *row;
        display_.drawBuffer(rowView);
    }
}

void Rasterizer::fillFace(const Face& face, char pixel)
{
    const auto toScreen = [this](const Vec3& vertex)
    {
        return ScreenVertex{
            (vertex.x_ + 0.5) * static_cast<double>(buffer_.width()),
            (0.5 - vertex.y_) * static_cast<double>(buffer_.height()),
            vertex.z_
        };
    };

    const ScreenVertex a = toScreen(face.a_);
    const ScreenVertex b = toScreen(face.b_);
    const ScreenVertex c = toScreen(face.c_);
    const double area = edge(a, b, c.x, c.y);
    if (std::abs(area) < 1e-9)
    {
        return;
    }

    const int maxScreenX = static_cast<int>(buffer_.width()) - 1;
    const int maxScreenY = static_cast<int>(buffer_.height()) - 1;
    const int minX = std::max(0, static_cast<int>(std::floor(std::min({a.x, b.x, c.x}))));
    const int maxX = std::min(maxScreenX, static_cast<int>(std::ceil(std::max({a.x, b.x, c.x}))));
    const int minY = std::max(0, static_cast<int>(std::floor(std::min({a.y, b.y, c.y}))));
    const int maxY = std::min(maxScreenY, static_cast<int>(std::ceil(std::max({a.y, b.y, c.y}))));

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            const double sampleX = static_cast<double>(x) + 0.5;
            const double sampleY = static_cast<double>(y) + 0.5;
            const double weightA = edge(b, c, sampleX, sampleY) / area;
            const double weightB = edge(c, a, sampleX, sampleY) / area;
            const double weightC = edge(a, b, sampleX, sampleY) / area;

            if (weightA >= -1e-9 && weightB >= -1e-9 && weightC >= -1e-9)
            {
                const double depth = weightA * a.z + weightB * b.z + weightC * c.z;
                buffer_.setPixel(static_cast<std::size_t>(x), static_cast<std::size_t>(y), depth, pixel);
            }
        }
    }
}