#include <gtest/gtest.h>
#include <memory>
#include "../include/array.h"
#include "../include/figure.h"
#include "../include/point.h"
#include "../include/polygon.h"

template<typename T>
concept TestPointScalar = requires {
    { Point<T>() } -> std::same_as<Point<T>>;
    requires std::is_arithmetic_v<T>;
};

TEST(PointConceptTest, ConceptCheck) {
    static_assert(TestPointScalar<int>);
    static_assert(TestPointScalar<double>);
}

TEST(ArrayTest, PushBackAndSize) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayMoveTest, MoveOnResize) {
    Array<int> arr;
    for(int i = 0; i < 10; ++i)
        arr.push_back(i);
    for(int i = 0; i < 10; ++i)
        EXPECT_EQ(arr[i], i);
}


TEST(PointTest, CreatePointWithScalarTypes) {
    Point<int> p1(1, 2);
    Point<double> p2(1.5, 2.5);

    EXPECT_EQ(p1.x(), 1);
    EXPECT_EQ(p1.y(), 2);
    EXPECT_DOUBLE_EQ(p2.x(), 1.5);
    EXPECT_DOUBLE_EQ(p2.y(), 2.5);
}

TEST(PentagonTest, AreaCalculation) {
    Pentagon<double> p({{0,0}, {1,0}, {1.5,1}, {0.5,2}, {-0.5,1}});
    double area = p.area();
    EXPECT_NEAR(area, 2.5, 0.5);
}

TEST(HexagonTest, AreaIsPositive) {
    Hexagon<double> h({{0,0}, {1,0}, {1.5,1}, {1,2}, {0,2}, {-0.5,1}});
    EXPECT_GT(h.area(), 0);
}

TEST(OctagonTest, CenterCalculation) {
    Octagon<double> o({{1,0},{2,0},{3,1},{3,2},{2,3},{1,3},{0,2},{0,1}});

    auto c = o.center();
    EXPECT_NEAR(c.x(), 1.5, 0.1);
    EXPECT_NEAR(c.y(), 1.5, 0.1);
}

TEST(FigureCopyCompareTest, CopyConstructorAndAssignment) {
    Pentagon<double> p1({{0,0},{1,0},{1,1},{0,1},{-0.5,0.5}});
    Pentagon<double> p2 = p1; 
    Pentagon<double> p3({{0,0},{0,0},{0,0},{0,0},{0,0}});
    p3 = p1; 
    EXPECT_EQ(static_cast<double>(p1), static_cast<double>(p2));
    EXPECT_EQ(static_cast<double>(p1), static_cast<double>(p3));
}

TEST(FigureCopyCompareTest, EqualityOperator) {
    Pentagon<double> p1({{0,0},{1,0},{1,1},{0,1},{-0.5,0.5}});
    Pentagon<double> p2({{0,0},{1,0},{1,1},{0,1},{-0.5,0.5}});
    Pentagon<double> p3({{0,0},{1,0},{1,1},{0,1},{0,0}});
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(FigurePolymorphismTest, AreaCasting) {
    std::shared_ptr<Figure<double>> f = std::make_shared<Pentagon<double>>(
        std::initializer_list<Point<double>>{{0,0},{1,0},{1,1},{0,1},{-0.5,0.5}});
    double area = static_cast<double>(*f); 
    EXPECT_GT(area, 0);
}

TEST(TotalAreaTest, SumOfFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    auto p = std::make_shared<Pentagon<double>>(
        std::initializer_list<Point<double>>{{0,0},{1,0},{1,1},{0,1},{-0.5,0.5}});
    auto h = std::make_shared<Hexagon<double>>(
        std::initializer_list<Point<double>>{{0,0},{1,0},{1.5,1},{1,2},{0,2},{-0.5,1}});
    auto o = std::make_shared<Octagon<double>>(
        std::initializer_list<Point<double>>{{1,0},{2,0},{3,1},{3,2},{2,3},{1,3},{0,2},{0,1}});
    figures.push_back(p);
    figures.push_back(h);
    figures.push_back(o);

    double total = 0;
    for (size_t i = 0; i < figures.size(); ++i)
        total += static_cast<double>(*figures[i]);
    EXPECT_GT(total, 0);
}
TEST(ArrayFigureInfoTest, PrintCentersAndVertices) {
    Array<std::shared_ptr<Figure<double>>> figures;

    figures.push_back(std::make_shared<Pentagon<double>>(
        std::initializer_list<Point<double>>{{0,0},{1,0},{1,1},{0,1},{-0.5,0.5}}));
    figures.push_back(std::make_shared<Hexagon<double>>(
        std::initializer_list<Point<double>>{{0,0},{1,0},{1.5,1},{1,2},{0,2},{-0.5,1}}));
    figures.push_back(std::make_shared<Octagon<double>>(
        std::initializer_list<Point<double>>{{1,0},{2,0},{3,1},{3,2},{2,3},{1,3},{0,2},{0,1}}));

    for(size_t i = 0; i < figures.size(); ++i){
        auto c = figures[i]->center();
        EXPECT_GT(c.x(), -1000);
        EXPECT_GT(c.y(), -1000);
        size_t count = figures[i]->vertexCount();
        std::unique_ptr<Point<double>[]> vertices = figures[i]->vertices();
        for(size_t j = 0; j < count; ++j){
            EXPECT_GE(vertices[j].x(), -1000);
            EXPECT_GE(vertices[j].y(), -1000);
        }
        EXPECT_EQ(count, figures[i]->vertexCount());
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
