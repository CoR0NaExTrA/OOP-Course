#define CATCH_CONFIG_MAIN
#include "../GeometricShape/CLineSegment.h"
#include "../GeometricShape/CTriangle.h"
#include "../GeometricShape/CRectangle.h"
#include "../GeometricShape/CCircle.h"
#include "../../../Catch/catch.hpp"

TEST_CASE("CLineSegment")
{
    SECTION("CLineSegment behaves correctly")
    {
        CPoint start(0, 0);
        CPoint end(3, 4);
        uint32_t color = 0xABCDEF;

        CLineSegment segment(start, end, color);
        //разобраться в approx

        CHECK(segment.GetStartPoint().GetX() == Approx(0));
        CHECK(segment.GetStartPoint().GetY() == Approx(0));
        CHECK(segment.GetEndPoint().GetX() == Approx(3));
        CHECK(segment.GetEndPoint().GetY() == Approx(4));
        CHECK(segment.GetPerimeter() == Approx(5.0));
        CHECK(segment.GetArea() == Approx(0.0));
        CHECK(segment.GetOutlineColor() == color);

        CHECK(segment.ToString().find("LineSegment") != std::string::npos);
        CHECK(segment.ToString().find("color=#abcdef") != std::string::npos);
    }
    
    SECTION("CLineSegment with zero length has zero perimeter and area")
    {
        CPoint point(1.0, 1.0);
        uint32_t color = 0xFFFFFF;

        CLineSegment segment(point, point, color);

        CHECK(segment.GetPerimeter() == Approx(0.0));
        CHECK(segment.GetArea() == Approx(0.0));
        CHECK(segment.ToString().find("LineSegment") != std::string::npos);
    }

}

TEST_CASE("CTriangle")
{
    SECTION("CTriangle behaves correctly")
    {
        CPoint v1(0, 0);
        CPoint v2(0, 3);
        CPoint v3(4, 0);
        uint32_t outlineColor = 0x123456;
        uint32_t fillColor = 0x654321;

        CTriangle triangle(v1, v2, v3, outlineColor, fillColor);

        CHECK(triangle.GetVertex1().GetX() == Approx(0));
        CHECK(triangle.GetVertex2().GetY() == Approx(3));
        CHECK(triangle.GetVertex3().GetX() == Approx(4));
        CHECK(triangle.GetArea() == Approx(6.0));
        CHECK(triangle.GetPerimeter() == Approx(12.0));
        CHECK(triangle.GetOutlineColor() == outlineColor);
        CHECK(triangle.GetFillColor() == fillColor);

        CHECK(triangle.ToString().find("Triangle") != std::string::npos);
        CHECK(triangle.ToString().find("OutlineColor=#123456") != std::string::npos);
        CHECK(triangle.ToString().find("FillColor=#654321") != std::string::npos);
    }

    SECTION("CTriangle with all vertices equal has zero area and perimeter")
    {
        CPoint v(2.0, 2.0);
        CTriangle triangle(v, v, v, 0xFFFFFF, 0xFFFFFF);

        CHECK(triangle.GetArea() == Approx(0.0));
        CHECK(triangle.GetPerimeter() == Approx(0.0));
    }
}

TEST_CASE("CRectangle")
{
    SECTION("CRectangle behaves correctly")
    {
        CPoint leftTop(10, 20);
        double width = 30;
        double height = 40;
        uint32_t outlineColor = 0xFF0000;
        uint32_t fillColor = 0x00FF00;

        CRectangle rect(leftTop, width, height, outlineColor, fillColor);

        CHECK(rect.GetLeftTop().GetX() == Approx(10));
        CHECK(rect.GetLeftTop().GetY() == Approx(20));
        CHECK(rect.GetWidth() == Approx(30));
        CHECK(rect.GetHeight() == Approx(40));
        CHECK(rect.GetArea() == Approx(1200));
        CHECK(rect.GetPerimeter() == Approx(140));
        CHECK(rect.GetOutlineColor() == outlineColor);
        CHECK(rect.GetFillColor() == fillColor);

        CHECK(rect.ToString().find("Rectangle") != std::string::npos);
        CHECK(rect.ToString().find("OutlineColor=#ff0000") != std::string::npos);
        CHECK(rect.ToString().find("FillColor=#ff00") != std::string::npos);
    }

    SECTION("CRectangle with zero width or height has zero area")
    {
        CRectangle zeroWidth(CPoint(0, 0), 0, 10, 0xFFFFFF, 0xFFFFFF);
        CRectangle zeroHeight(CPoint(0, 0), 10, 0, 0xFFFFFF, 0xFFFFFF);

        CHECK(zeroWidth.GetArea() == Approx(0.0));
        CHECK(zeroHeight.GetArea() == Approx(0.0));
        CHECK(zeroWidth.GetPerimeter() == Approx(20.0));
        CHECK(zeroHeight.GetPerimeter() == Approx(20.0));
    }

}

TEST_CASE("CCircle")
{
    SECTION("CCircle behaves correctly")
    {
        CPoint center(5, 5);
        double radius = 10;
        uint32_t outlineColor = 0x0000FF;
        uint32_t fillColor = 0xFFFFFF;

        CCircle circle(center, radius, outlineColor, fillColor);

        CHECK(circle.GetCenter().GetX() == Approx(5));
        CHECK(circle.GetCenter().GetY() == Approx(5));
        CHECK(circle.GetRadius() == Approx(10));
        CHECK(circle.GetArea() == Approx(M_PI * 100));
        CHECK(circle.GetPerimeter() == Approx(2 * M_PI * 10));
        CHECK(circle.GetOutlineColor() == outlineColor);
        CHECK(circle.GetFillColor() == fillColor);

        CHECK(circle.ToString().find("Circle") != std::string::npos);
        CHECK(circle.ToString().find("OutlineColor=#ff") != std::string::npos);
        CHECK(circle.ToString().find("FillColor=#ffffff") != std::string::npos);
    }

    SECTION("CCircle with radius zero has zero area and perimeter")
    {
        CCircle circle(CPoint(0, 0), 0, 0xFFFFFF, 0xFFFFFF);

        CHECK(circle.GetArea() == Approx(0.0));
        CHECK(circle.GetPerimeter() == Approx(0.0));
        CHECK(circle.ToString().find("Circle") != std::string::npos);
    }

}
