#include <algorithm>
#include <array>
#include <cmath>
#include <limits>

#include "Rasterizer.h"
#include "Face.h"
#include "IDisplay.h"

Rasterizer::Rasterizer(IDisplay& display, int scale) :
    display_(display),
    buffer_(display.getWidth(), display.getHeight()),
    depthBuffer_(display.getWidth() * display.getHeight()),
    scale_(scale)
{

}

void Rasterizer::render(const std::vector<Face>& faces)
{
    buffer_.clear();
    std::fill(depthBuffer_.begin(), depthBuffer_.end(), std::numeric_limits<double>::infinity());

    constexpr std::array<char, 6> pixels{'#', 'o', '=', '*', '%', '$'};
    std::vector<Vec3> faceNormals;
    std::vector<double> planeOffsets;
    const std::vector<std::size_t> faceSurfaceIndices =
        groupFacesByPlane(faces, faceNormals, planeOffsets);

    for (std::size_t index = 0; index < faces.size(); ++index)
    {
        fillFace(
            faces[index],
            faceNormals[index],
            pixels[faceSurfaceIndices[index] % pixels.size()]);
    }

    drawBuffer();
}

Vec3 Rasterizer::toScreen(const Vec3& vertex) const
{
    const double scale = static_cast<double>(scale_);
    const double aspectRatio =
        static_cast<double>(buffer_.width()) / static_cast<double>(buffer_.height());
    return Vec3{
        std::round(vertex.x_ * scale * aspectRatio + static_cast<double>(buffer_.width()) * 0.5),
        std::round(vertex.y_ * scale + static_cast<double>(buffer_.height()) * 0.5),
        vertex.z_
    };
}

Vec3 Rasterizer::getFaceNormal(const Face& face) const
{
    const Vec3 a{face.a_.x_ * face.a_.z_, face.a_.y_ * face.a_.z_, face.a_.z_};
    const Vec3 b{face.b_.x_ * face.b_.z_, face.b_.y_ * face.b_.z_, face.b_.z_};
    const Vec3 c{face.c_.x_ * face.c_.z_, face.c_.y_ * face.c_.z_, face.c_.z_};
    const Vec3 rawNormal = (b - a).cross(c - a);
    const double length = std::sqrt(rawNormal.dot(rawNormal));
    if (length < 1e-9)
    {
        return Vec3{0.0, 0.0, 0.0};
    }

    return Vec3{
        rawNormal.x_ / length,
        rawNormal.y_ / length,
        rawNormal.z_ / length
    };
}

double Rasterizer::getPlaneOffset(const Face& face, const Vec3& normal) const
{
    const Vec3 a{face.a_.x_ * face.a_.z_, face.a_.y_ * face.a_.z_, face.a_.z_};
    return normal.dot(a);
}

bool Rasterizer::samePlane(
    const Vec3& normalA,
    double offsetA,
    const Vec3& normalB,
    double offsetB) const
{
    constexpr double NormalTolerance = 1e-6;
    constexpr double OffsetTolerance = 1e-5;
    return normalA.dot(normalB) > 1.0 - NormalTolerance &&
           std::abs(offsetA - offsetB) < OffsetTolerance;
}

std::vector<std::size_t> Rasterizer::groupFacesByPlane(
    const std::vector<Face>& faces,
    std::vector<Vec3>& faceNormals,
    std::vector<double>& planeOffsets) const
{
    std::vector<Vec3> surfaceNormals;
    std::vector<std::size_t> faceSurfaceIndices;
    std::vector<double> surfaceOffsets;
    faceNormals.reserve(faces.size());
    planeOffsets.reserve(faces.size());
    surfaceNormals.reserve(faces.size());
    surfaceOffsets.reserve(faces.size());
    faceSurfaceIndices.reserve(faces.size());

    for (const Face& face : faces)
    {
        const Vec3 normal = getFaceNormal(face);
        const double offset = getPlaneOffset(face, normal);
        faceNormals.push_back(normal);
        planeOffsets.push_back(offset);

        std::size_t surfaceIndex = 0;
        while (surfaceIndex < surfaceNormals.size() &&
               !samePlane(normal, offset, surfaceNormals[surfaceIndex], surfaceOffsets[surfaceIndex]))
        {
            ++surfaceIndex;
        }
        if (surfaceIndex == surfaceNormals.size())
        {
            surfaceNormals.push_back(normal);
            surfaceOffsets.push_back(offset);
        }
        faceSurfaceIndices.push_back(surfaceIndex);
    }

    return faceSurfaceIndices;
}

bool Rasterizer::isFaceVisible(const Vec3& normal) const
{
    constexpr Vec3 cameraDirection{0.0, 0.0, 1.0};
    return normal.dot(cameraDirection) > 0.0;
}

double Rasterizer::edge(const Vec3& a, const Vec3& b, double x, double y)
{
    return (x - a.x_) * (b.y_ - a.y_) - (y - a.y_) * (b.x_ - a.x_);
}

void Rasterizer::fillFace(const Face& face, const Vec3& normal, char pixel)
{
    if (!isFaceVisible(normal))
    {
        return;
    }

    const Vec3 a = toScreen(face.a_);
    const Vec3 b = toScreen(face.b_);
    const Vec3 c = toScreen(face.c_);
    const Face screenFace(a, b, c);
    const double area = edge(screenFace.a_, screenFace.b_, screenFace.c_.x_, screenFace.c_.y_);
    if (std::abs(area) < 1e-9)
    {
        return;
    }

    fillScanlines(screenFace, area, pixel);
}

void Rasterizer::fillScanlines(const Face& face, double area, char pixel)
{
    const int maxScreenY = static_cast<int>(buffer_.height()) - 1;
    const double minY = std::min({face.a_.y_, face.b_.y_, face.c_.y_});
    const double maxY = std::max({face.a_.y_, face.b_.y_, face.c_.y_});
    const int firstY = std::max(0, static_cast<int>(std::ceil(minY)));
    const int lastY = std::min(maxScreenY, static_cast<int>(std::floor(maxY)));
    for (int y = firstY; y <= lastY; ++y)
    {
        int firstX = 0;
        int lastX = -1;
        if (getScanlineBounds(face, y, firstX, lastX))
        {
            fillScanline(y, firstX, lastX, face, area, pixel);
        }
    }
}

bool Rasterizer::getScanlineBounds(
    const Face& face,
    int y,
    int& firstX,
    int& lastX) const
{
    std::size_t intersectionCount = 0;
    double left = std::numeric_limits<double>::infinity();
    double right = -std::numeric_limits<double>::infinity();
    addEdgeIntersection(face.a_, face.b_, y, left, right, intersectionCount);
    addEdgeIntersection(face.b_, face.c_, y, left, right, intersectionCount);
    addEdgeIntersection(face.c_, face.a_, y, left, right, intersectionCount);

    if (intersectionCount < 2)
    {
        return false;
    }

    const int maxScreenX = static_cast<int>(buffer_.width()) - 1;
    firstX = std::max(0, static_cast<int>(std::ceil(left)));
    lastX = std::min(maxScreenX, static_cast<int>(std::floor(right)));
    return firstX <= lastX;
}

void Rasterizer::addEdgeIntersection(
    const Vec3& start,
    const Vec3& end,
    int y,
    double& left,
    double& right,
    std::size_t& intersectionCount) const
{
    if (start.y_ == end.y_)
    {
        if (static_cast<double>(y) == start.y_)
        {
            left = std::min({left, start.x_, end.x_});
            right = std::max({right, start.x_, end.x_});
            intersectionCount += 2;
        }
        return;
    }

    const double t = (static_cast<double>(y) - start.y_) / (end.y_ - start.y_);
    if (t >= 0.0 && t <= 1.0)
    {
        const double intersection = start.x_ + t * (end.x_ - start.x_);
        left = std::min(left, intersection);
        right = std::max(right, intersection);
        ++intersectionCount;
    }
}

void Rasterizer::fillScanline(
    int y,
    int firstX,
    int lastX,
    const Face& face,
    double area,
    char pixel)
{
    for (int x = firstX; x <= lastX; ++x)
    {
        const double sampleX = static_cast<double>(x);
        const double sampleY = static_cast<double>(y);
        const double weightA = edge(face.b_, face.c_, sampleX, sampleY) / area;
        const double weightB = edge(face.c_, face.a_, sampleX, sampleY) / area;
        const double weightC = edge(face.a_, face.b_, sampleX, sampleY) / area;
        const double reciprocalDepth =
            weightA / face.a_.z_ + weightB / face.b_.z_ + weightC / face.c_.z_;
        if (reciprocalDepth > 0.0)
        {
            writePixel(x, y, 1.0 / reciprocalDepth, pixel);
        }
    }
}

void Rasterizer::writePixel(int x, int y, double depth, char pixel)
{
    const std::size_t screenX = static_cast<std::size_t>(x);
    const std::size_t screenY = static_cast<std::size_t>(y);
    const std::size_t depthIndex = screenY * buffer_.width() + screenX;
    if (depth < depthBuffer_[depthIndex])
    {
        depthBuffer_[depthIndex] = depth;
        buffer_.setPixel(screenX, screenY, pixel);
    }
}

void Rasterizer::drawBuffer()
{
    display_.clear();
    for (FrameBuffer::Iterator row = buffer_.begin(); row != buffer_.end(); ++row)
    {
        const RowView rowView = *row;
        display_.drawBuffer(rowView);
    }
}