#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define w 400
using namespace cv;
void MyEllipse( Mat img, double angle );
void MyFilledCircle( Mat img, Point center );
void MyPolygon( Mat img );
void MyLine( Mat img, Point start, Point end );
int main( void ){
  char atom_window[] = "Drawing 1: Atom";
  char rook_window[] = "Drawing 2: Rook";
  Mat atom_image = Mat::zeros( w, w, CV_8UC3 );
  Mat rook_image = Mat::zeros( w, w, CV_8UC3 );
  MyEllipse( atom_image, 90 );
  MyEllipse( atom_image, 0 );
  MyEllipse( atom_image, 45 );
  MyEllipse( atom_image, -45 );
  MyFilledCircle( atom_image, Point( w/2, w/2) );
  MyPolygon( rook_image );
  rectangle( rook_image,
         Point( 0, 7*w/8 ),
         Point( w, w),
         Scalar( 0, 255, 255 ),
         FILLED,
         LINE_8 );
  MyLine( rook_image, Point( 0, 15*w/16 ), Point( w, 15*w/16 ) );
  MyLine( rook_image, Point( w/4, 7*w/8 ), Point( w/4, w ) );
  MyLine( rook_image, Point( w/2, 7*w/8 ), Point( w/2, w ) );
  MyLine( rook_image, Point( 3*w/4, 7*w/8 ), Point( 3*w/4, w ) );
  imshow( atom_window, atom_image );
  moveWindow( atom_window, 0, 200 );
  imshow( rook_window, rook_image );
  moveWindow( rook_window, w, 200 );
  waitKey( 0 );
  return(0);
}

void MyEllipse( Mat img, double angle )
{
  int thickness = 2;
  int lineType = 8;
  ellipse( img,
       Point( w/2, w/2 ),
       Size( w/4, w/16 ),
       angle,
       0,
       360,
       Scalar( 255, 0, 0 ),
       thickness,
       lineType );
}
void MyFilledCircle( Mat img, Point center )
{
  circle( img,
      center,
      w/32,
      Scalar( 0, 0, 255 ),
      FILLED,
      LINE_8 );
}
void MyPolygon( Mat img )
{
  int lineType = LINE_8;
  Point rook_points[1][20];
  rook_points[0][0]  = Point(    w/4,   7*w/8 );
  rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
  rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
  rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
  rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
  rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
  rook_points[0][6]  = Point(  3*w/4,     w/8 );
  rook_points[0][7]  = Point( 26*w/40,    w/8 );
  rook_points[0][8]  = Point( 26*w/40,    w/4 );
  rook_points[0][9]  = Point( 22*w/40,    w/4 );
  rook_points[0][10] = Point( 22*w/40,    w/8 );
  rook_points[0][11] = Point( 18*w/40,    w/8 );
  rook_points[0][12] = Point( 18*w/40,    w/4 );
  rook_points[0][13] = Point( 14*w/40,    w/4 );
  rook_points[0][14] = Point( 14*w/40,    w/8 );
  rook_points[0][15] = Point(    w/4,     w/8 );
  rook_points[0][16] = Point(    w/4,   3*w/8 );
  rook_points[0][17] = Point( 13*w/32,  3*w/8 );
  rook_points[0][18] = Point(  5*w/16, 13*w/16 );
  rook_points[0][19] = Point(    w/4,  13*w/16 );
  const Point* ppt[1] = { rook_points[0] };
  int npt[] = { 20 };
  fillPoly( img,
        ppt,
        npt,
        1,
        Scalar( 255, 255, 255 ),
        lineType );
}

void MyLine( Mat img, Point start, Point end )
{
  int thickness = 2;
  int lineType = LINE_8;
  line( img,
    start,
    end,
    Scalar( 0, 0, 0 ),
    thickness,
    lineType );
}

// Vertically gradient
void FillGradient(Mat img, int y1, int x1, int y2, int x2, Vec3d direction, Scalar fill1, Scalar fill2)
{
  int dy = abs(y2 - y1);
  int dx = abs(x2 - x1);

  int dy2 = dy / 2;
  int dx2 = dx / 2;
  dy2 = 0;
  dx2 = 0;

  direction[0];
  direction[1];
  direction[2];

  direction[0];
  direction[1];

  double valy1 = y1;
  double valy2 = y2;
  double valx1 = x1;
  double valx2 = x2;

  // double dy = 
  double dy = valy2 - valy1;
  double dx = valx2 - valx1;
  
  double c1 = fill1.val[0];
  double c2 = fill1.val[1];
  double c3 = fill1.val[2];

  double c1_1 = fill2.val[0];
  double c1_2 = fill2.val[1];
  double c1_3 = fill2.val[2];

  //
  // v1: direction vector 
  // c1: fill_start
  // c2: fill_end
  // 
  // Draw the whole with colors
  //  Dummy methods
  //    Find the color of Position(y,x)
  //      Let:
  //        l1 = 
  //      
  //  
  // 
  

}