#pragma once
#ifndef CELLBORDER_H
#define CELLBORDER_H

#include <string>
#include <tuple>

class CellBorder {
public:
    virtual ~CellBorder() = default;
    virtual std::string GnuplotPrintString(const std::string&) const = 0;
    virtual std::string SVGPrintString(const std::string&) const = 0;
};

class LineBorder : public CellBorder {
public:
    LineBorder(double x1, double y1, double x2, double y2);
    LineBorder(std::tuple<double, double, double, double>);
    std::string GnuplotPrintString(const std::string&) const override;
    std::string SVGPrintString(const std::string&) const override;

    double x1_, y1_, x2_, y2_;
};

class ArcBorder : public CellBorder {
public:
    ArcBorder(double cx, double cy, double r, double theta1, double theta2);
    std::string GnuplotPrintString(const std::string&) const override;
    std::string SVGPrintString(const std::string&) const override;

    double cx_, cy_, r_, theta1_, theta2_;
};

#endif /* end of include guard: CELLBORDER_H */
