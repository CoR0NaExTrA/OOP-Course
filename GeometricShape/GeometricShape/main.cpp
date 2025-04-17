#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "ISolidShape.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

using namespace std;

shared_ptr<IShape> ParseShape(const string& line)
{
    istringstream iss(line);
    string type;
    iss >> type;

    if (type == "line")
    {
        double x1, y1, x2, y2;
        string color;
        iss >> x1 >> y1 >> x2 >> y2 >> color;
        return make_shared<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), stoul(color, nullptr, 16));
    }
    else if (type == "triangle")
    {
        double x1, y1, x2, y2, x3, y3;
        string outline, fill;
        iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outline >> fill;
        return make_shared<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), stoul(outline, nullptr, 16), stoul(fill, nullptr, 16));
    }
    else if (type == "rectangle")
    {
        double x, y, w, h;
        string outline, fill;
        iss >> x >> y >> w >> h >> outline >> fill;
        return make_shared<CRectangle>(CPoint(x, y), w, h, stoul(outline, nullptr, 16), stoul(fill, nullptr, 16));
    }
    else if (type == "circle")
    {
        double x, y, r;
        string outline, fill;
        iss >> x >> y >> r >> outline >> fill;
        return make_shared<CCircle>(CPoint(x, y), r, stoul(outline, nullptr, 16), stoul(fill, nullptr, 16));
    }
    return nullptr;
}

shared_ptr<IShape> GetMaxAreaShape(const vector<shared_ptr<IShape>>& shapes)
{
    return *max_element(shapes.begin(), shapes.end(), [](const auto& a, const auto& b) {
        return a->GetArea() < b->GetArea();
        });
}

shared_ptr<IShape> GetMinPerimeterShape(const vector<shared_ptr<IShape>>& shapes)
{
    return *min_element(shapes.begin(), shapes.end(), [](const auto& a, const auto& b) {
        return a->GetPerimeter() < b->GetPerimeter();
        });
}

void PrintShapeDetails(const string& title, const shared_ptr<IShape>& shape)
{
    cout << "\n" << title << ":" << endl;
    cout << shape->ToString() << endl;
    cout << "Perimeter: " << shape->GetPerimeter() << endl;
    cout << "Area: " << shape->GetArea() << endl;
    cout << "Outline color: #" << hex << shape->GetOutlineColor() << dec << endl;

    if (auto solid = dynamic_pointer_cast<ISolidShape>(shape))
    {
        cout << "Fill color: #" << hex << solid->GetFillColor() << dec << endl;
    }
}

int main()
{
    vector<shared_ptr<IShape>> shapes;
    string line;

    while (getline(cin, line))
    {
        if (!line.empty())
        {
            auto shape = ParseShape(line);
            if (shape)
            {
                shapes.push_back(shape);
            }
        }
    }

    if (!shapes.empty())
    {
        auto maxAreaShape = GetMaxAreaShape(shapes);
        auto minPerimeterShape = GetMinPerimeterShape(shapes);

        PrintShapeDetails("Shape with maximum area", maxAreaShape);
        PrintShapeDetails("Shape with minimum perimeter", minPerimeterShape);
    }
    else
    {
        cout << "No shapes were parsed." << endl;
    }

    return 0;
}
