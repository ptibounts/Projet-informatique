#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED
#include <string>
#include <fstream>
#include <set>


constexpr char defcol[] = "black";

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=2000, int _height=1800);
        ~Svgfile();

        void addDisk(int x, int y, double r, std::string color=defcol);
        void addDisk(double x, double y, double r, std::string color, double thickness, std::string colorStroke);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);

        void addRect(int x, int y, int w, int h, std::string color);
        void addLine(int x1, int y1, int x2, int y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);
        void addEllipse(int x, int y, int w, int h, std::string color=defcol);
        void addRadial(int x, int y);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;
    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour �viter les ouverture multiples
        static std::set<std::string> s_openfiles;

};



#endif // SVGFILE_H_INCLUDED
