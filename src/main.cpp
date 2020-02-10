#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

struct Point
{
    std::string ToString() const
    {
        std::ostringstream oss;
        oss << "(" << x << ", " << y << ")";
        return oss.str();
    }

    int x;
    int y;
};

class Rectangle
{
public:
    Rectangle(Point corner1, Point corner2)
    : top{FindTop(corner1.y, corner2.y)},
      bottom{FindBottom(corner1.y, corner2.y)},
      right{FindRight(corner1.x, corner2.x)},
      left{FindLeft(corner1.x, corner2.x)}
    {
    }

    Rectangle(int x1, int y1, int x2, int y2)
    : top{ FindTop(y1, y2) },
      bottom{ FindBottom(y1, y2) },
      right{  FindRight(x1, x2) },
      left{ FindLeft(x1, x2) }
    {
    }

    int Top() const
    {
        return top;
    }
    int Bottom() const
    {
        return bottom;
    }
    int Left() const
    {
        return left;
    }
    int Right() const
    {
        return right;
    }
private:
    int FindBottom(int x1, int x2)
    {
        return std::min(x1, x2);
    }

    int FindTop(int x1, int x2)
    {
        return std::max(x1, x2);
    }

    int FindRight(int y1, int y2)
    {
        return std::max(y1, y2);
    }

    int FindLeft(int y1, int y2)
    {
        return std::min(y1, y2);
    }

    int top;
    int bottom;
    int left;
    int right;
};


void PrintPoint(const Point& c)
{
    std::cout << c.ToString() << std::endl;
}

void PrintRectangle(const Rectangle& r)
{
    std::cout << "Top: " << r.Top() << ", Bottom: " << r.Bottom() << ", Left: " << r.Left() << ", Right: " << r.Right() << std::endl;
}

int ToInt(const std::string& s)
{
    try
    {
        return std::stoi(s);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "'" << s << "' could not be converted to an int.\n";
        throw e;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "'" << s << "' is greater than the int max value.\n";
        throw e;
    }
}

void VerifyRelativePointLocations(const Point& bottomLeft, const Point& topRight)
{
    if(bottomLeft.x >= topRight.x)
    {
        throw std::runtime_error(
            std::string{
            "Relative point locations are invalid."
            " Bottom left x coordinate is greater than than top right x coordinate."} +
                " Bottom left : " + bottomLeft.ToString() +
                " Top right : " + topRight.ToString());
    }
    if(bottomLeft.y >= topRight.y)
    {
        throw std::runtime_error(
            std::string{
            "Relative point locations are invalid."
            " Bottom left y coordinate is greater than than top right y coordinate."} +
                " Bottom left : " + bottomLeft.ToString() +
                " Top right : " + topRight.ToString());
    }
}

void PromptUser()
{
    std::cout << "Enter barren plots" << std::endl;
}

std::vector<Rectangle> ParseInput()
{
    std::string answer;
    std::vector<Rectangle> rec{};
    std::getline(std::cin, answer);
    std::istringstream stream(answer);

    std::vector<std::string> results(std::istream_iterator<std::string>{stream},
                                     std::istream_iterator<std::string>());

    if(results.size() % 4 != 0)
    {
        throw std::runtime_error("Invalid number of points given");
    }

    for(size_t i = 0; i < results.size(); i += 4)
    {

        auto bottomLeft = Point{ToInt(results[i]), ToInt(results[i + 1])};
        auto topRight = Point{ToInt(results[i + 2]), ToInt(results[i + 3])};
        VerifyRelativePointLocations(bottomLeft, topRight);
        rec.emplace_back(bottomLeft, topRight);
    }
    return rec;
}

int main()
{
    PromptUser();
    auto barrenPlots = ParseInput();

    for(const auto& p : barrenPlots)
    {
        PrintRectangle(p);
    }

}