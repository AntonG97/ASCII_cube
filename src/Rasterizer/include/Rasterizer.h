#pragma once

#include <cstddef>
#include <vector>

#include "FrameBuffer.h"
#include "Vec3.h"

class Shape;
class Face;
class IDisplay;
class Rasterizer
{
private:
    IDisplay& display_;
    FrameBuffer buffer_;
    std::vector<double> depthBuffer_;
    int scale_;

    Vec3 toScreen(const Vec3& vertex) const;
    Vec3 getFaceNormal(const Face& face) const;
    double getPlaneOffset(const Face& face, const Vec3& normal) const;
    bool samePlane(const Vec3& normalA, double offsetA, const Vec3& normalB, double offsetB) const;
    std::vector<std::size_t> groupFacesByPlane(
        const std::vector<Face>& faces,
        std::vector<Vec3>& faceNormals,
        std::vector<double>& planeOffsets) const;
    bool isFaceVisible(const Vec3& normal) const;
    static double edge(const Vec3& a, const Vec3& b, double x, double y);
    void fillFace(const Face& face, const Vec3& normal, char pixel);
    void fillScanlines(const Face& face, double area, char pixel);
    bool getScanlineBounds(
        const Face& face,
        int y,
        int& firstX,
        int& lastX) const;
    void addEdgeIntersection(
        const Vec3& start,
        const Vec3& end,
        int y,
        double& left,
        double& right,
        std::size_t& intersectionCount) const;
    void fillScanline(
        int y,
        int firstX,
        int lastX,
        const Face& face,
        double area,
        char pixel);
    void writePixel(int x, int y, double depth, char pixel);
    void drawBuffer();

public:
    Rasterizer(IDisplay& display, int scale);
    void render(const std::vector<Face>& faces);
};